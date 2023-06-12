#include <machine.hpp> 

/// @brief Initialises all cocktails
void Machine::initCocktails() {
    Cocktail GnT("GnT", Gin, ONE_SHOT, Tonic, THREE_QUARTERS_CUP, None, 0, None, 0, None, 0);
    Cocktail GinLemonade("Gin and Lemonade", Gin, TWO_SHOTS, Lemonade, HALF_CUP, None, 0, None, 0, None, 0);
    Cocktail RumCoke("Rum and Coke", Rum, ONE_SHOT, Coke, THREE_QUARTERS_CUP, None, 0, None, 0, None, 0);

    allCocktails[0] = GnT;
    allCocktails[1] = GinLemonade;
    allCocktails[2] = RumCoke;
}

bool Machine::cocktailAvailable(int i) {
    Cocktail *cocktail = availableCocktails[i];
    bool available;
    for (int m = 0; m < 4; m++){
        available = false;
        for (int possibleMixer = 0; possibleMixer < NUMBER_MIXERS; possibleMixer++)
            if (cocktail->mixers[m] == possibleMixer) {
                available = true;
                break;
            }
        if (!available) {
            break;
        }
    }
    return available;
}

void Machine::findAvailable() {

    Cocktail *CurrentCocktail;
    int numAvailableCocktails = 0;
    for (int i = 0; i < TOTAL_NUMBER_COCKTAILS; i++) {
        CurrentCocktail = &allCocktails[i];
        if (cocktailAvailable(i)){
            availableCocktails[numAvailableCocktails++] = CurrentCocktail;
        }
    }
    numberAvailableCocktails = numAvailableCocktails;
}

void Machine::initAll() {
    Pump pump1(PUMP_PIN_1);
    Pump pump2(PUMP_PIN_2);
    Pump pump3(PUMP_PIN_3);
    Pump pump4(PUMP_PIN_4);
    pumps[0] = &pump1;
    pumps[1] = &pump2;
    pumps[2] = &pump3;
    pumps[3] = &pump4;
}

void Machine::requestMixer(int i) {
    int mixer_i = getBlynkSelection(&Mixers);
    mixer_i %= NUMBER_MIXERS; //ensure its in range
    Mixer mixer = static_cast<Mixer>(mixer_i); //eek found this on stack overflow. Don't know if this is good practice
    pumps[i]->mixer = mixer;
}


void Machine::run() {
    switch (state) {
        case initIngredients:
            //Definitely want to improve this state
            // receive user input for ingredients
            for (int i = 0; i < 4; i++) {
                if (!pumps[i]->mixer) {
                    //This line might change or be removed by an interupt
                    requestMixer(i);
                    break;
                }
            }

            if (!liquor) {
                //request liquor
            } else { //all has been initialised
                //create list of available pumps
                // if (completeSelection()) {
                //     
                //     state = displayMenu;
                // }
            }

            break;

        case displayMenu:

        //psuedocode ish
            // OLED.display(availableCocktails[i])

            // if (cocktailSelected) {
                //  currentCocktail = i;
            //      state = makeDrink;
            // }
            break;

        case makeDrink:
            if (!stepperFinished) {
                //run stepper for x amount of shots
            } else if (!pumpsFinished) {
                pumpsFinished = true; //unless proven otherwise
                for (int i = 0; i < 4; i++) {
                    if (!pumps[i]->finished) {
                        pumpsFinished = false;
                        pumps[i]->pumpRun();
                    }
                }
            } else {
                state = enjoy;
            }
            break;
        // case enjoy:
        //     //display "enjoy drink"
        //     //play with neopixel
        //     //Check loadcell for cup removal
        //     break;

    }
}