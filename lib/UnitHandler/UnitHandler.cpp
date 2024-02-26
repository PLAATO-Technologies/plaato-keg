#include "UnitHandler.h"

// TEMPERATURE
String UnitHandler::get_temp_unit_string()
{
    if (us_customary) {
        return "°F";  // fahrenheit
    }
    else {
        return "°C";  // celsius
    }
}

float UnitHandler::celsius_to_temp(float value)
{
    if (us_customary) {
        return value * 1.8f + 32.0f;  // fahrenheit
    }
    else {
        return value;  // celsius
    }
}

float UnitHandler::temp_to_celsius(float value)
{
    if (us_customary) {
        return (value - 32.0f) / 1.8f;  // fahrenheit
    }
    else {
        return value;  // celsius
    }
}

// Volume and Mass
String UnitHandler::get_volume_unit()
{
    if (us_customary) {
        return " gal";
    }
    else {
        return "L";
    }
}

String UnitHandler::get_small_volume_unit()
{
    if (us_customary) {
        return "oz";
    }
    else {
        return "L";
    }
}

String UnitHandler::get_weight_unit()
{
    if (us_customary) {
        return "lbs";
    }
    else {
        return "kg";
    }
}

float UnitHandler::kg_to_volume(float value)
{
    if (us_customary) {
        return value / fg * 0.264172053;  // gal
    }
    else {
        return value / fg;  // liters
    }
}

float UnitHandler::kg_to_whatever(float value)
{
    if (mass_to_volume) {
        if (us_customary) {
            return value / fg * 0.264172053;  // gal
        }
        else {
            return value / fg;  // liters
        }
    }
    else {
        if (us_customary) {
            return value * 2.2046226218488;  // pounds
        }
        else {
            return value;  // kg
        }
    }
}

float UnitHandler::kg_to_percent(float current_value)
{
    float litres = current_value / fg;
    int percent_left = (litres / keg_volume) * 100;
    if (percent_left > 0) {
        return percent_left;  // Percent
    }
    else {
        return 0;  // Percent
    }
}

float UnitHandler::kg_to_mass(float kg)
{
    if (us_customary) {
        return kg * 2.2046226218488;  // pounds
    }
    else {
        return kg;  // kg
    }
}

float UnitHandler::volume_to_kg(float value)
{
    if (us_customary) {
        return value * fg / 0.264172053;  // gal
    }
    else {
        return value * fg;  // litres
    }
}

float UnitHandler::mass_to_kg(float value)
{
    if (us_customary) {
        return value / 2.2046226218488;  // pounds
    }
    else {
        return value;  // kg
    }
}

int UnitHandler::mass_to_g(float value)
{
    if (us_customary) {
        return (value / 2.2046226218488) * 1000;  // pounds
    }
    else {
        return value * 1000;  // kg
    }
}

float UnitHandler::weight_to_volume(float value)
{
    if (us_customary) {
        return value / 8.345404;  // pounds to gallon based on density of water
    }
    else {
        return value;
    }
}

float UnitHandler::g_to_pour(float value)
{
    if (us_customary) {
        return value * fg * 0.0352739619;  // oz
    }
    else {
        return value * fg / 1000.0f;  // litres
    }
}

void UnitHandler::set_keg_volume(float value)
{
    if (us_customary) {
        keg_volume = value * 3.78541178;
    }
    else {
        keg_volume = value;
    }
}

float UnitHandler::get_keg_volume()
{
    return keg_volume;
}
