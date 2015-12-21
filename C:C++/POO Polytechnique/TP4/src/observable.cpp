//
// Created by adrien on 15-10-28.
//

#include "observable.h"
#include "observateur.h"


void Observable::ajouterObservateur(Observateur *observateur) {
    if(observateur != nullptr)
        listeObservateurs_.push_back(observateur);
}

void Observable::notifierChangement() {
    for(Observateur* observateur : listeObservateurs_){
        observateur->mettreAJour(this);
    }
}

std::string Observable::obtenirNomClasse() const
{
    return typeid(Observable).name();
}