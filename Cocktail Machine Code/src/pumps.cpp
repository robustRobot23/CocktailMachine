#include "pumps.hpp"

Pumps::Pumps(int p) {
    pin = p;
    pinMode(pin, OUTPUT);
}

void Pumps::resetPump() {
    startTime = 0;
    finished = false;
    pumpDuration = milliLitre * MILLISECONDS_PER_MILLILITER;
}

/// @brief "Run the pump until the time is up"
void Pumps::pumpRun() {
    if (startTime == 0) { //pump hasn't run yet
        startTime = millis();
        digitalWrite(pin, HIGH);
    }
    if (millis() - startTime >= pumpDuration) {
        digitalWrite(pin, LOW);
        finished = true;
    }
}