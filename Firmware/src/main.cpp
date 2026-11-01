#include <cstdio>
#include <cstring>
#include <algorithm>
#include "pico/stdlib.h"
#include "pico/stdio_usb.h"
#include "hardware/pwm.h"
#include "config.h"
#include "acquisition.h"

struct Settings {
    uint32_t rate  = 1000000;
    uint16_t level = 2048;
    uint8_t  rising = 1;
    uint8_t  mode   = TRIG_AUTO;
};

// Onda quadra 1 kHz 50% su GP29 per compensare la sonda (pad CAL)
static void cal_init() {
    gpio_set_function(PIN_CAL, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(PIN_CAL);
    pwm_set_clkdiv(slice, 2.0f);              // 125 MHz / 2 = 62,5 MHz
    pwm_set_wrap(slice, 62499);               // 1 kHz
    pwm_set_gpio_level(PIN_CAL, 31250);       // 50%
    pwm_set_enabled(slice, true);
}

// Comando dal PC: "SET <rate> <level 0-4095> <rising 0/1> <mode 0 free/1 auto/2 normal>\n"
static void poll_commands(Settings& s) {
    static char line[64];
    static size_t len = 0;
    int c;
    while ((c = getchar_timeout_us(0)) != PICO_ERROR_TIMEOUT) {
        if (c == '\n') {
            line[len] = 0; len = 0;
            unsigned r, l, e, m;
            if (sscanf(line, "SET %u %u %u %u", &r, &l, &e, &m) == 4) {
                s.rate   = acq_set_rate(r);
                s.level  = std::min<unsigned>(l, 4095);
                s.rising = e ? 1 : 0;
                s.mode   = std::min<unsigned>(m, 2);
            }
        } else if (c != '\r' && len < sizeof(line) - 1) {
            line[len++] = (char)c;
        }
    }
}

// Frame: A5 5A | rate u32 | n u16 | triggered u8 | 0 | n * u16 (little endian)
static void send_frame(uint32_t rate, bool trig, const uint16_t* buf, uint16_t n) {
    uint8_t h[10] = {0xA5, 0x5A};
    memcpy(h + 2, &rate, 4);
    memcpy(h + 6, &n, 2);
    h[8] = trig ? 1 : 0;
    h[9] = 0;
    fwrite(h, 1, sizeof(h), stdout);
    fwrite(buf, 2, n, stdout);
    fflush(stdout);
}

int main() {
    stdio_init_all();
    stdio_set_translate_crlf(&stdio_usb, false);   // dati binari: niente \n -> \r\n
    cal_init();

    Settings s;
    s.rate = acq_set_rate(s.rate);
    acq_init();
    s.rate = acq_set_rate(s.rate);
    acq_start();

    static uint16_t frame[FRAME_SAMPLES];

    while (true) {
        poll_commands(s);
        acq_service();

        TriggerCfg t{s.level, 24, s.rising != 0, (TrigMode)s.mode};
        uint32_t win_us = (uint64_t)FRAME_SAMPLES * 1000000u / s.rate;
        uint32_t timeout = (s.mode == TRIG_AUTO) ? std::max<uint32_t>(50000, 2 * win_us)
                                                 : 200000;
        bool trig = false;
        if (acq_capture(t, frame, timeout, &trig))
            send_frame(s.rate, trig, frame, FRAME_SAMPLES);
        sleep_ms(5);
    }
}
