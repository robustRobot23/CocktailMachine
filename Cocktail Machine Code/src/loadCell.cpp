#include "loadCell.hpp"

//need to get a calibration value for set_scale()
void loadCellInit() {
    scale.begin(LOAD_CELL_DATA_PIN, LOAD_CELL_CLOCK_PIN);
    scale.set_scale(2280.f);            // this value is obtained by calibrating the scale with known weights; see the README for details
    scale.tare();				        // reset the scale to 0
    Serial.println("Load Cell Init");
}

long weigh() {
    scale.power_up();

    long reading;
    if (scale.is_ready()) {
        reading = scale.get_units(5);
        Serial.print("HX711 reading: ");
        Serial.println(reading);
    } else {
        Serial.println("HX711 not found.");
        reading = 0;
    }
    scale.power_down();
    return reading;
}