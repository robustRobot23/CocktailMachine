#ifndef COCKTAILS_H
#define COCKTAILS_H

#include <Arduino.h>
#include <string>

/*
 * Need to add pumps class or struct
 * Currently thinking a struct will be better
 * 
 */


enum Mixer {
    None,
    Tonic,
    Lemonade,
    Coke,
    OrangeJ,
    Prosseco,
    PeachSchapps,
    RasberryCordial
};

std::string Mixers[8] = {
    "None",
    "Tonic",
    "Lemonade",
    "Coke",
    "Orange Juice",
    "Prosseco",
    "Peach Schapps",
    "Rasberry Cordial"
};

enum Liquor {
    Empty,
    Gin,
    Vodka,
    Whiskey,
    Tequila,
    Rum
};

std::string Liquors[6] = {
    "None",
    "Gin",
    "Vodka",
    "Whiskey",
    "Tequila",
    "Rum"
};



class CocktailHandling {
    public:
    void pumpOn(int pump, long int startTime);
    // Allows the code to continue running and periodically check if current < startTime + duration
    bool checkPump(int pump, long int duration);

    private:
    long int pump1Start;
    long int pump2Start;
    long int pump3Start;
    long int pump4Start;

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