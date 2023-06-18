#ifndef LOAD_CELL
#define LOAD_CELL

#include <Arduino.h>
#include "pinDefinitions.hpp"
#include "HX711.h"


void loadCellInit();
long loadCellWeigh();

#endif