#include <machine.hpp> 

State state = selectMixers;


void Machine::initCocktails() {
    static Cocktail GnT("GnT", Gin, ONE_SHOT, Tonic, THREE_QUARTERS_CUP, None, 0, None, 0, None, 0);
    static Cocktail GinLemonade("Gin and Lemonade", Gin, TWO_SHOTS, Lemonade, HALF_CUP, None, 0, None, 0, None, 0);
    static Cocktail RumCoke("Rum and Coke", Rum, ONE_SHOT, Coke, THREE_QUARTERS_CUP, None, 0, None, 0, None, 0);
    static Cocktail VodkaOG("Vodka and OJ", Vodka, TWO_SHOTS, OrangeJ, THREE_QUARTERS_CUP, None, 0, None, 0, None, 0);
    allCocktails[0] = &GnT;
    allCocktails[1] = &GinLemonade;
    allCocktails[2] = &RumCoke;

    
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
    // int numAvailableCocktails = 0;
    for (int i = 0; i < TOTAL_NUMBER_COCKTAILS; i++) {
        CurrentCocktail = allCocktails[i];
        if (cocktailAvailable(i)){
            availableCocktails[numberAvailableCocktails] = CurrentCocktail;
            numberAvailableCocktails++;
        }
    }
    if (numberAvailableCocktails == 0) {
        blynkTerminalPrint("No cocktails can be made, try again");
        state = selectMixers;
    }
    // numberAvailableCocktails = numAvailableCocktails;
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

bool Machine::requestMixer(int currentPump) {

    int mixer_i = blynkRequestMixer();
    bool selected = true;
    if (mixer_i == 0) {
        // pumps[currentPump]->gotMixer = true;
        selected = false;
    }
    mixer_i %= NUMBER_MIXERS; //ensure its in range
    Mixer mixer = static_cast<Mixer>(mixer_i); //Found this on stack overflow. Don't know if this is good practice
    pumps[currentPump]->mixer = mixer;
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
    return blynkSelected;
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

void Machine::run() {
    runBlynk();
    currentSelection = getBlynkCurrentSelection();
    static int ticks = 0;
    if (ticks >= 50000) {
        ticks = 0;
        Serial.print("currentSelection: ");
        Serial.println(currentSelection);
    }
    ticks++;
    terminalDisplay();
    

    static State previousState = enjoy;
    if (previousState != state) {
        previousState = state;
        Serial.print("Sate is: ");
        Serial.println(state);
        updateNeopixelColour();
    } 

    switch (state) {
        /// Yellow status
        
        case selectMixers:
        static bool selectedMixer = false;
            // if (!pumps[pumpToInitialise]->gotMixer) {
            if (!selectedMixer) {
                selectedMixer = requestMixer(pumpToInitialise);
            } else {
                selectedMixer = false;
                currentSelection = 0;
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
                state = displayMenu;
                previousSelection = 1;
                currentSelection = 0;
                clearDisplay();
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
                //run stepper for x amount of shots
                stepperRun(*availableCocktails[currentCocktail]->shots);
                stepperFinished = true;

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
        case enjoy:
            
            static long initialTime = millis();
            static long currentTime = 0;

            if (currentTime == 0) {
                clearDisplay();
                blynkTerminalPrint("Enjoy!");
                initialTime = millis();
                finalWeight = loadCellWeigh();
            }
            if ((finalWeight - currentWeight >= 100)||currentTime - initialTime >= FIVE_SECONDS) {
                currentTime = 0;
                resetDisplay();
                setNeopixelColour(ORANGE);
                state = displayMenu;
            }
            currentTime = millis();
            break;
    }
}