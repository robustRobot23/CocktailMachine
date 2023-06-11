#ifndef INGREDIENTS_H
#define INGREDIENTS_H

#define NUMBER_MIXERS 8

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

static std::string Mixers[NUMBER_MIXERS] = {
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

static std::string Liquors[6] = {
    "None",
    "Gin",
    "Vodka",
    "Whiskey",
    "Tequila",
    "Rum"
};

#endif