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
#include "chauffage.h"
#include "personne.h"

using namespace std;

Maison::Maison(string adresse, float position, unsigned int nbChauffages) : adresse_(adresse), position_(position) {
	for(int i = 0; i < nbChauffages; i++) {
		chauffages_.push_back(new Chauffage());
	}
}

Maison::Maison(const Maison& maison) : adresse_(maison.adresse_), position_(maison.position_), 
						personnes_(maison.personnes_), cellulaires_(maison.cellulaires_) {
	for(Chauffage* chauffage : maison.chauffages_){
		chauffages_.push_back(new Chauffage(*chauffage));
	}
}

Maison::~Maison() {
	for(Chauffage* chauffage : chauffages_) {
		delete chauffage;
	}
}

string Maison::obtenirAdresse() const {
	return adresse_;
}

void Maison::modifierAdresse(string adresse) {
	adresse_ = adresse;
}

float Maison::obtenirPosition() const {
	return position_;
}

void Maison::modifierPosition(float position) {
	position_ = position;
}

void Maison::ajouterOccupant(Personne* personne) {
	for(Personne* p : personnes_) {
		if(*personne == *p) {
			cout << "Cette personne est déjà dans la liste des occupants de la maison !" << endl;
			return;
		}
	}

	personnes_.push_back(personne);
}

void Maison::ajouterCellulaire(Cellulaire* cellulaire) {
	for(Cellulaire* c : cellulaires_) {
		if(*cellulaire == *c) {
			cout << "Ce cellulaire est déjà surveillé par la maison !" << endl;
			return;
		}
	}

	cellulaires_.push_back(cellulaire);
}

bool Maison::estOccupant(Personne* personne) const {
	for(Personne* p : personnes_) {
		if(*personne == *p) {
			return true;
		}
	}

	return false;
}

bool Maison::estVide() const {
	for(Personne* personne : personnes_) {
		if(personne->obtenirEstALaMaison()) {
			return false;
		}
	}

	return true;
}

void Maison::allumerChauffages() {
	bool auMoinsUnAllume = false;

	for(Chauffage* chauffage : chauffages_) {
		if(!chauffage->obtenirEstAllume()) {
			chauffage->allume();
			auMoinsUnAllume = true;
		}
		//else {
		//	cout << "Le chauffage est déjà allumé" << endl;
		//}
	}

	if(auMoinsUnAllume) {
		cout << "Tous les chauffages de la maison sont maintenant allumés" << endl;
	}
	//else {
	//	cout << "Les chauffages sont déjà tous allumés" << endl;
	//}
}

void Maison::eteindreChauffages() {
	bool auMoinsUnEteint = false;

	for(Chauffage* chauffage : chauffages_) {
		if(chauffage->obtenirEstAllume()) {
			chauffage->eteindre();
			auMoinsUnEteint = true;
		}
		//else {
		//	cout << "Le chauffage est déjà éteint" << endl;
		//}
	}

	if(auMoinsUnEteint) {
		cout << "Tous les chauffages de la maison sont maintenant éteints" << endl;
	}
	//else {
	//	cout << "Les chauffages sont déjà tous éteints" << endl;
	//}
}


void Maison::observerCellulaires(float tempsObservation) {
	// Boucle dans le temps, les cellulaires enregistrés sont observés en continu.
	time_t start = time(0);
	map<Personne*, bool> estALaMaisonMaisCestPasLaSienne;

	while (difftime(time(0), start) <= tempsObservation) {
		// Observation de tous les cellulaires, détéction de proximité et ouverture du système de la maison si besoin.
		for(Cellulaire* cellulaire : cellulaires_) {
			Personne* personne = cellulaire->obtenirPersonne();

			if(cellulaire->estProche(position_)) {
				if(estOccupant(personne)) {
					if(!personne->obtenirEstALaMaison()) {
						cout << personne->obtenirPrenom() << " " << personne->obtenirNom() << " arrive à la maison" << endl;

						bool personneEstALaMaison = true;
						for(Personne* personne : personnes_) {
							if(personne->obtenirEstALaMaison()) {
								personneEstALaMaison = false;
							}
						}

						personne->modifierEstALaMaison(true);

						if(personneEstALaMaison) {
							allumerChauffages();
						} 
					}
					//else {
					//	cout << personne->obtenirPrenom() << " " << personne->obtenirNom() << " est déjà à la maison" << endl;
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


						bool personneEstALaMaison = true;
						for(Personne* personne : personnes_) {
							if(personne->obtenirEstALaMaison()) {
								personneEstALaMaison = false;
							}
						}

						if(personneEstALaMaison) {
							eteindreChauffages();
						} 
					}
					//else {
					//	cout << personne->obtenirPrenom() << " " << personne->obtenirNom() << " n'est pas dans la maison" << endl;
					//}
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
		}

		// Pause de une seconde.
		PAUSE(1);
	}
}

void Maison::trierOccupants() {
	bool estTrie = false;

	while(!estTrie) {
		estTrie = true;
		for(int i = 0; i < personnes_.size() - 1; i++) {
			if(*(personnes_[i+1]) < *(personnes_[i])) {
				// Échange des deux personnes
				Personne* tmp = personnes_[i];
				personnes_[i] = personnes_[i+1];
				personnes_[i+1] = tmp;

				estTrie = false;
			}
		}
	} 
}

void Maison::afficherTirets(int nbTirets) {
	for (int i = 0; i < nbTirets; ++i) {
		cout << "-";
	}
	cout << endl;
}

void Maison::afficherListeOccupants() {
	trierOccupants();
	
	afficherTirets();
	cout << "La liste d'occupants en ordre alphabétique est :" << endl;
	afficherTirets();

	for(Personne* personne : personnes_) {
		cout << *personne << endl;
	}

	afficherTirets();
}

void Maison::afficherListeCellulaires() const {
	afficherTirets();
	cout << "La liste de cellulaires enregistrés est :" << endl;
	afficherTirets();

	for(Cellulaire* cellulaire : cellulaires_) {
		cout << *cellulaire << endl;
	}

	afficherTirets();
}

bool Maison::estChauffageAllume() const {
	for(Chauffage* chauffage : chauffages_) {
		if(chauffage->obtenirEstAllume()) {
			return true;
		}
	}
	
	return false;
}


Maison& Maison::operator+=(Personne* personne) {
	ajouterOccupant(personne);
	return *this;
}

Maison& Maison::operator+=(Cellulaire* cellulaire) {
	ajouterCellulaire(cellulaire);
	return *this;
}

Maison& Maison::operator=(const Maison& maison) {
	if (this != &maison) {
		adresse_ = maison.adresse_;
		position_ = maison.position_;
		personnes_ = maison.personnes_;
		cellulaires_ = maison.cellulaires_;

		for (Chauffage* chauffage : chauffages_) {
			delete chauffage;
		}
		chauffages_.clear();

		for (Chauffage* chauffage : maison.chauffages_) {
			chauffages_.push_back(new Chauffage(*chauffage));
		}
	}
	return *this;
}
