#include "pct2075.h"

// Sets up I2C wire for the tmp102
bool Pct2075::setup(int sda, int scl)
{
    return Wire.begin(sda, scl);
}

bool Pct2075::shut_down()
{
    Wire.beginTransmission(PCT_ADDRESS);
    Wire.write(0x01);  // Set register pointer to 01h conf
    Wire.write(0x01);  // Set B0 register to 1 to enable shutdown
    if (Wire.endTransmission() == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool Pct2075::wake_up()
{
    Wire.beginTransmission(PCT_ADDRESS);
    Wire.write(0x01);  // Set register pointer to 01h conf
    Wire.write(0x00);  // Set B0 register to 0 to wake up
    if (Wire.endTransmission() == 0) {
        return true;
    }
    else {
        return false;
    }
}

float Pct2075::get_temperature()
{
    return this->temperature;
}

bool Pct2075::read_temperature()
{
    Wire.beginTransmission(PCT_ADDRESS);
    Wire.write(0x00);  // Set pointer to scratch
    if (Wire.endTransmission() != 0) {
        return false;
    }
    Wire.requestFrom(PCT_ADDRESS, 2);
    byte MSB = Wire.read();
    byte LSB = Wire.read();

    if (Wire.endTransmission()) {
        // It's a 11bit int, using two's compliment for negative
        int TemperatureSum = ((MSB << 3) | (LSB >> 5));
        float TempC = TemperatureSum * 0.125;
        if (TempC > 128) {
            TempC = TempC - 256;  // for negative temperatures
        }
        this->temperature = TempC;
        return true;
    }
    else {
        return false;
    }
}

// Sets up I2C wire for the tmp102
void Pct2075_simulator::setup(int sda, int scl)
{
    (void)sda;
    (void)scl;
    randomSeed(analogRead(0));
}

bool Pct2075_simulator::shut_down()
{
    return true;
}

bool Pct2075_simulator::wake_up()
{
    return true;
}

float Pct2075_simulator::get_temperature()
{
    return this->temperature;
}

bool Pct2075_simulator::read_temperature()
{
    this->temperature = 18.0 + float(random(50)) / 10.0;
    return true;
}
