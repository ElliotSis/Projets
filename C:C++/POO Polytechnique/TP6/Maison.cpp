#include <ctime>
#include <cstdio>
#include <iostream>
#include "Maison.h"
#include "Routeur.h"
#include "Meteo.h"
#include "MessageEnvoiePersonne.h"
#include <algorithm>
#include <typeinfo>

using namespace std;

// !!!!!!!!!! A FAIRE !!!!!!!!!!!!
// Vous devez modifier le constructeur pour permettre l'envoie de signaux.
Maison::Maison(unsigned int id, const std::string& adresse, float position, string ville)
    :ObjetConnecte(id), temperatureAGarder_(20), temperatureExterieure_(15), ville_(ville)
{
	id_ = id;
	adresse_ = adresse;
	position_ = position;
}

Maison::~Maison()
{

}

// !!!!!!!!!! A FAIRE !!!!!!!!!!!!
// Vous devez emettre des signaux lorsqu'une personne approche de la maison ou s'en éloigne.
void Maison::mettreAJour(Observable* arg)
{
	string nom = arg->obtenirNomClasse();
    if (nom == typeid(Cellulaire).name())
	{
		Cellulaire *cell = (Cellulaire*)arg;
		Personne *proprio = cell->getProprietaire();
		if (cell->estProche(position_) && !proprio->estALaMaison())
		{
            emit(signal_bonjour());
			if (this->estOccupant(proprio))
			{
				cell->seConnecter(routeur_);
				if (this->estVide() && temperatureExterieure_ <= this->temperatureAGarder_)
				{
					Message *msg = new Message(id_, 0, ALLUMAGE_AUTOMATIQUE);
					this->envoyerMessage(msg);
					delete msg;
				}
			}
			else
			{
				Message *msg = new MessageEnvoiePersonne(id_, 0, NOTIFICATION_VISITEUR, proprio);
				this->envoyerMessage(msg);
				delete msg;
			}
            proprio->setEstALaMaison(true);
		}
		else if (!cell->estProche(position_) && proprio->estALaMaison())
		{
            emit(signal_aurevoir());
			if (this->estOccupant(proprio))
			{
				cell->seDeconnecter();
			}
			proprio->setEstALaMaison(false);
			if (estVide())
			{
				Message *msg = new Message(id_, 0, ETTEINDRE_CHAUFFAGE);
				this->envoyerMessage(msg);
				delete msg;
            }
		}
	}
	else if (nom == typeid(Meteo).name())
	{
		Meteo *meteo = (Meteo*)arg;
		if (meteo->getTemp(ville_) > this->temperatureAGarder_)
		{
			Message msg(id_, 0, ETTEINDRE_CHAUFFAGE);
			this->envoyerMessage(&msg);
		}
		else if (meteo->getTemp(ville_) <= this->temperatureAGarder_ && !this->estVide())
		{
			Message msg(id_, 0, ALLUMAGE_AUTOMATIQUE);
			this->envoyerMessage(&msg);
		}
	}
}

void Maison::ajouterOccupant(Personne* personne)
{
	occupants_.push_back(personne);
}

bool Maison::estOccupant(const Personne* personne) const
{
	return (find(occupants_.begin(), occupants_.end(), personne) != occupants_.end());
}

bool Maison::estVide() const
{
	bool estVide = true;
    for(std::list<Personne*>::const_iterator it = occupants_.begin(); it != occupants_.end(); it++)
    {
        if (estVide && (*it)->estALaMaison())
		{
			estVide = false;
		}
    }
	return estVide;
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
