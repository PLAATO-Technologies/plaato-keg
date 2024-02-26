#pragma once

#include <Arduino.h>
#include <Wire.h>

#define PCT_ADDRESS 0x49

class Pct2075 {
    private:
    float temperature;

    public:
    bool setup(int sda, int scl);
    bool shut_down();
    bool wake_up();
    float get_temperature();
    bool read_temperature();
};

class Pct2075_simulator {
    private:
    float temperature;

    public:
    void setup(int sda, int scl);
    bool shut_down();
    bool wake_up();
    float get_temperature();
    bool read_temperature();
};
