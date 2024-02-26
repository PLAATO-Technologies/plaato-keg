#pragma once

#include <Arduino.h>

class WaterDetector {
    public:
    bool water_detected = false;

    bool check_for_water(int water_enable_pin, int water_out_pin);
    bool check_for_water_without_enable(int water_out_pin);
    void enable(int water_enable_pin);
    void disable(int water_enable_pin);
};
