#ifndef MY_BLYNK_H
#define MY_BLYNK_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <privateInfo.hpp>
#include <state.hpp>
#include <ingredients.hpp>


static volatile int blynkCurrentSelection = 0;
static volatile bool blynkSelected = false;
static volatile int blynkSelectedElement = 0;
static volatile int blynkManualRGB;

static WidgetTerminal terminal(V5);

void blynkInit();
int getBlynkSelection();

#endif