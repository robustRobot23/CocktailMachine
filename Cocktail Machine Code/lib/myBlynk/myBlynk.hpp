#ifndef MY_BLYNK_H
#define MY_BLYNK_H

#include <Arduino.h>
#include <Blynk.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <privateInfo.hpp>
// #include <machine.hpp>
#include <state.hpp>
#include <ingredients.hpp>


volatile int blynkCurrentSelection;
volatile bool blynkSelected;
volatile int blynkSelectedElement;
volatile int blynkManualRGB;

WidgetTerminal terminal(V5);

void blynkInit();
int getBlynkSelection();
void blynkTerminalDisplay();

#endif