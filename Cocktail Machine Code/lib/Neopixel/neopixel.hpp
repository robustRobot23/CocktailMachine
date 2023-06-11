#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include "Adafruit_NeoPixel.h"
#include "pinDefinitions.hpp"

#define NUM_NEOPIXELS 24


Adafruit_NeoPixel ring = Adafruit_NeoPixel(NUM_NEOPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void neopixelInit();

/*
 * Call using 
 * setNeopixelColour(ring.color(x,y,z));
 */
void setNeopixelColour(uint32_t c);


#endif


