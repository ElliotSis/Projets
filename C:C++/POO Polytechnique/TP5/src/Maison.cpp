#include <ctime>
#include <cstdio>
#include <iostream>
#include <functional>
#include "enumTypes.h"
#include "Maison.h"
#include "Routeur.h"
#include "Meteo.h"
#include "TrierNombre.h"
#include "Frigo.h"
#include "MessageEnvoiePersonne.h"

using namespace std;
// TP5 A COMPLETER
Maison::Maison(unsigned int id, string adresse, float position, string nomVille, int temperatureExterieure, int temperatureAGarder) :
	ObjetConnecte(id), adresse_(adresse), position_(position), nomVille_(nomVille), temperatureExterieure_(temperatureExterieure), temperatureAGarder_(temperatureAGarder) {}

string Maison::getNomVille() const {
	return nomVille_;
}

void Maison::setNomVille(string nomVille) {
	nomVille = nomVille_;
}

void Maison::trierListeNomPrenom() {
	personnes_.sort([] (const Personne* personne1, const Personne* personne2) {
		return (*personne1 < *personne2);
	});
	afficherOccupants();
}

void Maison::trierListeAge() {
	personnes_.sort([] (const Personne* personne1, const Personne* personne2) {
		TrierNombre<unsigned int> t(personne1->getAge());
		return t(personne2->getAge());
	});
	afficherOccupants();
}

void Maison::afficherOccupants() const {
	for_each(personnes_.cbegin(), personnes_.cend(), 
		[] (const Personne* personne) {
			cout << *personne;
		});
}

bool Maison::estOccupant(const Personne* personne) const {
	return (find(personnes_.begin(), personnes_.end(), personne) != personnes_.end());
} 

void Maison::ajouterOccupant(Personne* personne) {
	if (!estOccupant(personne)) {
		personnes_.push_back(personne);
	}
} 

	

bool Maison::estVide() const {
	return (find_if(personnes_.cbegin(), personnes_.cend(), 
		[] (const Personne* personne) {
			return personne->estALaMaison();
		}) == personnes_.cend());
}

Maison::~Maison()
{

}

void Maison::mettreAJour(Observable* arg)
{
	string nom = arg->obtenirNomClasse();
	if (nom == typeid(Cellulaire).name())
	{
		Cellulaire *cell = (Cellulaire*)arg;
		Personne *proprio = cell->getProprietaire();
		if (cell->estProche(position_) && !proprio->estALaMaison())
		{
			if (estOccupant(proprio)) {
				if (!cell->isConnected()) {
					cell->seConnecter(routeur_);
				}
				proprio->setEstALaMaison(true);
				Message aux(id_, 0, ALLUMER_CHAUFFAGE);
        		envoyerMessage(&aux);
            }
            else {
            	MessageEnvoiePersonne aux(cell->getId(), 0, NOTIFICATION_VISITEUR, proprio);
            	envoyerMessage(&aux);
            } 
		}
		else if (!cell->estProche(position_) && proprio->estALaMaison()) {
			if (cell->isConnected()) {
                cell->seDeconnecter();
            }		
            proprio->setEstALaMaison(false);
        }
	}
	else if (nom == typeid(Meteo).name())
	{
		Meteo *meteo = (Meteo*)arg;
		temperatureExterieure_ = meteo->getTempVent(nomVille_).first;
		if (!estVide() && temperatureExterieure_ < temperatureAGarder_) {
			Message aux(id_, 0, ALLUMER_CHAUFFAGE);
        	envoyerMessage(&aux);
		}
		else {
			Message aux(id_, 0, ETTEINDRE_CHAUFFAGE);
        	envoyerMessage(&aux);
		}
	}
}



string Maison::getAdresse() const
{
	return adresse_;
}


void Maison::setAdresse(string adresse)
{
	adresse_ = adresse;
}

float Maison::getPosition() const
{
	return position_;
}

void Maison::setPosition(float position)
{
	position_ = position;
}

void Maison::recevoirMessage(Message* message)
{
}