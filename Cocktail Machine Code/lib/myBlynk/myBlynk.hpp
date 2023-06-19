#ifndef MY_BLYNK_H
#define MY_BLYNK_H

#include <Arduino.h>
#include <privateInfo.hpp>
#include <state.hpp>
#include <ingredients.hpp>

static int blynkCurrentSelection = 0;
static int blynkPreviousSelection = 1;
static bool blynkSelected = false;
static int blynkSelectedElement = 0;
static int blynkManualRGB;
static int numberAvailableCocktails = 0;

void blynkInit();
void runBlynk();

int getBlynkSelection();
bool blynkSelectedConfirmation();
int getBlynkCurrentSelection();

void blynkTerminalPrint(String message, String value);
void blynkTerminalPrint(String message);
void blynkClearDisplay();

int blynkRequestMixer();
int blynkRequestLiquor();


#endif