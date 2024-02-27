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

![](docs/img/PLAATO%20Keg%20PCB%20Flashing%20Test%20Pads.png "The test pads used for flashing the PCB")

### HX711 Breakout Hookup Guide

For more information about using HX711 you can check out [this guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all).
