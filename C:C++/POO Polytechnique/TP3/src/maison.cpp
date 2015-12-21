#include "maison.h"

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

#include "personne.h"
#include "cellulaire.h"

using namespace std;

Maison::Maison(unsigned int id, string adresse, float position) : ObjetConnecte(id), adresse_(adresse), position_(position) {
}

Maison::~Maison() {
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
	return routeur_->obtenirCellulaires().empty();
}


void Maison::observerCellulaires(float tempsObservation) {
	// Boucle dans le temps, les cellulaires enregistrés sont observés en continu.
	time_t start = time(0);
    bool estMaison = false;

	while (difftime(time(0), start) <= tempsObservation) {
		// Observation de tous les cellulaires, détection de proximité et ouverture du système de la maison si besoin.
		for(Cellulaire* cellulaire : cellulaires_) {
			if(cellulaire->estProche(position_)){
				if(estOccupant(cellulaire->obtenirPersonne())){
                    if(!cellulaire->estConnecte()) {
                        cellulaire->seConnecter(routeur_);
                        if (!estMaison) {
                            Message aux(id_, 0, ALLUMER_CHAUFFAGE);
                            envoyerMessage(aux);
                            estMaison = true;
                        }
                    }
				} else {
                    if(!cellulaire->estConnecte()) {
                        cellulaire->seConnecter(routeur_);
                        for (Cellulaire *c : cellulaires_) {
                            if (estOccupant(c->obtenirPersonne())) {
                                Message aux(cellulaire->obtenirId(), c->obtenirId(), NOTIFICATION_VISITEUR);
                                envoyerMessage(aux);
                            }
                        }
                    }
				}
			} else {
                if(cellulaire->estConnecte()) {
                    cellulaire->seDeconnecter();
                }
			}
		}

		//Si la maison est vide
		if(estVide() && estMaison) {
            Message aux(id_, 0, ETEINDRE_CHAUFFAGE);
            envoyerMessage(aux);
            estMaison = false;
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


Maison& Maison::operator+=(Personne* personne) {
	ajouterOccupant(personne);
	return *this;
}

Maison& Maison::operator+=(Cellulaire* cellulaire) {
	ajouterCellulaire(cellulaire);
	return *this;
}

void Maison::seConnecter(Routeur* routeur){
    if(connecte_){
        std::cerr << "Un autre routeur est déjà connecté à cette maison" << std::endl;
        return;
    }
	routeur->accepterConnexion(this);
    routeur_ = routeur;
	connecte_ = true;
}
