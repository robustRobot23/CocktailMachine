#include "machine.hpp" 

void CocktailMachine::initCocktails() {
    Cocktail GnT(Gin, ONE_SHOT, Tonic, THREE_QUARTERS_CUP, None, 0, None, 0, None, 0);
    Cocktail GinLemonade(Gin, TWO_SHOTS, Lemonade, HALF_CUP, None, 0, None, 0, None, 0);
    Cocktail RumCoke(Rum, ONE_SHOT, Coke, THREE_QUARTERS_CUP, None, 0, None, 0, None, 0);

    allCocktails[0] = *GnT;
    allCocktails[1] = *GinLemonade;
    allCocktails[2] = *RumCoke;
}

bool CocktailMachine::cocktailAvailable(Cocktail *cocktail) {
    bool available;
    for (int m = 0; m < 4, m++){
        available = false;
        for (int possibleMixer = 0; possibleMixer < NUMBER_MIXERS; possibleMixer++)
            if (cocktail->mixers[m] == possibleMixer) {
                available true;
                break;
            }
        if (!available) {
            break;
        }
    }
    return available;
}

int CocktailMachine::findAvailable() {

    Cocktail *ptrCurrentCocktail;
    int numAvailableCocktails = 0;
    for (int i = 0; i < TOTAL_NUMBER_COCKTAILS; i++) {
        ptrCurrentCocktail = allCocktails[i];
        if (cocktailAvailable(ptrCurrentCocktail)){
            availableCocktails[numAvailableCocktails++] = ptrCurrentCocktail;
        }
    }
    return numAvailableCocktails;
}

void CocktailMachine::initAll() {
    
    pumps[0] = Pumps pump1(PUMP_PIN_1);
    pumps[1] = Pumps pump2(PUMP_PIN_2);
    pumps[2] = Pumps pump3(PUMP_PIN_3);
    pumps[3] = Pumps pump4(PUMP_PIN_4);
    
}

void CocktailMachine::requestMixer(int i) {
    //display that we need mixer #i??
    //
}