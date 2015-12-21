#ifndef FRIGO_H
#define FRIGO_H

#include <algorithm>
#include <iterator>
#include <list>
#include <functional>

#include "enumTypes.h"
#include "ObjetConnecte.h"
#include "RestrictionAlimentaire.h"
#include "MessageEnvoiePersonne.h"

template <class T>
class Frigo : public ObjetConnecte
{
public:
	Frigo() {}
	Frigo(unsigned int id) : ObjetConnecte(id) {}

	void ajouterContenu(T* contenu) { listeContenu_.push_back(contenu); }

	template<class P> 
	bool retirerContenu(const P& predicat) {
		auto it = find_if(listeContenu_.begin(), listeContenu_.end(), predicat);
		std::cout << "L'Aliment " << predicat.getNomAliment() << " ";
		if (it != listeContenu_.end()) {
			listeContenu_.erase(it);
			std::cout << "a été retiré" << std::endl; 
			return true;
		} else {
			std::cout << "n'a pas été trouvé" << std::endl; 
			return false; 
		}
	}

	template<class P> 
	void suggererMenu(const P& predicat) {
		copy_if(listeContenu_.begin(), listeContenu_.end(), std::ostream_iterator<T*>(std::cout, "\n"), predicat);
	}

	template<class P, class PP> 
	void suggererMenu2(const P& predicat1, const PP& predicat2) {
		copy_if(listeContenu_.begin(), listeContenu_.end(), std::ostream_iterator<T*>(std::cout, "\n"), 
			[&] (Aliment* a) { 
				return predicat1(a) && predicat2(a); 
			});
	}

	void recevoirMessage(Message* message) {
		if (message->getType() == NOTIFICATION_VISITEUR && message->obtenirNomClasse() == typeid(MessageEnvoiePersonne).name()) {
			suggererMenu(RestrictionAlimentaire(((MessageEnvoiePersonne*)message)->getPersonne()));
		}
	}
	
private:
	std::list<T*> listeContenu_;
};

#endif