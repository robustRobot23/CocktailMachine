#include "cocktails.hpp"

Cocktail::Cocktail(Liquor l, int s, Mixer m1, int mL1, Mixer m2, int mL2, Mixer m3, int mL3, Mixer m4, int mL4) {
    liquors[0] = l;
    shots[0] = s;

    mixers[0] = m1;
    mixerVolumes[0] = mL1;

    mixers[1] = m1;
    mixerVolumes[1] = mL1;

    mixers[2] = m1;
    mixerVolumes[2] = mL1;

    mixers[3] = m1;
    mixerVolumes[3] = mL1;

}






