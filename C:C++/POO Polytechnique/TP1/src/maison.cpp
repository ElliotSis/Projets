#include "maison.h"

#include <cstdio>
#include <ctime>
#include <map>
#include <iostream>

#ifdef _WIN32
#   include <Windows.h>
#   define PAUSE(x) Sleep(x * 1000)
#else
#   include <unistd.h>
#   define PAUSE(x) sleep(x)
#endif

#include "cellulaire.h"
#include "personne.h"

using namespace std;

Maison::Maison(const string adresse, float position) : adresse_(adresse), position_(position), chauffage_() {
	// Initialisation des personnes.
	for (int i = 0; i < NB_OCCUPANTS_MAX; ++i) {
		personnes_[i] = nullptr;
	}

	// Initialisation des cellulaires.
	for (int i = 0; i < NB_CELLULAIRES_MAX; ++i) {
		cellulaires_[i] = nullptr;
	}
}

Maison::~Maison() {}

const string Maison::obtenirAdresse() const {
	return adresse_;
}

void Maison::modifierAdresse(const string adresse) {
	adresse_ = adresse;
}

float Maison::obtenirPosition() const {
	return position_;
}

void Maison::modifierPosition(float position) {
	position_ = position;
}

void Maison::ajouterOccupant(Personne* personne) {
	int i = 0;

	while (i < NB_OCCUPANTS_MAX && personnes_[i] != nullptr) {
		i++;
	}

	if (i == NB_OCCUPANTS_MAX) {
		cout << "Le nombre de personnes maximum est atteint pour " <<
			"cette maison" << endl;
	}
	else {
		personnes_[i] = personne;
	}
}

void Maison::ajouterCellulaire(Cellulaire * cellulaire) {
	int i = 0;

	while(i < NB_CELLULAIRES_MAX && cellulaires_[i] != nullptr) {
		i++;
	}

	if(i == NB_CELLULAIRES_MAX) {
		cout << "Le nombre de cellulaires maximum est atteint pour " <<
			"cette maison" << endl;
	}
	else {
		cellulaires_[i] = cellulaire;
	}
}

bool Maison::estOccupant(Personne* personne) const {
	int i = 0;

	while(i < NB_OCCUPANTS_MAX && personnes_[i] != personne) {
		i++;
	}

	return (i < NB_OCCUPANTS_MAX);
}

bool Maison::estVide() const {
	int i = 0;

	while(i < NB_OCCUPANTS_MAX && personnes_[i] != nullptr && !(personnes_[i]->obtenirEstALaMaison())) {
		i++;
	}

	return (i == NB_OCCUPANTS_MAX || personnes_[i] == nullptr);
}

void Maison::observerCellulaires(float tempsObservation) {
	// Boucle dans le temps, les cellulaires enregistrés sont observés en continu.
	time_t start = time(0);
	map<Personne*, bool> estALaMaisonMaisCestPasLaSienne;

	while (difftime(time(0), start) <= tempsObservation) {
		// Observation de tous les cellulaires, détéction de proximité et ouverture du système de la maison si besoin.
		int i = 0;

		while(i < NB_CELLULAIRES_MAX && cellulaires_[i] != nullptr) {
			Personne* personne = cellulaires_[i]->obtenirPersonne();

			if(cellulaires_[i]->estProche(position_)) {
				if(estOccupant(personne)) {
					if(!personne->obtenirEstALaMaison()) {
						cout << personne->obtenirPrenom() << " " << personne->obtenirNom() << " arrive à la maison" << endl;
						personne->modifierEstALaMaison(true);
					}
					//else {
					//	cout << personne->obtenirPrenom() << " " << personne->obtenirNom() << " est déjà à la maison" << endl;
					//}

					if(!chauffage_.obtenirEstAllume()) {
						chauffage_.allume();
					}
					//else {
					//	cout << "Le chauffage est déjà allumé" << endl;
					//}
				}
				else {
					if(estALaMaisonMaisCestPasLaSienne.find(personne) == estALaMaisonMaisCestPasLaSienne.end() || !estALaMaisonMaisCestPasLaSienne[personne]) {
						estALaMaisonMaisCestPasLaSienne[personne] = true;
						cout << personne->obtenirPrenom() << " " << personne->obtenirNom() << " n'est pas un occupant, mais il passe quand même à la maison" << endl;	
					}
					//else {
					//	cout << personne->obtenirPrenom() << " " << personne->obtenirNom() << " n'est pas un occupant, et il est déjà à la maison" << endl;
					//}
				}
			} 
			else {
				if (estOccupant(personne)) {
					if(personne->obtenirEstALaMaison()) {
						personne->modifierEstALaMaison(false);
						cout << personne->obtenirPrenom() << " " << personne->obtenirNom() << " pars de sa maison" << endl;
					}
					//else {
					//	cout << personne->obtenirPrenom() << " " << personne->obtenirNom() << " n'est pas dans la maison" << endl;
					//}

					if(estVide()){
						if (chauffage_.obtenirEstAllume()) {
							chauffage_.eteindre();
						}
						//else {
						//	cout << "Le chauffage est déjà éteint" << endl;
						//}
					}
				}
				else {
					if(estALaMaisonMaisCestPasLaSienne.find(personne) != estALaMaisonMaisCestPasLaSienne.end() && estALaMaisonMaisCestPasLaSienne[personne]) {
						estALaMaisonMaisCestPasLaSienne[personne] = false;
						cout << personne->obtenirPrenom() << " " << personne->obtenirNom() << " quitte la maison de ses amis" << endl;
					}
					//else {
					//	cout << personne->obtenirPrenom() << " " << personne->obtenirNom() << " n'est pas dans la maison, mais ce n'est pas un occupant" << endl;
					//}
				}
			}

			i++;
		}

		// Pause de une seconde.
		PAUSE(1);
	}
}
