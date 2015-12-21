//
// Created by adrien on 15-10-28.
//

#ifndef TP4_OBSERVABLE_H
#define TP4_OBSERVABLE_H

#include <vector>
#include <string>
#include <typeinfo>

class Observateur;

class Observable{
public:
    void ajouterObservateur(Observateur* observateur);
    void notifierChangement();
    virtual std::string obtenirNomClasse() const;
private:
    std::vector<Observateur*> listeObservateurs_;
};

#endif //TP4_OBSERVABLE_H
