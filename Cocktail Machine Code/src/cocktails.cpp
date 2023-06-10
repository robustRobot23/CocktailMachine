#include "cocktails.hpp"

Cocktails::Cocktails(Liquor l, Mixer m1, int mL1, Mixer m2, int mL2, Mixer m3, int mL3, Mixer m4, int mL4) {
    liquor = l;

    mixerOne = m1;
    volumeOne = mL1;

    mixerTwo = m2;
    volumeTwo = mL2;
    
    mixerThree = m3;
    volumeThree = mL3;

    mixerFour = m4;
    volumeFour = mL4;
}

//This would be a lot nicer if a pump struct or class was passed to this function
void CocktailHandling::pumpOn(int pump, long int startTime) {
    switch(pump) {
        case 1:
            pump1Start = startTime;
            break;
        case 2:
            pump2Start = startTime;
            break;
        case 3:
            pump3Start = startTime;
            break;
        case 4:
            pump4Start = startTime;
            break;
    }
}

//This would also be a lot nicer if a pump struct or class was passed to this function
bool CocktailHandling::checkPump(int pump, long int duration) {
    bool pumpDone = false;
    //whats the function call to get current time?
    switch (pump) {
        case 1:
            pumpDone = duration <= millis() - pump1Start;
            break;
        case 2:
            pumpDone = duration <= millis() - pump2Start;
            break;
        case 3:
            pumpDone = duration <= millis() - pump3Start;
            break;
        case 4:
            pumpDone = duration <= millis() - pump4Start;
            break;
    }
    return pumpDone;
}

