#ifndef COCKTAILS_H
#define COCKTAILS_H

#include <Arduino.h>
#include <string>
#include "ingredients.hpp"
/*
 * Need to add pumps class or struct
 * Currently thinking a struct will be better
 * 
 */




class CocktailHandling {
    public:
    // Allows the code to continue running and periodically check if current < startTime + duration
    // bool checkPump(int pump, long int duration);

    private:


};


class Cocktails {
    public: 
    // Initialise the cocktails ingredients when the class is created
    Cocktails(Liquor l, Mixer m1, int mL1, Mixer m2, int mL2, Mixer m3, int mL3, Mixer m4, int mL4);

    private:
    Liquor liquor;

    Mixer mixerOne;
    Mixer mixerTwo;
    Mixer mixerThree;
    Mixer mixerFour;

    int volumeOne;
    int volumeTwo;
    int volumeThree;
    int volumeFour;
};

#endif  