#ifndef MACHINE_H
#define MACHINE_H

#include <cocktails.hpp>
#include <pumps.hpp>
#include <ingredients.hpp>
#include <Arduino.h>
#include <myBlynk.hpp>
#include <state.hpp>
#include <stepper.hpp>
#include <loadCell.hpp>
#include <neopixel.hpp>

#define TOTAL_NUMBER_COCKTAILS 4
#define FIVE_SECONDS 5000


/// @brief Class that controls the machines state and drink making
class Machine {
    public:
    /// @brief Method to initialise all periferals on the machine.
    /// Called on startup
    void initAll();

    /// @brief Method to create cocktail objects to populate 'allCocktails' array
    void initCocktails();

    
    bool mixerInPumps(Mixer mixer);
    bool mixerAvailable(int i);
    bool liquorAvailable(int i);

    
    /// @brief Checks if the given cocktail is able to be made from the current mixers and liquor
    /// @param i The element in the 'allCocktails' array to check
    /// @return Cocktail available bool
    bool cocktailAvailable(int i);

    /// @brief Method to find all available cocktails from 'allCocktails' array
    void findAvailableCocktails();
    bool cocktailInitSuccess();
    bool requestMixer();
    void requestLiquor();
    bool getInitConfirmation();
    bool getCocktailConfirmation();
    void terminalDisplay();
    void resetDisplay();
    void clearDisplay();
    void updateNeopixelColour();
    void resetMachine();
    void beginEnjoy();
    void checkStateChange();
    /// @brief The main FSM of the machine. Calls all peripherals when needed
    void run();

    /// @brief The element of the current cocktail in the 'availabileCocktails' array
    int currentCocktail;
    int previousCocktailElement = 0;
    bool cocktailSelected;

    int numberAvailableCocktails = 0;
    int currentSelection = 0;
    int previousSelection = 1;
    // int numberAvailableCocktails;

    long cupWeight = 0;
    long currentWeight = 0;
    long finalWeight = 0;
    
    /// @brief The array of all cocktails in the world
    Cocktail *allCocktails[TOTAL_NUMBER_COCKTAILS];

    /// @brief The array of the cocktails the machine can currently make
    Cocktail* availableCocktails[TOTAL_NUMBER_COCKTAILS];

    /// @brief An array of pointers to the 4 Pump objects.
    /// Contains pump operation methods and pump status
    Pump* pumps[4];

    int pumpToInitialise = 0;
    bool initConfirmation = false;

    /// @brief The liqour in the machine
    Liquor liquor = Empty;

    /// @brief Flag raised when all pumps have finished dispensing mixers.
    /// Reset before making new cocktail
    bool pumpsFinished = false;

    /// @brief Flag raised when stepper motor has finished dispensing liquor.
    /// Reset before making new cocktail
    bool stepperFinished = false;
    //enjoy variables
    long enjoyInitialTime = 0;
    long enjoyCurrentTime = 0;

};




#endif