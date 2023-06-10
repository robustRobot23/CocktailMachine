#include <Arduino.h>
#include "kernal.hpp"

CocktailMachine machine;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  machine.initAll();
}

void loop() {
  run(*machine);
}
