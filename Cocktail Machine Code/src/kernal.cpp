#include "kernal.hpp"

void run(CocktailMachine *machine_p) {
    switch (machine_p->state) {
        case initIngredients:
            //Definitely want to improve this state
            // receive user input for ingredients
            for (int i = 0; i < 4; i++) {
                if (!machine_p->pumps[i].mixer) {
                    //This line might change or be removed by an interupt
                    machine_p->requestMixer(i);
                    break;
                }
            }

            if (!machine_p->liquor) {
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
            //      machine_p->currentCocktail = availableCocktails[i];
            //      machine_p->state = makeDrink;
            // }
            break;
    
        case makeDrink:
            if (!machine_p->stepperFinished) {
                //run stepper for x amount of shots
            } else if (!machine_p->pumpsFinished) {
                machine_p->pumpsFinished = true; //unless proven otherwise
                for (int i = 0; i < 4; i++) {
                    if (!machine_p->pumps[i]->finished) {
                        machine_p->pumpsFinished = false;
                        machine_p->pumps[i]->pumpRun();
                    }
                }
            } else {
                machine_p->state = enjoy;
            }
            break;
        case enjoy:
            //display "enjoy drink"
            //play with neopixel
            //Check loadcell for cup removal
            

    }
}