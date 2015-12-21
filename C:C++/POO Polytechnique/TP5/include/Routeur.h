#ifndef ROUTEUR_H
#define ROUTEUR_H

#include <map>
#include <vector>
#include "Cellulaire.h"
#include "Chauffage.h"
#include "Maison.h"
#include "Message.h"

class Routeur
{
public:
	// TP5 A COMPLETER!
	Routeur();
	void accepterConnexion(ObjetConnecte* obj);
	bool retirerConnexion(unsigned int id);
	void acheminerMessage(Message* message) const;

	ObjetConnecte* getObjetConnecte(unsigned int id) const;

private:
	std::map<unsigned int, ObjetConnecte*> objetsConnectes_;
	
};

#endif