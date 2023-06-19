#ifndef MY_BLYNK_H
#define MY_BLYNK_H

#include <Arduino.h>
#include <privateInfo.hpp>
#include <state.hpp>
#include <ingredients.hpp>


static volatile int blynkCurrentSelection = 0;
static volatile bool blynkSelected = false;
static volatile int blynkSelectedElement = 0;
static volatile int blynkManualRGB;
static volatile int numberAvailableCocktails = 0;

void blynkInit();
void runBlynk();
int getBlynkSelection();
void blynkTerminalPrint(String message, String value);
void blynkTerminalPrint(String message);
void blynkClearDisplay();


#endif