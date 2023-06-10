#ifndef COCKTAILS_H
#define COCKTAILS_H

#include <Arduino.h>
#include <string>
#include "ingredients.hpp"

#define ONE_SHOT            1
#define TWO_SHOTS           2
#define THREE_SHOTS         3

#define THREE_QUARTERS_CUP  188
#define HALF_CUP            125 
#define THIRD_CUP           83 
#define QUATER_CUP          63 

class Cocktail {
    public: 
    // Initialise the cocktails ingredients when the class is created
    Cocktail(Liquor l, int s; Mixer m1, int mL1, Mixer m2, int mL2, Mixer m3, int mL3, Mixer m4, int mL4);

    private:
    Liquor liquors[1];
    int shots[1];

    Mixer mixers[4];
    int mixerVolumes[4];
};

#endif  