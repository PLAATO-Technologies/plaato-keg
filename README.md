# PLAATO Keg OS

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

The dependency for HX711 _might_ need to be updated to `bogde/HX711@0.7.1` and potentially `0.7.5`.

## Hardware

### Pinout overview

![](docs/img/PLAATO%20Keg%20Pinout%20.png "Pinout overview for the PLAATO Keg")

### PCB Flashing Test Pads

![](docs/img/PLAATO%20Keg%20PCB%20Flashing%20Test%20Pads.png "The test pads used for flashing the PCB")
