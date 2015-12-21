#ifndef MESSAGEENVOIEPERSONNE_H
#define MESSAGEENVOIEPERSONNE_H

#include "Message.h"
#include "Personne.h"
#include <string>

class MessageEnvoiePersonne :
	public Message
{
public:
	// Constructeur
	MessageEnvoiePersonne(unsigned int src, unsigned int dest, TYPE_MESSAGE type, Personne* personne);
	
	// Get et Set
	Personne* getPersonne() { return personne_; };

	// Autres m�thodes
	virtual std::string obtenirNomClasse() const;
	

private:
	// Attributs
	Personne* personne_;
};



#endif // MESSAGEENVOIEPERSONNE_H


