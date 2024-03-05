# PLAATO Keg

This repository contains documentation and code for the PLAATO Keg for use in open-source projects.  
Please open an issue if there is code or documentation missing.

## Platform.io configuration

This is an excerpt from the original `platformio.ini` file:

```
platform = espressif32@1.11.1
framework = arduino
board = esp32dev

lib_deps =
    ; HX711 id: 1100
    1100@0.7.1
```

The HX711 dependency _might_ need to be changed to `bogde/HX711@0.7.1` and potentially `0.7.5`. See [bogde/HX711](https://github.com/bogde/HX711).

## Hardware

### Pinout overview

![](docs/img/PLAATO%20Keg%20Pinout%20.png "Pinout overview for the PLAATO Keg")

### PCB Flashing Test Pads

#### Keeping factory calibration intact 

To flash new firmware to the PLAATO Keg there are some considerations to take into account. The most important one is to not erase the entire flash when uploading to new firmware as this will remove the factory calibration. If this happens and you use the library [plaato_keg_scale](https://github.com/PLAATO-Technologies/plaato-keg/tree/main/lib/plaato_keg_scale) in your firmware the PLAATO Keg will default back to a default calibration instead of the factory set calibration. The default calibration will likely be less accurate than the factory one, but your PLAATO Keg will still function.

The reason for this is that the factory calibration is stored in Non-Volatile Storage (NVS) which takes up a part of the flash memory. Erasing the entire flash will remove this area. However, if you use the same partition table as the PLAATO Keg currently uses and only write your firmware and the needed boot files during flashing then the NVS will stay intact. You can read more about NVS here: [Non-Volatile Storage Library - ESP32 - — ESP-IDF Programming Guide latest documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/storage/nvs_flash.html)

The easiest way to make sure this happens is to use the same tech stack that we have used develop the PLAATO Keg. The firmware is build with [Arduino core for the ESP32](https://github.com/espressif/arduino-esp32)and [Visual Studio Code](https://code.visualstudio.com/)with the [PlatformIO](https://platformio.org/)plugin. We used the default partition table that looks like this.

| Name    | Type | SubType | Offset   | Size     |
| ------- | ---- | ------- | -------- | -------- |
| nvs     | data | nvs     | 0x9000   | 0x5000   |
| otadata | data | ota     | 0xE000   | 0x2000   |
| app0    | app  | ota_0   | 0x10000  | 0x140000 |
| app1    | app  | ota_1   | 0x150000 | 0x140000 |
| spiffs  | data | spiffs  | 0x290000 | 0x170000 |

The offset value in the table above is the memory address which data is written to. In this case the the factory calibration will be written in the memory space `0x9000` to `0xE000` and as long as this area of the flash memory is not erased or overwritten the calibration work as intented.

With the tech stack above this is the partition table that is used when flashing firmware to an ESP32 by default. However, to be completely sure that this is the case add this line to your platformio.ini file for your project under the`[env]` section:

```
[env]
board_build.partitions = default.csv
```

Using the partition table and using PlatformIO for flashing out of the box there will be written 4 files to the flash memory.

| Name       | Address |
| ---------- | ------- |
| bootloader | 0x1000  |
| partition  | 0x8000  |
| boot_app   | 0xE000  |
| firmware   | 0x10000 |

As you see the bootloader and partition is written before the NVS in the flash memory and the boot_app and firmware are written to the offset addresses we see in the partition table.

#### PCB Testpads for flashing 

When flashing the PLAATO Keg there are four testpads that needs to be used.

1. Boot Mode (GPIO 0) - P20
2. RX (GPIO 3) - P17
3. TX (GPIO 1) - P15
4. GND - P21

![](docs/img/PLAATO%20Keg%20PCB%20Flashing%20Test%20Pads.png "The test pads used for flashing the PCB")

All these four pins need to be connected to a development tool that has a USB Bridge. Normally when using an ESP32 breakout board this chip is on the PCB and you can connect it directly to your computer, but the PLAATO Keg does not have such a chip. There are many such chips you can by online, but we use the [ESP-Prog Board](https://docs.espressif.com/projects/espressif-esp-iot-solution/en/latest/hw-reference/ESP-Prog_guide.html) from Espressif. The board has two sides, the PROG and the JTAG. We will be using the PROG side for flashing. 

![](docs/img/ESP-Prog%20Board%20Layout.png "An overview of the ESP-Prog and its layout")

The Boot Mode pin needs to be pulled low to get the ESP32 in the correct mode to write firmware the flash memory. If you have an ESP32 breakout board this is the same pin as the button that says BOOT as you see on the ESP-Prog. The pins need to be connected as follows:

- P20 -> ESP_IO0
- P17 -> ESP_RXD
- P15 -> ESP_TXD
- P21 -> GND

![](docs/img/ESP-Prog%20Board%20Program%20Interface.png "The pinout overview for the ESP-Prog Program Interface")

Normally to reset the ESP32 to get it into Boot Mode we would connect the ESP_EN to EN on the ESP32 to use the RST button on the ESP-Prog similar to an ESP32 breakout board. However, there is no testpad for this pin on the PCBs. 

To get the same result wire up the ESP-Prog to the testpads as described and connect the ESP-Prog to your computer. Now connect the PLAATO Keg power cable to your computer as well and power the connect while holding the BOOT button on the ESP-Prog down. 

OBS! Both the ESP-Prog and PLAATO Keg needs to be connected to the same computer.

If you have trouble getting the PLAATO Keg to download new firmware to the flash memory try disconnecting and connecting power while holding the BOOT button and PlatformIO is trying to get a connecting. This may require some trial and error has the device was not built to be reflashed like this.

### HX711 Breakout Hookup Guide

For more information about using HX711 you can check out [this guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all).
