#include "pumps.hpp"

Pumps::Pumps(int p) {
    pin = p;
}

void Pumps::initPump() {
    pinMode(pin, OUTPUT);
}

void Pumps::resetPump() {
    startTime = 0;
    finished = false;
    pumpDuration = milliLitre * MILLISECONDS_PER_MILLILITER;
}

void Pumps::pumpRun() {
    if (startTime == 0) { //pump hasn't run yet
        startTime = millis();
    }
    if (millis() - startTime >= pumpDuration) {
        digitalWrite(pin, LOW);
        finished = true;
    }
}