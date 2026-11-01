#pragma once
#include "pico/stdlib.h"

// ---- Pin (controlla che coincidano con il tuo schema!) ----
constexpr uint PIN_ADC_SCK = 2;   // SPI0 SCK  -> ADS7883 SCLK
constexpr uint PIN_ADC_SDO = 4;   // SPI0 RX   <- SDO (dopo 74LVC1G125)
constexpr uint PIN_ADC_CS  = 5;   // SPI0 CSn  -> ADS7883 CS_N
constexpr uint PIN_CAL     = 29;  // PWM calibrazione (R11 -> pad CAL)

// ---- ADC ----
constexpr uint32_t ADC_SPI_BAUD = 31250000;  // max ADS7883: 48 MHz
constexpr uint32_t ACQ_MIN_RATE = 2000;      // limite del timer DMA (125MHz/65535)
constexpr uint32_t ACQ_MAX_RATE = 1500000;   // limite pratico dell'SPI a 31,25 MHz
constexpr int      ADC_SHIFT    = 0;         // se i valori escono x2 o /2 prova 1 o -1 (vedi README)

// ---- Buffer ----
constexpr uint RING_BITS      = 14;                    // anello da 16 KB
constexpr uint RING_SAMPLES   = (1u << RING_BITS) / 2; // 8192 campioni da 16 bit
constexpr uint FRAME_SAMPLES  = 1024;                  // campioni per schermata
constexpr uint PRE_TRIGGER    = 256;                   // campioni prima del trigger
