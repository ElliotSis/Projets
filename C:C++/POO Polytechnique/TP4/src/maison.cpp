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
#include "meteo.h"

using namespace std;

Maison::Maison(unsigned int id, string adresse, float position) : ObjetConnecte(id), adresse_(adresse), position_(position) {
    tempExterieure_ = 15;
    tempInterieure_ = 20;
    nbCellulairesCo_ = 0;
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

bool Maison::estOccupant(Personne* personne) const {
	for(Personne* p : personnes_) {
		if(*personne == *p) {
			return true;
		}
	}

	return false;
}

bool Maison::estVide() const {
	return (nbCellulairesCo_ == 0);
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


Maison& Maison::operator+=(Personne* personne) {
	ajouterOccupant(personne);
	return *this;
}



void Maison::mettreAJour(Observable *observable) {
    //cout << observable->obtenirNomClasse() << endl;
    if(observable->obtenirNomClasse() == "5Meteo"){
        tempExterieure_ = ((Meteo*)observable)->obtenirTemp();
    } else if (observable->obtenirNomClasse() == "10Cellulaire"){
        Cellulaire* cellulaire = ((Cellulaire*)observable);
        if(cellulaire->estProche(position_)){
            if(estOccupant(cellulaire->obtenirPersonne())) {
                if (!cellulaire->estConnecte()) {
                    cellulaire->seConnecter(routeur_);
                    nbCellulairesCo_++;
                    std::cout << cellulaire->obtenirPersonne()->obtenirPrenom() << " " <<  cellulaire->obtenirPersonne()->obtenirNom() <<
                               " arrive à la maison !" << std::endl;
                }
            } else {
                std::cout << cellulaire->obtenirPersonne()->obtenirPrenom() << " " <<  cellulaire->obtenirPersonne()->obtenirNom() <<
                            " arrive." << std::endl;
                Message aux(cellulaire->obtenirId(), 0, NOTIFICATION_VISITEUR);
                envoyerMessage(aux);
            }
        } else {
            if (!cellulaire->estConnecte()) {
                cellulaire->seDeconnecter();
                std::cout << cellulaire->obtenirPersonne()->obtenirPrenom() << " " <<  cellulaire->obtenirPersonne()->obtenirNom() <<
                " pars de la maison !" << std::endl;
                nbCellulairesCo_--;
            }
        }
    }
    if(!estVide() && tempExterieure_ < tempInterieure_){
        Message aux(id_, 0, ALLUMER_CHAUFFAGE);
        envoyerMessage(aux);
    } else {
        Message aux(id_, 0, ETEINDRE_CHAUFFAGE);
        envoyerMessage(aux);
    }
}
