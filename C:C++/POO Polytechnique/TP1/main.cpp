#include <iostream>

#include "personne.h"
#include "cellulaire.h"
#include "maison.h"

using namespace std;

int main(int argc, char* argv[]) {
    
    // 1. Creer deux personnes: Philippe et Mathilde Lafrite (55 et 42 ans respectivement)
	Personne personne1("Phillipe", "Lafrite", 55);
	Personne personne2("Mathilde", "Lafrite", 42);
    
    // 2. Créer deux cellulaires avec les numéros 514-430-9999 et 514-000-0101, et les attribuer à Philippe et Mathilde.
    // Ne pas oublier de modifier le propriétaire des cellulaires.
	Cellulaire cellulaire1("514-430-9999");
	personne1.modifierNumeroCelullaire("514-430-9999");
	cellulaire1.modifierPersonne(&personne1);

	Cellulaire cellulaire2("514-000-0101");
	personne2.modifierNumeroCelullaire("514-000-0101");
	cellulaire2.modifierPersonne(&personne2);
    
    // 3. Modifier la position des cellulaires de Philippe et de Mathilde à 4 et 8, respectivement.
	cellulaire1.modifierPositionGps(4.0f);
	cellulaire2.modifierPositionGps(8.0f);
    
    // 4. Créer une maison, avec une adresse et la position 14.0.
	Maison maison("5032 Côte des Neiges", 14.0f);
    
    // 5. Ajouter Philippe et Mathilde comme occupants de la maison.
    // Lorsqu'on ajoute un occupant à la maison, son cellulaire doit également etre ajouté.
	maison.ajouterOccupant(&personne1);
	maison.ajouterCellulaire(&cellulaire1);
	maison.ajouterOccupant(&personne2);
	maison.ajouterCellulaire(&cellulaire2);
    
    // 6. Créer une nouvelle personne avec un nouveau cellulaire: Francois Lerigolo (55 ans également), 514-678-1234.
    // Ajouter le cellulaire de Francois aux cellulaires observés par la maison, sans que Francois soit occupant de la maison.
	Personne personne3("François", "Lerigolo", 55, "514-678-1234");
	Cellulaire cellulaire3("514-678-1234");
	cellulaire3.modifierPersonne(&personne3);
	maison.ajouterCellulaire(&cellulaire3);
    
    // 7. Démarrer l'observation des cellulaires par la maison.
    // Lorsqu'un cellulaire approche de la maison, son proprietaire est identifié. 
    // S'il est occupant de la maison, le chauffage est allume, si ce n'est deja fait.
    // Deroulement du programme:
    // Mathilde rentre en premier à la maison, la maison l'identifie comme etant un occupant et active le chauffage.
    // Philippe arrive ensuite, mais rien ne se passe car la maison n'est pas vide.
    // La maison détecte l'arrivée de Francois mais n'active rien car il n'est pas un occupant de la maison. 
    // La maison previent Philippe et Mathilde de l'arrivée de leur ami Francois.
    cout << "Demarrage de l'observation..." << endl;
    maison.observerCellulaires();
    cout << "Fin de l'observation..." << endl;
    
    // 8. Désallocation de la mémoire.
    // Automatique car on travaille avec des objets directement.
    
    return 0;
}
