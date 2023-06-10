#ifndef INGREDIENTS_H
#define INGREDIENTS_H

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

static std::string Mixers[8] = {
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