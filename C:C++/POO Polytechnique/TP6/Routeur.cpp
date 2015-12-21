#include "Routeur.h"
#include <iostream>
#include <map>

using namespace std;

Routeur::Routeur()
{
}

void Routeur::accepterConnexion(ObjetConnecte* obj)
{
	if (obj == NULL || connexions_.find(obj->getId()) != connexions_.end())
	{
		return;
	}
	connexions_[obj->getId()] = obj;
}

bool Routeur::retirerConnexion(unsigned int id)
{
	if (connexions_.find(id) == connexions_.end())
	{
		return false;
	}
	connexions_.erase(id);
	return true;
}

void Routeur::acheminerMessage(Message* message) const
{
	std::cout << "Routeur: Acheminement d'un message de " << message->getSrc() << " vers " << message->getDest() << "." << std::endl;
	if (message->getDest() == 0)
	{
		for (map<unsigned int, ObjetConnecte*>::const_iterator it = connexions_.begin(); it != connexions_.end(); ++it)
		{
			it->second->recevoirMessage(message);
		}
	}
	else
	{
		connexions_.find(message->getDest())->second->recevoirMessage(message);
	}
}