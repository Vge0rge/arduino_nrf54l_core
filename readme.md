# (Very) Unofficial arduino core for nRF54L15

> [!IMPORTANT]
>
> This is a personal hobby project and it is not sponsored or supported by Nordic Semiconductor or any other other entity.

This is a first attempt to port the nRF54L15 to support the Arduino framework. This project is in very early stages of development. It is a personal project driven by my curiosity to understand how the Arduino cores work.

The core uses the official Nordic nrfx library for most of the provided functionality.

At the moment the following features work:

* Digital and analog pin control
* Random number generation
* UART

Archives used:

* ARM Zephyr toolchain
* Arduino core API
* Nordic NRFX library
* Pyocd

The versions of the external tools/libraries are described in the zip file and in the json file.

### Supported boards:

* Official nrf54L15 DK

## Installation

1. [Download and install the Arduino IDE](https://www.arduino.cc/en/Main/Software) (Tested with version 2.3.6)
2. Start the Arduino IDE
3. Go into Preferences
4. Add "https://raw.githubusercontent.com/Vge0rge/arduino_nrf54l_core/refs/heads/main/package_nrf54l15_boards_index.json" as an 'Additional Board Manager URL'
5. Restart the Arduino IDE
6. Open the Boards Manager from the Tools -> Board menu and install 'Nordic nRF54L15 Boards'
7. Once the BSP is installed, select 'Official nRF54L15 DK' from the Tools -> Board menu.

## Credits

Multiple existed cores used as a reference point to create this core. In the case of any files being copied the copyrights are kept intact.

* https://github.com/arduino/ArduinoCore-mbed
* https://github.com/sandeepmistry/arduino-nRF5
* https://github.com/arduino/ArduinoCore-samd
* https://github.com/adafruit/Adafruit_nRF52_Arduino
* https://github.com/pdcook/nRFMicro-Arduino-Core

Also there are two additional projects that helped this effort:

* https://git.trustedfirmware.org/TF-M/trusted-firmware-m.git
* https://github.com/ARM-software/CMSIS_6
