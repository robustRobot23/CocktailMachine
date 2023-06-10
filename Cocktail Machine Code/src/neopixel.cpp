#include "neopixel.hpp"

void neopixelInit() {
    ring.begin();
    ring.setBrightness(50);
    ring.show(); // Initialize all pixels to 'off'
}   

void setNeopixelColour(uint32_t c) {
  for(uint16_t i=0; i < NUM_NEOPIXELS; i++) {
    ring.setPixelColor(i, c);
  }
  ring.show();
}

