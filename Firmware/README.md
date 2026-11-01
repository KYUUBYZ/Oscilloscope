# Firmware (C++, Pico SDK)

Mettilo nella cartella `firmware/` del repo.

## Compilare con VS Code
1. Installa l'estensione "Raspberry Pi Pico" e fai "Import Project" su questa cartella (Pico SDK 2.x).
2. Scheda: waveshare_rp2040_zero (gia' impostata nel CMakeLists).
3. Build, poi tieni premuto BOOTSEL, collega l'USB e carica il file .uf2.

## Usare
    pip install pyserial numpy matplotlib
    python viewer.py COM5 --rate 1000000 --trig 0 --edge rise --mode auto

## Prima prova (importante)
- BNC in corto (ingresso 0 V): il valore medio deve essere ~2048 (2,5 V).
- Se leggi ~4096 o ~1024 l'allineamento dei bit e' sbagliato: cambia ADC_SHIFT in config.h.
- Sonda sul pad CAL: onda quadra a 1 kHz di 3,3 V (0,33 V alla punta con sonda x10).

## Come funziona
SPI0 + 2 canali DMA: il TX, ritmato da un timer DMA, fa partire i 16 clock di ogni
conversione (CS_N lo gestisce l'hardware SPI); l'RX scrive in un anello da 8192 campioni.
Il trigger (fronte salita/discesa, livello, isteresi) cerca nell'anello e copia 1024
campioni con 256 di pre-trigger. Il frame esce via USB CDC (formato in main.cpp).
