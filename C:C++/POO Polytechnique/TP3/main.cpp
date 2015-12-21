#include <iostream>
#include <chauffage.h>

#include "personne.h"
#include "cellulaire.h"
#include "maison.h"

using namespace std;

int main(int argc, char* argv[]) {

    // 1 : Création des personnes
    Personne personne1("Phillipe", "Lafrite", 55, "514-987-9547");
    Personne personne2("Mathilde", "Lafrite", 42, "514-546-3547");
    Personne personne3("François", "Lerigolo", 55, "514-678-1234");

    // 2 : Création de leurs celluaires
    Cellulaire cellulaire1(1, "514-987-9547");
    Cellulaire cellulaire2(2, "514-546-3547");
    Cellulaire cellulaire3(3, "514-678-1234");

    // 3 : Affectation des cellulaire au propriétaire
    cellulaire1.modifierPersonne(&personne1);
    cellulaire2.modifierPersonne(&personne2);
    cellulaire3.modifierPersonne(&personne3);

    // 4 : Création des chauffages
    Chauffage chauffage1(4);
    Chauffage chauffage2(5);

    // 5 : Création de la maison
    Maison maison(6, "5032 Côte des Neiges", 14.0f);

    // 6 : Spécification des propriétaires de la maison et cellualires observés
    maison.ajouterOccupant(&personne1);
    maison.ajouterOccupant(&personne2);
    maison.ajouterCellulaire(&cellulaire1);
    maison.ajouterCellulaire(&cellulaire2);
    maison.ajouterCellulaire(&cellulaire3);

    // 7 : Création du routeur
    Routeur routeur;

    // 8 : Connexion de tous les appareils au routeur
    maison.seConnecter(&routeur);
    chauffage1.seConnecter(&routeur);
    chauffage2.seConnecter(&routeur);

    // 9 : Enjoy the simulation !
    maison.observerCellulaires();

    // 10 : Après la simulation on déconnecte tout
    maison.seDeconnecter();
    chauffage1.seDeconnecter();
    chauffage2.seDeconnecter();

    return 0;
}
