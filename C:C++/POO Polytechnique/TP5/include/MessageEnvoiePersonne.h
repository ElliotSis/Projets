#include "Message.h"

#ifndef MESSAGEENVOIEPERSONNE_H
#define MESSAGEENVOIEPERSONNE_H

#include "enumTypes.h"
#include "Personne.h"

class MessageEnvoiePersonne : public Message
{
public:
	MessageEnvoiePersonne(unsigned int src, unsigned int dest, TYPE_MESSAGE type, Personne* personne);
	Personne* getPersonne() const;
	void setPersonne(Personne* peronne);
	std::string obtenirNomClasse() const;
private:
	// Attribut représentant la personne
	Personne* personne_;
};

#endif