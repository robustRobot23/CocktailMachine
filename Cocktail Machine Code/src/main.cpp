#include <Arduino.h>
#include "machine.hpp"

CocktailMachine machine;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  machine.initAll();
}

void loop() {
  machine.run();
}
