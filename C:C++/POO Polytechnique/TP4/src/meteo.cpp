//
// Created by adrien on 15-10-28.
//

#include "meteo.h"


int Meteo::obtenirTemp() {
    return temp_;
}

void Meteo::modifierTemp(int temp) {
    temp_ = temp;
    notifierChangement();
}

int Meteo::obtenirVitesseVents() {
    return vitesseVents_;
}

void Meteo::modifierVitesseVents(int vitesseVents) {
    vitesseVents_ = vitesseVents;
    notifierChangement();
}

std::string Meteo::obtenirNomClasse() const
{
    return typeid(Meteo).name();
}
