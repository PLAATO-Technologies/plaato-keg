#include "plaato_keg_scale.h"

PlaatoKegScale::PlaatoKegScale() {}

void PlaatoKegScale::measure_weight()
{
    total_weight -= weight_vector.at(array_index);               // Subtract oldest value from total
    weight_vector.at(array_index) = this->get_units(n_samples);  // Replace oldest value newest measurement
    total_weight += weight_vector.at(array_index);               // Add the newest value to total
    array_index = (array_index + 1) % average_window;            // Move pointer to the 'new' oldest value
    total_weight_filtered = total_weight / average_window;       // Get average
    beer_weight = (total_weight_filtered - measureStore.keg_weight);
    beer_weight_kg = float(beer_weight / 10) / 100.0f;           // Convert from grams to kilo grams
}

void PlaatoKegScale::fill_weight_vector_by_measure()
{
    for (int i = 0; i < average_window; i++) {
        this->PlaatoKegScale::measure_weight();
    }
}

void PlaatoKegScale::tare_with_extra_weight(int extra_weight_g, byte times)
{
    double sum = read_average(times) - double(extra_weight_g) * this->get_scale();
    set_offset(sum);
}

void PlaatoKegScale::calibrate(int known_weight_g)
{
    if (known_weight_g > 0) {
        float new_slope = this->get_value(10) / float(known_weight_g);
        this->measureStore.scale_slope = new_slope;
        this->set_scale(new_slope);
    }
    // Does nothing if value is zero. Inform the user or something?
}

int PlaatoKegScale::get_beer_weight()
{
    return this->beer_weight;
}

int PlaatoKegScale::get_beer_weight_last()
{
    return this->beer_weight_last;
}

float PlaatoKegScale::get_beer_weight_kg()
{
    return this->beer_weight_kg;
}

void PlaatoKegScale::update_beer_weight_last()
{
    this->beer_weight_last = this->beer_weight;
}

bool PlaatoKegScale::measure_load()
{
    memset(&measureStore, 0, sizeof(measureStore));
    if (preferences_measure.getBytes("measure", &measureStore, sizeof(measureStore)) == 0) {
        log_e("ERROR: Could not getBytes from preferences");
        return false;
    }
    return true;
}

bool PlaatoKegScale::measure_save()
{
    if (preferences_measure.putBytes("measure", &measureStore, sizeof(measureStore)) == 0) {
        log_e("ERROR: Measure store failed to save");
        return false;
    }
    else {
        log_i("Measure store saved");
        return true;
    }
}

bool PlaatoKegScale::measure_init()
{
    if (!preferences_measure.begin("measure", false)) {
        log_e("ERROR: Measure store failed to begin");
        return false;
    }
    if (measure_load()) {
        log_i("Loaded old measureStore");
        if (this->measureStore.magic != measureDefault.magic) {
            this->measureStore = measureDefault;
            log_w("Magic number does not match. Using default config");
            return false;
        }
        return true;
    }
    else {
        log_i("No measureStore exists. Using default config");
        this->measureStore = measureDefault;
        return false;
    }
}

bool PlaatoKegScale::measure_reset()
{
    log_i("Resetting measure configuration!");
    this->measureStore = measureDefault;
    if (measure_save()) {
        return true;
    }
    else {
        return false;
    }
}

void PlaatoKegScale::set_sensitivity(int averageWindow)
{
    this->average_window = averageWindow;
    weight_vector.resize(average_window);
    total_weight = total_weight_filtered * weight_vector.size();
    for (int i = 0; i < weight_vector.size(); i++) {
        weight_vector.at(i) = total_weight_filtered;
    }
    array_index = 0;
}

unsigned int PlaatoKegScale::get_vector_size()
{
    return weight_vector.capacity();
}
