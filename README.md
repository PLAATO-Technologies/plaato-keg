# Open PLAATO Keg

## Original Platform.io configuration

This is an excerpt from the original `platformio.ini` file

```
platform = espressif32@1.11.1
framework = arduino
board = esp32dev

lib_deps =
    ; HX711 id: 1100 - might need to update to 'bogde/HX711@0.7.1' or 0.7.5
    1100@0.7.1
```

## Hardware

### Pinout overview

![](docs/img/PLAATO%20Keg%20Pinout%20.png "Pinout overview for the PLAATO Keg")

### PCB Flashing Test Pads

![](docs/img/PLAATO%20Keg%20PCB%20Flashing%20Test%20Pads.png "The test pads used for flashing the PCB")