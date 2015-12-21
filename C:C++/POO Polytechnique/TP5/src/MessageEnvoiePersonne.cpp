#include "MessageEnvoiePersonne.h"

using namespace std;

MessageEnvoiePersonne::MessageEnvoiePersonne(unsigned int src, unsigned int dest, TYPE_MESSAGE type, Personne* personne) : 
	Message(src, dest, type), personne_(personne) {}

Personne* MessageEnvoiePersonne::getPersonne() const {
	return personne_;
}

void MessageEnvoiePersonne::setPersonne(Personne* personne) {
	personne_ = personne;
}

string MessageEnvoiePersonne::obtenirNomClasse() const {
	return typeid(MessageEnvoiePersonne).name();
}