#include "loadCell.hpp"

void loadCellInit() {
    scale.begin(LOAD_CELL_DATA_PIN, LOAD_CELL_CLOCK_PIN);
}

long weigh() {
    long reading;
    if (scale.is_ready()) {
        reading = scale.read();
        Serial.print("HX711 reading: ");
        Serial.println(reading);
    } else {
        Serial.println("HX711 not found.");
        reading = 0;
    }
    return reading;
}