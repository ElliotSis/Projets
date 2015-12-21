#include <iostream>

#include "personne.h"
#include "cellulaire.h"
#include "maison.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Création des personnes
    Personne jeanTil("Jean-Til", "Lafrite", 14, "514-430-7777");
    Personne mathilde("Mathilde", "Lafrite", 42, "514-430-8888");
    Personne philippe("Philippe", "Lafrite", 55, "514-430-9999");

    // Création des cellulaires
    Cellulaire cellulaire1("514-430-7777", &jeanTil, 2.0f);
    Cellulaire cellulaire2("514-430-8888", &mathilde, 4.0f);
    Cellulaire cellulaire3("514-430-9999", &philippe, 8.0f);

    // Création de la maison avec 4 chauffages
    Maison maison("5032 Côte des Neiges", 14.0f, 4);

    // Ajout des occupants dans la maison
    maison += &jeanTil;
    maison.ajouterOccupant(&mathilde);
    maison += &philippe;

    // Test de l'opérateur d'égalité de personne + non-ajout des personnes déjà occupantes
    /*
    maison.ajouterOccupant(&philippe); // Affichage d'un message d'erreur
    Personne jeanTilCopie("Jean-Til", "Lafrite", 27);
    maison += &jeanTilCopie; // Affichage d'un message d'erreur
    */

    // Ajout des cellulaires dans la maison
    maison += &cellulaire1;
    maison += &cellulaire2;
    maison.ajouterCellulaire(&cellulaire3);

    // Test de l'opérateur d'égalité de cellulaire + non-ajout des cellulaires déjà surveillés
    // Test du constructeur par copie de cellulaire
    // Test de l'affectation de cellulaire
    /*
    maison.ajouterCellulaire(&cellulaire1); // Affichage d'un message d'erreur
    Cellulaire cellulaire2Copie(cellulaire2);
    maison += &cellulaire2Copie; // Affichage d'un message d'erreur
    cellulaire2Copie = cellulaire1;
    maison.ajouterCellulaire(&cellulaire2Copie); // Affichage d'un message d'erreur
    */

    // Test de l'affichage
    maison.afficherListeOccupants();
    cout << endl;
    maison.afficherListeCellulaires();
    cout << endl;

    // Test du constructeur par copie de maison
    /*
    Maison maisonCopie(maison);

    maisonCopie.afficherListeOccupants();
    cout << endl;
    maisonCopie.afficherListeCellulaires();
    cout << endl;
    */

    // Test de l'affectation de maison
    /*
    Maison maisonAffectation;
    maisonAffectation = maison;

    maisonAffectation.afficherListeOccupants();
    cout << endl;
    maisonAffectation.afficherListeCellulaires();
    cout << endl;
    */

    // Ajout d'autres personnes et cellulaires
    Personne huguette("Huguette", "Fromage", 88, "514-430-6666");
    Personne florence("Florence", "Poutine", 16, "514-430-5555");
    Cellulaire cellulaire4("514-430-6666", &huguette, 3.0f);
    Cellulaire cellulaire5("514-430-5555", &florence, 1.0f);

    maison += &huguette;
    maison += &florence;
    maison += &cellulaire4;
    maison += &cellulaire5;

    // Test de l'affichage
    maison.afficherListeOccupants();
    cout << endl;
    maison.afficherListeCellulaires();
    cout << endl;    

    // Observation des cellulaires
    maison.observerCellulaires();

    // Désallocation de la mémoire
    // Automatique car on a travaillé qu'avec des objets directement

    return 0;
}
