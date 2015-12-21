#ifndef FRIGO_H
#define FRIGO_H



#include "ObjetConnecte.h"
#include "RestrictionAlimentaire.h"
#include "Message.h"
#include "MessageEnvoiePersonne.h"
#include "memeAliment.h"
#include <list>
#include <algorithm>
#include <iostream>
#include <iterator>


template <typename T>
class Frigo :	public ObjetConnecte
{
public:
	// Constructeurs et destructeurs
	Frigo(unsigned int id);
	~Frigo() {};

	// Get et Set

	// Autres méthodes
	void ajouterContenu(T *contenu);
	template<typename Predicate>
	bool retirerContenu(const Predicate& memeAliment);
	template<typename Predicate>
	void suggererMenu(const Predicate& restriction);
	virtual void recevoirMessage(Message* message);

private:
	// Attributs
	std::list<T*> listeContenu_;
};



using namespace std;


// Constructeur par parametre
template<typename T>
Frigo<T>::Frigo(unsigned int id) : ObjetConnecte(id)
{

}


// Ajouter le contenu
template<typename T>
void Frigo<T>::ajouterContenu(T *contenu)
{
	listeContenu_.push_back(contenu);
}


template<typename T>
template<typename Predicate>
bool Frigo<T>::retirerContenu(const Predicate &p)
{
	
	size_t sizeBefore = listeContenu_.size();
	listeContenu_.remove_if(p);
	bool trouve = (sizeBefore != listeContenu_.size());
	// Afficher le message
	if (trouve)
		cout << "L'aliment " << p.getNomAliment() << " a ete retire\n";
	else
		cout << "L'aliment " << p.getNomAliment() << " n'a pas ete trouve\n";

	// Quitter
	return trouve;
}


template<typename T>
template<typename Predicate>
void Frigo<T>::suggererMenu(const Predicate &p)
{
	// Affiche le menu � l'aide de copy_if
	cout << "Le menu suggere est : \n";
	copy_if(
		listeContenu_.begin(),
		listeContenu_.end(),
		ostream_iterator<T*>(cout, "\n"),
		p
		);
}


template<typename T>
void Frigo<T>::recevoirMessage(Message *message)
{
	// Si le message est du bon type
	MessageEnvoiePersonne *msgCast = dynamic_cast<MessageEnvoiePersonne*>(message);
	if (message->getType() == NOTIFICATION_VISITEUR && msgCast != NULL)
	{
		// Sugg�rer le menu pour la personne concern�e
        if (msgCast->getPersonne() != 0)
		{
			RestrictionAlimentaire restriction(msgCast->getPersonne());
			suggererMenu(restriction);
		}
	}
}


#endif //FRIGO_H
