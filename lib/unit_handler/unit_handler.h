#pragma once

#include <Arduino.h>

class UnitHandler {
    public:
    // FLAGS
    bool us_customary = false;
    bool mass_to_volume = false;

    // VARIABLES
    // Temperature
    bool temp_notification_sent = false;
    float temp_min = 0.0;
    float temp_max = 30.0;

    // Volume and Mass
    float og = 1.000;
    float fg = 1.000;

    // FUNCTIONS
    // Temperature
    String get_temp_unit_string();
    float celsius_to_temp(float value);
    float temp_to_celsius(float value);

    // Volume and Mass
    float kg_to_volume(float value);
    float kg_to_whatever(float value);
    float kg_to_mass(float value);
    float volume_to_kg(float value);
    float kg_to_percent(float current_value);
    float mass_to_kg(float value);
    int mass_to_g(float value);
    float weight_to_volume(float);
    float g_to_pour(float value);
    void set_keg_volume(float value);
    String get_volume_unit();
    String get_small_volume_unit();
    String get_weight_unit();
    float get_keg_volume();

    private:
    float keg_volume = 20;  // Will always be saved as liters
};