#include "pumps.hpp"



Pump::Pump(int p) {
    pin = p;
    pinMode(pin, OUTPUT);
}

void Pump::resetPump() {
    startTime = 0;
    finished = false;
    pumpDuration = milliLitre * MILLISECONDS_PER_MILLILITER;
}

/// @brief "Run the pump until the time is up"
void Pump::pumpRun() {
    if (startTime == 0) { //pump hasn't run yet
        startTime = millis();
        digitalWrite(pin, HIGH);
    }
    if (millis() - startTime >= pumpDuration) {
        digitalWrite(pin, LOW);
        finished = true;
    }
}

void pumpsInit(Pump *pumps[]) {
    static Pump pump1(PUMP_PIN_1);
    static Pump pump2(PUMP_PIN_2);
    static Pump pump3(PUMP_PIN_3);
    static Pump pump4(PUMP_PIN_4);
    pumps[0] = &pump1;
    pumps[1] = &pump2;
    pumps[2] = &pump3;
    pumps[3] = &pump4;
}

bool pumpsRun(Pump *pumps[4]) {
    bool pumpsFinished = true;
    for (int i = 0; i < 4; i++) {
        if (!pumps[i]->finished) {
            pumpsFinished = false;
            pumps[i]->pumpRun();
        }
    }
    return pumpsFinished;
}