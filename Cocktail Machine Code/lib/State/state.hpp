#ifndef STATE_H
#define STATE_H


/// @brief The state enum that controls the FSM in Machine::run()
enum State {

    selectMixers,
    selectLiquor,
    /// @brief Request user input to assign a mixer to the pumps, and a liquor to the stepper motor.
    /// Once ingredients are selected, find what cocktails can be made with these ingredients.
    /// Entered from: MCU startup/reset.
    /// Next state: displayMenu
    initIngredients,

    /// @brief Display the available cocktails to the user, and wait for user to select cocktail to make
    /// Entered from: initIngredients, enjoy.
    /// Next state: makeDrink
    displayMenu,

    /// @brief Run the actuators required to make the drink.
    /// Check the appropriate sensors to confirm drinks is made and recieved.
    /// Raise warning if error (watchdog and loadcell?).
    /// Entered from: displayMenue. 
    /// Next state: enjoy
    makeDrink,

    /// @brief Final state after making drink. 
    /// Entered from: makeDrink.
    /// Next state: display menu
    enjoy
};

/// @brief Current state of the machine.
    /// Controls the FSM in Machine::run()
State state;


#endif