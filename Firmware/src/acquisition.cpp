#include "acquisition.h"
#include "config.h"
#include "hardware/spi.h"
#include "hardware/dma.h"
#include "hardware/clocks.h"
#include "hardware/gpio.h"

// L'anello deve essere allineato alla propria dimensione in byte
alignas(1u << RING_BITS) static uint16_t ring[RING_SAMPLES];
static uint16_t dummy_tx = 0;
static int  dma_rx, dma_tx;
static uint dma_timer;

static inline uint16_t smp(uint32_t i) {
    uint16_t raw = ring[i & (RING_SAMPLES - 1)];
    uint16_t v = (ADC_SHIFT >= 0) ? (raw >> ADC_SHIFT) : (raw << -ADC_SHIFT);
    return v & 0x0FFF;
}

void acq_init() {
    spi_init(spi0, ADC_SPI_BAUD);
    // 16 bit per frame: 4 zeri + 12 bit di dato. CS_N e' gestito dall'hardware SPI.
    spi_set_format(spi0, 16, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    gpio_set_function(PIN_ADC_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_ADC_SDO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_ADC_CS,  GPIO_FUNC_SPI);

    dma_timer = dma_claim_unused_timer(true);
    dma_rx = dma_claim_unused_channel(true);
    dma_tx = dma_claim_unused_channel(true);

    // RX: SPI -> anello (ritmato dal FIFO RX)
    dma_channel_config c = dma_channel_get_default_config(dma_rx);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_16);
    channel_config_set_read_increment(&c, false);
    channel_config_set_write_increment(&c, true);
    channel_config_set_dreq(&c, spi_get_dreq(spi0, false));
    channel_config_set_ring(&c, true, RING_BITS);
    dma_channel_configure(dma_rx, &c, ring, &spi_get_hw(spi0)->dr, 0xFFFFFFFF, false);

    // TX: parole fittizie verso l'SPI, ritmate dal timer DMA = frequenza di campionamento
    c = dma_channel_get_default_config(dma_tx);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_16);
    channel_config_set_read_increment(&c, false);
    channel_config_set_write_increment(&c, false);
    channel_config_set_dreq(&c, dma_get_timer_dreq(dma_timer));
    dma_channel_configure(dma_tx, &c, &spi_get_hw(spi0)->dr, &dummy_tx, 0xFFFFFFFF, false);
}

uint32_t acq_set_rate(uint32_t hz) {
    if (hz < ACQ_MIN_RATE) hz = ACQ_MIN_RATE;
    if (hz > ACQ_MAX_RATE) hz = ACQ_MAX_RATE;
    uint32_t clk = clock_get_hz(clk_sys);
    uint32_t den = (clk + hz / 2) / hz;       // periodo in cicli di clock
    if (den > 65535) den = 65535;
    if (den < 1) den = 1;
    dma_timer_set_fraction(dma_timer, 1, (uint16_t)den);
    return clk / den;
}

void acq_start() {
    dma_start_channel_mask((1u << dma_rx) | (1u << dma_tx));
}

void acq_service() {
    // A 1,5 MSPS il contatore da 4 miliardi dura ~48 minuti: lo riarmiamo prima
    if (dma_channel_hw_addr(dma_rx)->transfer_count < 0x10000000u) {
        dma_channel_abort(dma_tx);
        dma_channel_abort(dma_rx);
        while (spi_is_readable(spi0)) (void)spi_get_hw(spi0)->dr;
        dma_channel_set_trans_count(dma_rx, 0xFFFFFFFF, false);
        dma_channel_set_trans_count(dma_tx, 0xFFFFFFFF, false);
        acq_start();
    }
}

uint32_t acq_write_index() {
    uint32_t addr = dma_channel_hw_addr(dma_rx)->write_addr;
    return ((addr - (uint32_t)ring) >> 1) & (RING_SAMPLES - 1);
}

bool acq_capture(const TriggerCfg& t, uint16_t* out, uint32_t timeout_us, bool* triggered) {
    const uint32_t M = RING_SAMPLES - 1;
    const uint32_t post = FRAME_SAMPLES - PRE_TRIGGER;
    uint32_t last = acq_write_index();
    uint32_t t0 = time_us_32();
    bool armed = false, found = false;
    uint32_t trig = 0;

    if (t.mode != TRIG_FREE) {
        while (!found) {
            uint32_t cur = acq_write_index();
            while (last != cur) {
                uint16_t s = smp(last);
                if (t.rising) {
                    if (s + t.hyst < t.level) armed = true;
                    else if (armed && s >= t.level) found = true;
                } else {
                    if (s > t.level + t.hyst) armed = true;
                    else if (armed && s <= t.level) found = true;
                }
                if (found) { trig = last; break; }
                last = (last + 1) & M;
            }
            if (found) break;
            if (time_us_32() - t0 > timeout_us) break;
        }
    }

    uint32_t base;
    if (found) {
        // aspetta i campioni successivi al trigger
        uint32_t t1 = time_us_32();
        while (((acq_write_index() - trig) & M) < post) {
            if (time_us_32() - t1 > 2000000) return false;
        }
        base = (trig - PRE_TRIGGER) & M;
    } else {
        if (t.mode == TRIG_NORMAL) { *triggered = false; return false; }
        base = (acq_write_index() - FRAME_SAMPLES) & M;   // ultimo blocco disponibile
    }
    for (uint i = 0; i < FRAME_SAMPLES; i++) out[i] = smp(base + i);
    *triggered = found;
    return true;
}
