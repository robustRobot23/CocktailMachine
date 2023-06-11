#ifndef MACHINE_H
#define MACHINE_H

#include "cocktails.hpp"
#include "state.hpp"
#include "pumps.hpp"
#include "ingredients.hpp"

#define TOTAL_NUMBER_COCKTAILS 3


class CocktailMachine {
    public:
    void initAll();
    void initCocktails();
    int findAvailable();
    void requestMixer(int i);
    void run();
    State state;
    Cocktail currentCocktail;

    Pumps* pumps[4];
    Liquor liquor = Empty;

    bool pumpsFinished = false;
    bool stepperFinished = false;

    Cocktail* allCocktails[TOTAL_NUMBER_COCKTAILS];
    Cocktail* availableCocktails[TOTAL_NUMBER_COCKTAILS];

};




#endif