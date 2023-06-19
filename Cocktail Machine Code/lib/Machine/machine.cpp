#include <machine.hpp> 

State state = selectMixers;


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
    // int numAvailableCocktails = 0;
    for (int i = 0; i < TOTAL_NUMBER_COCKTAILS; i++) {
        CurrentCocktail = &allCocktails[i];
        if (cocktailAvailable(i)){
            availableCocktails[numberAvailableCocktails] = CurrentCocktail;
            numberAvailableCocktails++;
        }
    }
    // numberAvailableCocktails = numAvailableCocktails;
}

void Machine::initAll() {
    //possible could start with a welcome state
    Pump pump1(PUMP_PIN_1);
    Pump pump2(PUMP_PIN_2);
    Pump pump3(PUMP_PIN_3);
    Pump pump4(PUMP_PIN_4);
    pumps[0] = &pump1;
    pumps[1] = &pump2;
    pumps[2] = &pump3;
    pumps[3] = &pump4;

    blynkInit();
    neopixelInit();
    loadCellInit();
    stepperInit();
    initCocktails();

}

void Machine::requestMixer(int i) {

    int mixer_i = blynkRequestMixer();
    Serial.print("Request Mixer: ");
    Serial.println(mixer_i);
    if (mixer_i != 0) {
        pumps[i]->gotMixer = true;
    }

    mixer_i %= NUMBER_MIXERS; //ensure its in range
    Mixer mixer = static_cast<Mixer>(mixer_i); //eek found this on stack overflow. Don't know if this is good practice
    pumps[i]->mixer = mixer;
}

void Machine::requestLiquor() {
    int liquor_i = blynkRequestLiquor();
    
    liquor = static_cast<Liquor>(liquor_i); //if nothing was selected, liquor = 0 = Empty, state will not change
}

bool Machine::getInitConfirmation() {
    return blynkSelected;
}

bool Machine:: getCocktailConfirmation() {
    return blynkSelected;
}
/// @brief Want to change name to displayMessage or something similar
void Machine::terminalDisplay() {
    switch(state) {
        case selectMixers:
            // String mixing = Mixers[blynkSelectedElement];
            blynkTerminalPrint("Mixer: ", Mixers[blynkCurrentSelection]);
            // terminal.print("Mixer: ");
            // terminal.print(Mixers[blynkCurrentSelection]);
            break;
        case selectLiquor:
            blynkTerminalPrint("Liqour: ", Liquors[blynkCurrentSelection]);

            // terminal.print("Liqour: ");
            // terminal.print(Liquors[blynkCurrentSelection]);
            break;
        case displayMenu:
            blynkTerminalPrint("Cocktail: ", availableCocktails[blynkCurrentSelection]->name);

            // terminal.print("Cocktail: ");
            // terminal.print(availableCocktails[blynkCurrentSelection]->name); 
    }

    // terminal.println();
    // terminal.flush();
}

void Machine::resetDisplay() {
    previousCocktailElement = 0;
    blynkCurrentSelection = 0;
    clearDisplay();
    blynkTerminalPrint("Select Drink");
}

void Machine::clearDisplay() {
    blynkClearDisplay();
    
}

void Machine::run() {
    runBlynk();
    static State previousState = enjoy;
    if (previousState != state) {
        previousState = state;
        Serial.print("Sate is: ");
        Serial.println(state);
    } 
    switch (state) {
        case selectMixers:
            if (!pumps[pumpToInitialise]->gotMixer) {
                requestMixer(pumpToInitialise);
            } else {
                blynkTerminalPrint("Success! ", String(pumpToInitialise));
                pumpToInitialise++;
                if (pumpToInitialise >= 4) {
                    for (int i = 0; i < 4; i++) {
                        Serial.print("Mixer ");
                        Serial.print(i);
                        Serial.print(" = ");
                        Serial.println(pumps[i]->mixer);
                    }
                    state = selectLiquor;
                    blynkCurrentSelection = 0;
                }
            }
            break;

        case selectLiquor:
            if (!liquor) {
                requestLiquor();
            } else {
                state = initIngredients;
                blynkCurrentSelection = 0;
            }

            break;

        case initIngredients:
            if (!initConfirmation) {
                initConfirmation = getInitConfirmation();
            } else {
                state = displayMenu;
                setNeopixelColour(ORANGE);
                terminalDisplay();


            }
            break;

        case displayMenu:
            
            if (previousCocktailElement != blynkCurrentSelection) {
                previousCocktailElement = blynkCurrentSelection;
                terminalDisplay();
            }
            if (!cocktailSelected) {
                cocktailSelected = getCocktailConfirmation();
            } else {
                state = makeDrink;
                blynkCurrentSelection = 0;
                setNeopixelColour(HOT_PINK);
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
                setNeopixelColour(GREEN);
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