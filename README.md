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

## Repository Structure


## Building the PCB

1. Open the KiCad project files in the `/pcb` folder.
2. Gerber and drill files are included for direct upload to a fabrication service (e.g. JLCPCB).
3. Board is a standard 2-layer FR-4 PCB.

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
