#include "ObjetConnecte.h"
#include "Routeur.h"

using namespace std;

// !!!!!!!!!! A FAIRE !!!!!!!!!!!!
// Vous devez modifier la classe pour que le fichier .cpp soit compatible avec le fichier .h
	
ObjetConnecte::ObjetConnecte(unsigned int id) : QObject(), id_(id), estConnecte_(false)
{
}

unsigned int ObjetConnecte::getId() const
{
	return id_;
}

bool ObjetConnecte::seConnecter(Routeur* routeur)
{
	if (!estConnecte_)
	{
		routeur->accepterConnexion(this);
		routeur_ = routeur;
		estConnecte_ = true;
		return true;
	}
	return false;
}

void ObjetConnecte::seDeconnecter()
{
	if (estConnecte_)
	{
		routeur_->retirerConnexion(id_);
		routeur_ = NULL;
		estConnecte_ = false;
	}
}

void ObjetConnecte::envoyerMessage(Message *message)
{
	if (estConnecte_)
	{
		routeur_->acheminerMessage(message);
	}
}

void ObjetConnecte::setIsConnected(bool value)
{
	estConnecte_ = value;
}

bool ObjetConnecte::isConnected() const
{
	return estConnecte_;
}

