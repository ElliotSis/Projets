#ifndef ROUTEUR_H
#define ROUTEUR_H

#include <vector>
#include "Cellulaire.h"
#include "Chauffage.h"
#include "Maison.h"
#include "Message.h"
#include <map>

class Routeur
{
public:
	Routeur();
	void accepterConnexion(ObjetConnecte* obj);
	bool retirerConnexion(unsigned int id);
	void acheminerMessage(Message* message) const;

private:
	std::map<unsigned int, ObjetConnecte*> connexions_;
};

#endif