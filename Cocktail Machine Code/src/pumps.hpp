#ifndef PUMPS_H
#define PUMPS_H

#include <Arduino.h>
#include "pinDefinitions.hpp"
#include "ingredients.hpp"

#define MILLISECONDS_PER_MILLILITER 100

class Pumps {
    public:
    Pumps(int p);
    void resetPump();
    void pumpRun();

    Mixer mixer = None;
    int milliLitre = 0;
    bool finished = true;

    private:
    int pin;

    long int startTime = 0;
    long int pumpDuration = 0;
};



#endif