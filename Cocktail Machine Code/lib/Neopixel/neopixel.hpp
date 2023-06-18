#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include "Adafruit_NeoPixel.h"
#include <pinDefinitions.hpp>

#define NUM_NEOPIXELS 24

#define RED         0xFF0000
#define GREEN       0x00FF00
#define BLUE        0x0000FF
#define ORANGE      0xFF6600
#define YELLOW      0xFFFF00
#define HOT_PINK    0xFF69B4
#define PURPLE      0x5A1073


void neopixelInit();
  
/// @brief Sets the entire ring to one RGB colour
/// @param c Bit packed RGB value. Use hex code or ring.color(r,g,b) 
void setNeopixelColour(uint32_t c);


#endif


