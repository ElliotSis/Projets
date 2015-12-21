//
// Created by adrien on 15-10-28.
//

#ifndef TP4_METEO_H
#define TP4_METEO_H


#include "observable.h"

class Meteo : public Observable{
public:
    int obtenirTemp();
    void modifierTemp(int temp);
    int obtenirVitesseVents();
    void modifierVitesseVents(int vitesseVents);
    std::string obtenirNomClasse() const;

private:
    int temp_;
    int vitesseVents_;
};


#endif //TP4_METEO_H
