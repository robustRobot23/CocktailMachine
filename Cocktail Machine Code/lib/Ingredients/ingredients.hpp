#ifndef INGREDIENTS_H
#define INGREDIENTS_H

#define NUMBER_MIXERS 8
#define NUMBER_LIQUORS 6
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

static String Mixers[NUMBER_MIXERS] = {
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

static String Liquors[NUMBER_LIQUORS] = {
    "None",
    "Gin",
    "Vodka",
    "Whiskey",
    "Tequila",
    "Rum"
};

#endif