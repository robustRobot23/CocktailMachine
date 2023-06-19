#include <myBlynk.hpp>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

WidgetTerminal terminal(V5);


void blynkInit(){
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void runBlynk() {
    Blynk.run();
}

BLYNK_WRITE(V1) {
    blynkManualRGB = param.asInt();  // Get value as integer
}

BLYNK_WRITE(V2) {
    blynkCurrentSelection--;
    switch(state) {
        case selectMixers:
            if (blynkCurrentSelection < 1) {
                blynkCurrentSelection = NUMBER_MIXERS;
            }
            break;
        case selectLiquor:
            if (blynkCurrentSelection < 0) {
                blynkCurrentSelection = NUMBER_LIQUORS;
            } 
            break;
        
        case displayMenu:
            if (blynkCurrentSelection < 0) {
                blynkCurrentSelection = numberAvailableCocktails; 
            }
            break;
    }
    
}

BLYNK_WRITE(V3) {
    blynkCurrentSelection++;
    switch(state) {
        case selectMixers:
            if (blynkCurrentSelection > NUMBER_MIXERS) {
                blynkCurrentSelection = 1;
            } 
            break;
        case selectLiquor:
            if (blynkCurrentSelection > NUMBER_LIQUORS) {
                blynkCurrentSelection = 1;
            }
            break;
        
        case displayMenu:
            if (blynkCurrentSelection > numberAvailableCocktails) {
                blynkCurrentSelection = 0;
            }
            break;
    }
}
BLYNK_WRITE(V4) {
    blynkSelected = true;
    blynkSelectedElement = blynkCurrentSelection;
}

BLYNK_WRITE(V5) {

    ///Currently do nothing with terminal messages. No plans to change this
}

int getBlynkSelection() {
    if (blynkSelected) {
        return blynkSelectedElement;
    } else {
        return 0;
    }
}

void blynkTerminalPrint(String message, String value) {

    terminal.print(message);
    terminal.print(value);

    terminal.println();
    terminal.flush();

}

void blynkTerminalPrint(String message) {
    terminal.print(message);
    terminal.println();
    terminal.flush();
}

void blynkClearDisplay() {
    terminal.clear();
}


