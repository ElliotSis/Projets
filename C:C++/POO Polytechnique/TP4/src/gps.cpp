#include "gps.h"

#include <cstdlib>
#include <iostream>
#include <stdio.h>

using namespace std;

GPS::GPS(float position) : position_(position) {
    srand ((time(NULL)));

    // Récupérer le temps actuel.
    time(&temps_);
}

GPS::~GPS() {}

float GPS::obtenirPosition() const {
    return position_;
}

void GPS::modifierPosition(float position) {
    position_ = position;
}

bool GPS::estProche(float position) {
    simulateurDePosition();
    return (position_ >= position - PROXIMITE && position_ <= position + PROXIMITE);
}

void GPS::simulateurDePosition() {
    time_t temps_actuel = time(NULL);
    float vitesse = 3.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(5.0-3.0)));
    position_ += (temps_actuel - temps_) * vitesse * 0.01;
}
