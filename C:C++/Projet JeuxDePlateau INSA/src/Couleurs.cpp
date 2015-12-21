#include "Couleurs.h"

void intToRGB(int couleur, double& r, double& g, double& b){
    b = (couleur & 255)/255.;
    g = ((couleur >> 8) & 255)/255.;
    r = ((couleur >> 16) & 255)/255.;
}
