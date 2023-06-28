#include <Arduino.h>
#include <machine.hpp>

Machine machine;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  machine.initAll();
}

void loop() {
  machine.run();
}
