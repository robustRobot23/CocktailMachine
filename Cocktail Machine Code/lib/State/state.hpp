#ifndef STATE_H
#define STATE_H


/// @brief The state enum that controls the FSM in Machine::run()
enum State {
    /// @brief Request user input to assign a mixers to the machine
    /// Entered from: MCU startup or reset
    /// Goes to: selectLiquor
    selectMixers,

    /// @brief Request user input to add a liquor to the machine
    /// Entered from: selectMixers
    /// Goes to: initIngredients
    selectLiquor,

    /// @brief Once ingredients are selected, find what cocktails can be made with these ingredients.
    /// Entered from: selectLiquor.
    /// Goes to: displayMenu
    initIngredients,

    /// @brief Display the available cocktails to the user, and wait for user to select cocktail to make
    /// Entered from: initIngredients, enjoy.
    /// Goes to: makeDrink
    displayMenu,

    /// @brief Run the actuators required to make the drink.
    /// Check the appropriate sensors to confirm drinks is made and recieved.
    /// Raise warning if error (watchdog and loadcell?).
    /// Entered from: displayMenue. 
    /// Goes to: enjoy
    makeDrink,

    /// @brief Final state after making drink. 
    /// Entered from: makeDrink.
    /// Goes to: display menu
    enjoy
};

/// @brief Current state of the machine.
    /// Controls the FSM in Machine::run()
extern State state;


#endif