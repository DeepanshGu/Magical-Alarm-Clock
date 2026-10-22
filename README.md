<img width="679" height="290" alt="clockfrontview" src="https://github.com/user-attachments/assets/46b911ab-0617-4695-add1-5466e9c9078e" />
<img width="946" height="535" alt="Screenshot 2026-09-21 210639" src="https://github.com/user-attachments/assets/7a893350-c244-4f65-ae27-093fbaa9ad06" />

# Magical Alarm Clock

A custom-built alarm clock featuring an ST7789 display, XIAO ESP32-C3 microcontroller, 
4 physical buttons, and a buzzer — designed from scratch as part of Hack Club's 
[BLARE](https://blare.hackclub.com/) program.

Built entirely with KiCad (schematic + PCB), Fusion 360 (enclosure), and Arduino IDE (firmware).

## Features

- Real-time clock display on a 284x76 ST7789 TFT screen
- Set the current time manually using onboard buttons (fully offline — no WiFi/NTP required)
- Set, enable, and disable a daily alarm
- Buzzer sounds when the alarm triggers, silenced with a button press
- Fully custom 2-layer PCB — no breadboard or dev-kit shield required
- 3D-printable enclosure designed in Fusion 360

## Hardware

| Component | Notes |
|---|---|
| Seeed XIAO ESP32-C3 | Main microcontroller |
| ST7789 TFT Display | 284x76 resolution (unusual — not the standard 240x320) |
| 4x Push Buttons | Mode / Increment / Decrement / Alarm toggle |
| Buzzer | Alarm sound output |
| Custom PCB | 2-layer, designed in KiCad |

## Bill of Materials

| Part | Qty | Unit Price (USD) | Link | Notes |
| :--- | :---: | :---: | :--- | :--- |
| Seeed XIAO ESP32-C3 | 1 | $5.49 | [Seeed Studio](https://www.seeedstudio.com/XIAO-ESP32C3-p-5431.html) | Main microcontroller |
| 2.25" TFT 76x284 SPI Display (ST7789P3) | 1 | $2.50 | [BuyDisplay](https://www.buydisplay.com/chinese/2-25-inch-tft-serial-spi-76x284-lcd-display-module-w-st7789p3) | Non-standard resolution match |
| Tactile Push Button Switch 6x6mm (pack of 20) | 1 | $2.50 | [Adafruit](https://www.adafruit.com/product/367) | Only 4 needed per clock; pack covers spares |
| 5V Piezo Buzzer | 1 | $0.95 | [Adafruit](https://www.adafruit.com/products/1536) | Breadboard-friendly; no driver circuit needed |
| M3 Brass Heat-Set Inserts (pack of 50) | 1 | $5.95 | [Adafruit](https://www.adafruit.com/product/4256) | Only 4 needed per clock; pack covers spares |
| M3 Screws (6-8mm length) | 4 | ~$0.10 each | — | Widely available individually at hardware store |
| Custom PCB | 1 | ~$8.20 (for 5) | — | JLCPCB quote for 2-layer 75x107mm board |
| **Total Estimated Cost** | — | **~$25.99** | — | **Includes single-unit parts & bulk packs/PCBs** |


## Repository Structure


## Building the PCB

1. Open the KiCad project files in the `/pcb` folder.
2. Gerber and drill files are included for direct upload to a fabrication service (e.g. JLCPCB).
3. Board is a standard 2-layer FR-4 PCB.
   <img width="1210" height="844" alt="Screenshot 2026-10-22 150021" src="https://github.com/user-attachments/assets/f2b3b936-60f5-4914-aa4a-ffefa43b92f7" />



## Firmware Setup

1. Install [Arduino IDE](https://www.arduino.cc/en/software).
2. Add ESP32 board support via Boards Manager.
3. Install these libraries via Library Manager:
   - `Adafruit ST7735 and ST7789`
   - `Adafruit GFX`
4. Open `/firmware/magical_alarm_clock.ino`.
5. Update the GPIO pin definitions at the top of the file to match your wiring.
6. Select **XIAO_ESP32C3** as the board, choose the correct COM port, and upload.

## Enclosure

The case was designed in Fusion 360 around the PCB and display's real dimensions, 
with support posts for heat-set inserts and a cutout for the display and buttons. 
STEP files are available in `/enclosure`.

## Credits

- Built following the [BLARE](https://blare.hackclub.com/) guide by Liam Newbill, part of Hack Club's Stardance program.
- Designed and built by [Deepansh Gupta](https://github.com/DeepanshGu).

## License

*No license added yet.*
