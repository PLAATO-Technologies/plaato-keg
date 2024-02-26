#pragma once

#include "HX711.h"  // Strongly dependent on this library
#include <Preferences.h>
#include <vector>

#define MEASURE_STORE_VERSION "1.0.0"

struct MeasureStore {
    uint32_t magic;
    char version[9];
    uint16_t keg_weight;
    uint16_t one_pour;
    float max_keg_kg;
    int32_t scale_offset;
    float scale_slope;
    float factory_scale_slope;  // Should only be set in test mode
    bool us_customary;          // false is metric. True is imperial
    bool mass_to_volume;        // If we should convert weight as volume or not
    float temperature_offset;   // Temperature offset as celsius
    uint16_t checksum;
} __attribute__((packed));

const MeasureStore measureDefault = {
    0x4444444,
    MEASURE_STORE_VERSION,
    0,
    300,
    20.0,
    217687,
    -44.0,
    -44.0,
    false,
    false,
    0,
    0
};

class Plaato_beer_scale : public HX711 {
    private:
    int average_window;

    int total_weight;
    int total_weight_filtered;
    int array_index = 0;
    std::vector<int> weight_vector;
    int beer_weight;
    int beer_weight_last;
    float beer_weight_kg = 0;
    int n_samples = 1;

    Preferences preferences_measure;

    bool measure_load();

    public:
    MeasureStore measureStore;

    // Constructors
    Plaato_beer_scale();

    // Gets
    int get_beer_weight();
    int get_beer_weight_last();
    float get_beer_weight_kg();
    unsigned int get_vector_size();

    // Sets
    void update_beer_weight_last();  // beer_weight_last = beer_weight;

    void measure_weight();
    void fill_weight_vector_by_measure();
    void calibrate(int);
    void set_n_samples();
    void tare_with_extra_weight(int extra_weight, byte times = 10);

    // Measure store functions
    bool measure_save();
    bool measure_init();
    bool measure_reset();

    void set_sensitivity(int);
};