# Oscilloscope

<!--START_SECTION:BOM-TABLE-->
| Item | Qty | Supplier | Cost/item | Total Cost | link |
| --- | --- | --- | --- | --- | --- |
| RT0805BRD0710KL | 20 | LCSC | 0.0371 | 0.74 | [Link](https://www.lcsc.com/product-detail/C110775.html) |
| FRC0805J470 TS | 100 | LCSC | 0.0017 | 0.17 | [Link](https://www.lcsc.com/product-detail/C2907331.html) |
| HRC0805F4703FNTN | 100 | LCSC | 0.0019 | 0.19 | [Link](https://www.lcsc.com/product-detail/C54921198.html) |
| CGA0805X7R104K500KT | 100 | LCSC | 0.0043 | 0.43 | [Link](https://www.lcsc.com/product-detail/C7503486.html) |
| BAT54S | 100 | LCSC | 0.0123 | 1.23 | [Link](https://www.lcsc.com/product-detail/C916425.html) |
| FM21X102K501PXG | 250 | LCSC | 0.0080 | 2.00 | [Link](https://www.lcsc.com/product-detail/C440004.html) |
| CC0805CRNPO9BN2R2 | 50 | LCSC | 0.0144 | 0.72 | [Link](https://www.lcsc.com/product-detail/C519933.html) |
| SN74LVC1G125DCKR(AT) | 20 | LCSC | 0.0381 | 0.76 | [Link](https://www.lcsc.com/product-detail/C54973442.html) |
| TCC0805X7R103K251DT | 100 | LCSC | 0.0061 | 0.61 | [Link](https://www.lcsc.com/product-detail/C282726.html) |
| CC0805FRNPO9BN100 | 20 | LCSC | 0.0369 | 0.74 | [Link](https://www.lcsc.com/product-detail/C541512.html) |
| CA45A-P-6.3V-10UF-K | 5 | LCSC | 0.1209 | 0.60 | [Link](https://www.lcsc.com/product-detail/C2976905.html) |
| GRM21BR61C106KE15L | 20 | LCSC | 0.0375 | 0.75 | [Link](https://www.lcsc.com/product-detail/C77075.html) |
| AC0805KKX7R5BB105 | 20 | LCSC | 0.0290 | 0.58 | [Link](https://www.lcsc.com/product-detail/C3869051.html) |
| 1N5819 | 40 | LCSC | 0.0367 | 1.47 | [Link](https://www.lcsc.com/product-detail/C2474.html) |
| TCC0805COG220J500BT | 100 | LCSC | 0.0055 | 0.55 | [Link](https://www.lcsc.com/product-detail/C376875.html) |
| 0805B101K500NT | 50 | LCSC | 0.0098 | 0.49 | [Link](https://www.lcsc.com/product-detail/C2838744.html) |
| 0805N270J500CT | 100 | LCSC | 0.0084 | 0.84 | [Link](https://www.lcsc.com/product-detail/C237200.html) |
| RT0805BRD07499KL | 10 | LCSC | 0.0596 | 0.60 | [Link](https://www.lcsc.com/product-detail/C706243.html) |
| MT3608B | 10 | LCSC | 0.1053 | 1.05 | [Link](https://www.lcsc.com/product-detail/C19189893.html) |
| OPA2376AIDR-TP | 2 | LCSC | 0.3457 | 0.69 | [Link](https://www.lcsc.com/product-detail/C42370509.html) |
| REF5050AIDR | 1 | LCSC | 1.0427 | 1.04 | [Link](https://www.lcsc.com/product-detail/C27804.html) |
| OPA192IDBVR | 1 | LCSC | 1.7822 | 1.78 | [Link](https://www.lcsc.com/product-detail/C139648.html) |
| ADS7883SDBVT | 1 | LCSC | 6.2840 | 6.28 | [Link](https://www.lcsc.com/product-detail/C122523.html) |
| PCB | 1 | JLPCB | 2 | 2 |  |
| RP2040-Zero | 1 | AliExpress | $3.90 | $3.90 | [Link](https://www.aliexpress.com/item/1005010768723373.html?spm=a2g0o.cart.0.0.4b8438daNiUA5Y&mp=1&pdp_npi=6%40dis%21USD%21USD%203.90%21USD%203.90%21%21USD%203.90%21%21%21%400b88486a17935424509128878e0ea7%2112000056461341594%21ct%21IT%216215000935%21%211%210%21) |
| MSP2402 | 1 | Aliexpress | $4.80 | $4.80 | [Link](https://it.aliexpress.com/item/1005006173440437.html?spm=a2g0o.cart.0.0.4b8438daNiUA5Y&mp=1&pdp_npi=6%40dis%21USD%21USD%208.57%21USD%204.80%21%21USD%204.80%21%21%21%400b88486a17935424485818824e0ea7%2112000036216232691%21ct%21IT%216215000935%21%211%210%21&gatewayAdapt=glo2ita) |
| BNC | 1 | AliExpress | $6.33 | $6.33 | [Link](https://www.aliexpress.com/item/1005003950007418.html?spm=a2g0o.cart.0.0.4b8438daNiUA5Y&mp=1&pdp_npi=6%40dis%21USD%21USD%206.48%21USD%206.33%21%21USD%206.33%21%21%21%400b88486a17935424485818824e0ea7%2112000027542547180%21ct%21IT%216215000935%21%211%210%21) |
| Shipping cost |  |  | 3 | 3 |  |
<!--END_SECTION:BOM-TABLE-->

This is my DIY oscilloscope, it's not a super advanced one, but you can measure PWM signals with this, in my case i work a lot with servos so it's an useful project, lemme know what you think about it.

# How it works:

My oscilloscope uses an RP2040-ZERO as microcontroller, i use it a lot, it's cheap, it has a lot of GPio pins and its small. Via usb-c to a power source, it transmit its 5V output to the MT3608 module where it become 7V, then these 7V go to the REF5050, where they become a really stable 5V to be used as reference for the ADS7883 (the OPA735's purpose is to get buffed).

The BNC gets its data and they get sent to the Vbias and +IN_A definer (part of the opa2365 module) and they become readeble data for the ADS7883's VIN where they become a 12 bits sequence and become digital , so, readable for the RP2040-ZERO's chip

# Up-view:
<img width="1226" height="927" alt="image" src="https://github.com/user-attachments/assets/996408fc-62c0-4ec3-a0c2-0b5c61d2aefa" />

# Front-view:
<img width="1237" height="782" alt="image" src="https://github.com/user-attachments/assets/f8d1e770-773f-4284-a59c-546274581c9f" />

# PCB-view:
<img width="849" height="714" alt="Immagine 2026-11-01 153140" src="https://github.com/user-attachments/assets/8dfdb3e3-8483-4c6c-9e5a-a60f825dad5d" />

# Schematic-view:
<img width="1057" height="736" alt="Immagine 2026-11-01 153237" src="https://github.com/user-attachments/assets/699409f6-63fa-4f50-a855-d78758a35362" />
