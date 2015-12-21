#include "MessageEnvoiePersonne.h"
#include <typeinfo>

using namespace std;




MessageEnvoiePersonne::MessageEnvoiePersonne
(unsigned int src, unsigned int dest, TYPE_MESSAGE type, Personne * personne):
	Message(src, dest, type), personne_(personne)
{
}


std::string MessageEnvoiePersonne::obtenirNomClasse() const
{
	return (typeid(MessageEnvoiePersonne).name());
}
