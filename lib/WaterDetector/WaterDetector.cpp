#include "WaterDetector.h"

void WaterDetector::enable(int water_enable_pin)
{
    digitalWrite(water_enable_pin, LOW);  // Water detection circuit is activated when this pin is low
}

void WaterDetector::disable(int water_enable_pin)
{
    digitalWrite(water_enable_pin, HIGH);  // Water detection circuit is activated when this pin is low
}

bool WaterDetector::check_for_water(int water_enable_pin, int water_out_pin)
{
    this->enable(water_enable_pin);
    delay(300);
    bool res = false;
    if (!digitalRead(water_out_pin)) {
        this->water_detected = true;
        res = true;
    }
    else {
        this->water_detected = false;
        res = false;
    }
    this->disable(water_enable_pin);
    return res;
}

bool WaterDetector::check_for_water_without_enable(int water_out_pin)
{
    bool res = false;
    if (!digitalRead(water_out_pin)) {
        this->water_detected = true;
        res = true;
    }
    else {
        this->water_detected = false;
        res = false;
    }
    return res;
}