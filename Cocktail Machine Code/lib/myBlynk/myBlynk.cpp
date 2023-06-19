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
    if (param.asInt()) {
    Serial.println("Blynk --");
    blynkCurrentSelection--;
    switch(state) {
        case selectMixers:
            if (blynkCurrentSelection < 0) {
                blynkCurrentSelection = NUMBER_MIXERS - 1;
            }
            break;
        case selectLiquor:
            if (blynkCurrentSelection < 0) {
                blynkCurrentSelection = NUMBER_LIQUORS - 1;
            } 
            break;
        
        case displayMenu:
            if (blynkCurrentSelection < 0) {
                blynkCurrentSelection = numberAvailableCocktails; 
            }
            break;
    }
    }
}

BLYNK_WRITE(V3) {
    if (param.asInt()) {
    Serial.println("Blynk ++");

    blynkCurrentSelection++;
    switch(state) {
        case selectMixers:
            if (blynkCurrentSelection >= NUMBER_MIXERS) {
                blynkCurrentSelection = 1;
            } 
            break;
        case selectLiquor:
            if (blynkCurrentSelection >= NUMBER_LIQUORS) {
                blynkCurrentSelection = 1;
            }
            break;
        
        case displayMenu:
            if (blynkCurrentSelection >= numberAvailableCocktails) {
                blynkCurrentSelection = 0;
            }
            break;
    }
    }
}
BLYNK_WRITE(V4) {
    if (param.asInt()) {
        blynkSelected = true;
        blynkSelectedElement = blynkCurrentSelection;
        blynkCurrentSelection = 0;
    }
}

BLYNK_WRITE(V5) {

    ///Currently do nothing with terminal messages. No plans to change this
}

int getBlynkSelection() {
    int selectedElement = 0;
    if (blynkSelected) {
        blynkSelected = false;
        selectedElement = blynkSelectedElement;
        blynkSelectedElement = 0;
    } 
    return selectedElement;
}

bool blynkSelectedConfirmation() {
    bool selected = blynkSelected;
    blynkSelected = false;
    return selected;
}

int getBlynkCurrentSelection() {
    return blynkCurrentSelection;
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

int blynkRequestMixer() {
    return getBlynkSelection();

}

int blynkRequestLiquor() {
    return getBlynkSelection();
}

// void blynkUpdateDisplay() {
//     static State previousState = enjoy; //will not start in this state so the following if statement should always run
//     if (state != previousState) {
//         switch (state) {
//             case selectMixers:
//                 static Mixer previousMixer = None;
//                 if ()
//         }
//     }
// }