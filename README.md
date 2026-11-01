# Oscilloscope

<!--START_SECTION:BOM-TABLE-->
<!--END_SECTION:BOM-TABLE-->

This is my DIY oscilloscope, it's not a super advanced one, but you can measure PWM signals with this, in my case i work a lot with servos so it's an useful project, lemme know what you think about it.

# How it works:

My oscilloscope uses an RP2040-ZERO as microcontroller, i use it a lot, it's cheap, it has a lot of GPio pins and its small. Via usb-c to a power source, it transmit its 5V output to the MT3608 module where it become 7V, then these 7V go to the REF5050, where they become a really stable 5V to be used as reference for the ADS7883 (the OPA735's purpose is to get buffed).

The BNC gets its data and they get sent to the Vbias and +IN_A definer (part of the opa2365 module) and they become readeble data for the ADS7883's VIN where they become a 12 bits sequence and become digital , so, readable for the RP2040-ZERO's chip

# Up-view:
<img width="1264" height="773" alt="Immagine 2026-11-01 153215" src="https://github.com/user-attachments/assets/b070e582-5a7c-490d-bc4e-c148bed164ae" />

# Front-view:
<img width="1081" height="927" alt="Immagine 2026-11-01 153210" src="https://github.com/user-attachments/assets/3eb66196-b794-48c7-8d05-8815fa2f914a" />

# PCB-view:
<img width="849" height="714" alt="Immagine 2026-11-01 153140" src="https://github.com/user-attachments/assets/8dfdb3e3-8483-4c6c-9e5a-a60f825dad5d" />

# Schematic-view:
<img width="1057" height="736" alt="Immagine 2026-11-01 153237" src="https://github.com/user-attachments/assets/699409f6-63fa-4f50-a855-d78758a35362" />
