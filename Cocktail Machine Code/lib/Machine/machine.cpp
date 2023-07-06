#include <machine.hpp> 

State state = selectMixers;
State previousState = enjoy;

void Machine::initCocktails() {
    static Cocktail GnT("GnT", Gin, ONE_SHOT, Tonic, THREE_QUARTERS_CUP, None, 0, None, 0, None, 0);
    static Cocktail GinLemonade("Gin and Lemonade", Gin, TWO_SHOTS, Lemonade, HALF_CUP, None, 0, None, 0, None, 0);
    static Cocktail RumCoke("Rum and Coke", Rum, ONE_SHOT, Coke, THREE_QUARTERS_CUP, None, 0, None, 0, None, 0);
    static Cocktail VodkaOG("Vodka and OJ", Vodka, TWO_SHOTS, OrangeJ, THREE_QUARTERS_CUP, None, 0, None, 0, None, 0);
    allCocktails[0] = &GnT;
    allCocktails[1] = &GinLemonade;
    allCocktails[2] = &RumCoke;
    allCocktails[3] = &VodkaOG;
    //Remember to update TOTAL_NUMBER_COCKTAILS when adding a cocktail
}

bool Machine::mixerInPumps(Mixer mixer) {
    bool mixerIsInPumps = false;
    for (int i = 0; i<4; i++) {
        if (mixer == pumps[i]->mixer) {
            mixerIsInPumps = true;
            Serial.print("Mixer: ");
            Serial.print(mixer);
            Serial.println(" ");
        }
    }
    return mixerIsInPumps;
}


bool Machine::mixerAvailable(int i) {
    Cocktail *cocktail = allCocktails[i];
    int noneCount = 0;
    // Goes through each mixer in the cocktail, and checks if it corresponds to a mixer in the pump
    for (int m = 0; m<4; m++) {
        if (cocktail->mixers[m] != None) {
            if(!mixerInPumps(cocktail->mixers[m])) {
                Serial.print(Mixers[m]);
                Serial.println(" not available");
                return false;
            }        
        } else {
            noneCount++;
        }
        Serial.print(Mixers[m]);
        Serial.println(" available");
    }
    if (noneCount >= 4) {
        Serial.println("No mixers in cocktail");
    }
    return true;
    
}

bool Machine::liquorAvailable(int i) {
    Cocktail *cocktail = allCocktails[i];
    if (cocktail->liquor == liquor) {
        Serial.print("Liquor: ");
        Serial.print(liquor);
        Serial.println(" ");
        return true;
    } 
    Serial.println("Liquor not available");
    return false;
}


bool Machine::cocktailAvailable(int i) {
    Cocktail *cocktail = allCocktails[i];
    Serial.print(cocktail->name);
    Serial.println(":");

    if (!liquorAvailable(i) || !mixerAvailable(i)) {
        return false;
    }
    return true;    
}

bool Machine::cocktailInitSuccess() {
    if (numberAvailableCocktails == 0) {
        blynkTerminalPrint("No cocktails can be made, try again");
        Serial.println("No cocktails can be made, try again");
        return false;
    } else if (numberAvailableCocktails > TOTAL_NUMBER_COCKTAILS) {
        setNeopixelColour(RED);
        blynkTerminalPrint("Error: numberAvailableCocktails greater than max");
        Serial.println("Error: numberAvailableCocktails greater than max");
        return false;
    }
    return true;
}

void Machine::findAvailableCocktails() {
    for (int i = 0; i < TOTAL_NUMBER_COCKTAILS; i++) {
        if (cocktailAvailable(i)){
            availableCocktails[numberAvailableCocktails] = allCocktails[i];
            numberAvailableCocktails++;
        }
    }
    setBlynkAvailableCocktails(numberAvailableCocktails);    
}

void Machine::initAll() {
    //possible could start with a welcome state
    pumpsInit(pumps);
    blynkInit();
    neopixelInit();
    loadCellInit();
    stepperInit();
    initCocktails();
    clearDisplay();
}

bool Machine::requestMixer() {

    int mixer_i = blynkRequestMixer();
    bool selected = true;
    if (mixer_i == 0) {
        selected = false;
    }  else {
        mixer_i %= NUMBER_MIXERS; //ensure its in range
        Mixer mixer = static_cast<Mixer>(mixer_i); //Found this on stack overflow. Don't know if this is good practice
        pumps[pumpToInitialise]->mixer = mixer;
    }
    
    return selected;
}

void Machine::requestLiquor() {
    int liquor_i = blynkRequestLiquor();
    liquor = static_cast<Liquor>(liquor_i); //if nothing was selected, liquor = 0 = Empty, state will not change
}

bool Machine::getInitConfirmation() {
    return blynkSelectedConfirmation();
}

