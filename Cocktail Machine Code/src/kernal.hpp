#ifndef KERNAL_H
#define KERNAL_H

//May move this into the machine module

#include <Arduino.h>
#include "cocktails.hpp"
#include "machine.hpp"
#include "state.hpp"


void run(CocktailMachine *machine_p);
#endif