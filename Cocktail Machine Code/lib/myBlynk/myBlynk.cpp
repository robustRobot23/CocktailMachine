#include <myBlynk.hpp>

void blynkInit(){
      Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

BLYNK_WRITE(V1) {
    blynkManualRGB = param.asInt();  // Get value as integer
}

BLYNK_WRITE(V2) {
    switch(state) {
        case selectMixers:
            if (blynkCurrentSelection-- < 1) {
                blynkCurrentSelection = NUMBER_MIXERS;
            } else if (blynkCurrentSelection-- > NUMBER_MIXERS) {
                blynkCurrentSelection = 1;
            }
            break;
        case selectLiquor:
            if (blynkCurrentSelection-- < 0) {
                blynkCurrentSelection = NUMBER_LIQUORS;
            } else if (blynkCurrentSelection-- > NUMBER_LIQUORS) {
                blynkCurrentSelection = 1;
            }
            break;
        
        case displayMenu:
            
            break;
    }
    blynkCurrentSelection--;
}

BLYNK_WRITE(V3) {
    blynkCurrentSelection++;
}
BLYNK_WRITE(V4) {
    blynkSelected = true;
    blynkSelectedElement = blynkCurrentSelection;
}

BLYNK_WRITE(V5) {


}

int getBlynkSelection() {
    if (blynkSelected) {
        return blynkSelectedElement;
    } else {
        return 0;
    }
}

void blynkTerminalDisplay(int x) {
    switch(x) {
        case 0:
            // String mixing = Mixers[blynkSelectedElement];
            terminal.print("Current Mixer: ");
            terminal.print(Mixers[blynkSelectedElement]);
            break;
        case 1:
            terminal.print("Current Liqour: ");
            terminal.print(Liquors[blynkSelectedElement]);
            break;
        case 2:
            terminal.print("Current Cocktail");
            terminal.print(blynkSelectedElement); 
    }

    terminal.println();
    terminal.flush();
}


