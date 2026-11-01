#pragma once
#include <cstdint>

enum TrigMode : uint8_t { TRIG_FREE = 0, TRIG_AUTO = 1, TRIG_NORMAL = 2 };

struct TriggerCfg {
    uint16_t level;   // 0..4095
    uint16_t hyst;    // isteresi in codici
    bool     rising;
    TrigMode mode;
};

void     acq_init();
uint32_t acq_set_rate(uint32_t hz);   // ritorna la frequenza reale
void     acq_start();
void     acq_service();               // da chiamare nel loop: riarma il DMA
uint32_t acq_write_index();
// true se ha prodotto un frame; *triggered dice se c'e' stato un vero trigger
bool     acq_capture(const TriggerCfg& t, uint16_t* out, uint32_t timeout_us, bool* triggered);
