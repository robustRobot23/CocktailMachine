#ifndef COCKTAILS_H
#define COCKTAILS_H

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

char* Mixers[] = {
    "None",
    "Tonic",
    "Lemonade",
    "Coke",
    "Orange Juice",
    "Prosseco",
    "Peach Schapps",
    "Rasberry Cordial"
};

enum Liqour {
    None,
    Gin,
    Vodka,
    Whiskey,
    Tequila,
    Rum
};

char* Liquors[] = {
    "None",
    "Gin",
    "Vodka",
    "Whiskey",
    "Tequila",
    "Rum"
};



class CocktailHandling {
    public:
    // Allows the code to continue running and periodically check if current < startTime + duration
    void PumpOnTime(int pump, long int startTime, long int duration);
    bool getStatus(int pump);

    
};


class Cocktails {
    public: 
    // Initialise the cocktails ingredients when the class is created
    Cocktails(Liqour liqour, Mixer mixerOne, Mixer mixerTwo, Mixer mixerThree, Mixer MixerFour);
};

#endif  