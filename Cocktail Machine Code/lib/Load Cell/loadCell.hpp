#ifndef LOAD_CELL
#define LOAD_CELL

#include <Arduino.h>
#include "pinDefinitions.hpp"
#include "HX711.h"

HX711 scale;

void loadCellInit();
long weigh();

#endif