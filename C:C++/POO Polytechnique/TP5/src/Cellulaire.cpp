#include "Cellulaire.h"
#include "Routeur.h"

using namespace std;

Cellulaire::Cellulaire(unsigned int id) : ObjetConnecte(id)
{
}

Cellulaire::~Cellulaire()
{

}

Cellulaire::Cellulaire(unsigned int id, std::string numero)
	: ObjetConnecte(id), numero_(numero)
{

}

bool Cellulaire::estProche(float position)
{
	return gps_.estProche(position);
}

string Cellulaire::getNumero() const
{
	return numero_;
}

void Cellulaire::setNumero(string numero)
{
	numero_ = numero;
}

Personne* Cellulaire::getProprietaire() const
{
	return proprietaire_;
}

void Cellulaire::setProprietaire(Personne* personne)
{
	proprietaire_ = personne;
}

float Cellulaire::getPosition() const
{
	return gps_.getPosition();
}

void Cellulaire::setPosition(float position)
{
	gps_.setPosition(position);
	this->notifierChangement();
}

void Cellulaire::recevoirMessage(Message* message)
{
	if (message->getType() == NOTIFICATION_VISITEUR)
	{
		cout << "Notification visiteur recue par le cellulaire de " << proprietaire_->getPrenom() << "." << endl;
	}
}

string Cellulaire::obtenirNomClasse() const
{
	return typeid(Cellulaire).name();
}