bool Machine:: getCocktailConfirmation() {
    return blynkSelectedConfirmation();
}
/// @brief Want to change name to displayMessage or something similar
void Machine::terminalDisplay() {
    if (currentSelection != previousSelection) {
        previousSelection = currentSelection;
        switch(state) {
            case selectMixers:
                blynkTerminalPrint("Mixer: ", Mixers[currentSelection]);
                break;
            case selectLiquor:
                blynkTerminalPrint("Liqour: ", Liquors[currentSelection]);
                break;
            case displayMenu:
                blynkTerminalPrint("Cocktail: ", availableCocktails[currentSelection]->name);
                break;
        }
    }
}

void Machine::resetDisplay() {
    previousCocktailElement = 0;
    currentSelection = 0;
    clearDisplay();
    blynkTerminalPrint("Select Drink");
}

void Machine::clearDisplay() {
    blynkClearDisplay();
    
}

void Machine::updateNeopixelColour() {
    switch (state) {
        case selectMixers:
            setNeopixelColour(ORANGE);
            break;
        case selectLiquor:
            setNeopixelColour(BLUE);
            break;
        case initIngredients:
            setNeopixelColour(LIME);
            break;

        case displayMenu:
            setNeopixelColour(HOT_PINK);
            break;
        
        case makeDrink:
            setNeopixelColour(YELLOW);
            break;
        case enjoy:
            setNeopixelColour(GREEN);
            break;
    }
}

void Machine::resetMachine() {
    stepperFinished = false;

    for (int i = 0; i < 4; i++) {
        pumps[i]->finished = false;
    }

    resetDisplay();

}

void Machine::beginEnjoy() {
    clearDisplay();
    blynkTerminalPrint("Enjoy!");
    enjoyInitialTime = millis();
    finalWeight = loadCellWeigh();
}

void Machine::checkStateChange() {
    if (previousState != state) {
        previousState = state;
        Serial.print("Sate is: ");
        Serial.println(state);
        updateNeopixelColour();
    } 
}


void Machine::run() {
    runBlynk();

    currentSelection = getBlynkCurrentSelection();
    terminalDisplay();
    
    checkStateChange();

    switch (state) {

        /// Yellow status
        case selectMixers:
            static bool selectedMixer = false;

            if (!selectedMixer) {
                selectedMixer = requestMixer();
            } else {
                selectedMixer = false;
                // currentSelection = 0;
                blynkTerminalPrint("Selected: ", Mixers[pumps[pumpToInitialise]->mixer]);
                pumpToInitialise++;
                if (pumpToInitialise >= 4) {
                    for (int i = 0; i < 4; i++) {
                        Serial.print("Mixer ");
                        Serial.print(i);
                        Serial.print(" = ");
                        Serial.println(pumps[i]->mixer);
                    }      
                    state = selectLiquor;
                    selectedMixer = false;
                    currentSelection = 0;
                }
            }
            break;

        /// Blue status 
        case selectLiquor:
            if (!liquor) {
                requestLiquor();
            } else {
                state = initIngredients;
                clearDisplay();
                blynkTerminalPrint("Selected Ingredients: ");
                if (liquor >= 0 && liquor < NUMBER_LIQUORS) {
                    blynkTerminalPrint("Liquor: ", Liquors[liquor]);
                } else {
                    blynkTerminalPrint("Invalid Liquor: ", String(liquor));
                }
                for (int i = 0; i < 4; i++) {
                    if (pumps[i]->mixer >= 0 && pumps[i]->mixer <NUMBER_MIXERS) {
                        blynkTerminalPrint("Mixer: ", Mixers[pumps[i]->mixer]);
                    } else {
                        blynkTerminalPrint("Invalid mixer: ", String(pumps[i]->mixer));
                    }
                }
                blynkTerminalPrint("Ready to proceed?");
                currentSelection = 0;
            }

            break;

        // Lime status
        case initIngredients:
            if (!initConfirmation) {
                initConfirmation = getInitConfirmation();
            } else {
                findAvailableCocktails();
                if (cocktailInitSuccess()) {
                    state = displayMenu;
                    previousSelection = 1;
                    currentSelection = 0;
                    clearDisplay();
                } else {
                    state = selectMixers;
                }
                
            }
            break;

        case displayMenu:
            if (!cocktailSelected) {
                cocktailSelected = getCocktailConfirmation();
            } else {
                state = makeDrink;
                currentSelection = 0;
            }

            break;
            

        case makeDrink:
            if (!stepperFinished) {
                int numberShots = *availableCocktails[currentCocktail]->shots;
                stepperRun(numberShots);
                stepperFinished = true;
            } else if (!pumpsFinished) {
                pumpsFinished = pumpsRun(pumps);  
            } else {
                state = enjoy; 
                enjoyInitialTime = millis();
                enjoyCurrentTime = 0; 
            }
            break;

        case enjoy:
            
            if (enjoyCurrentTime == 0) {
                beginEnjoy();
            }

            enjoyCurrentTime = millis();
            long timePassed = enjoyCurrentTime - enjoyInitialTime;

            if ((finalWeight - loadCellWeigh() >= 100) || timePassed >= FIVE_SECONDS) {
                resetMachine();
                state = displayMenu;
            }
            break;
    }
}