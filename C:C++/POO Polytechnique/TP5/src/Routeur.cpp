#include "Routeur.h"
#include <iostream>
// TP5 A COMPLETER

using namespace std;

Routeur::Routeur() {}

void Routeur::accepterConnexion(ObjetConnecte* obj) {
	objetsConnectes_.insert(make_pair(obj->getId(), obj));
}

bool Routeur::retirerConnexion(unsigned int id) {
	auto it = objetsConnectes_.find(id);
	if (it != objetsConnectes_.end()) {
		objetsConnectes_.erase(it);
		return true;
	}
	return false;
}

void Routeur::acheminerMessage(Message* message) const {
	cout << "Routeur : Acheminement d'un message de " << message->getSrc() << " vers " << message->getDest() << endl;
	if (message->getDest() == 0) {
		for_each(objetsConnectes_.begin(), objetsConnectes_.end(), 
			[&] (pair<unsigned int, ObjetConnecte*> p) {
				p.second->recevoirMessage(message);
			});
	} else {
		ObjetConnecte* dest = getObjetConnecte(message->getDest());
		dest->recevoirMessage(message);
	}
}

ObjetConnecte* Routeur::getObjetConnecte(unsigned int id) const {
	auto it = objetsConnectes_.find(id);
	if (it != objetsConnectes_.end()) {
		return it->second;
	}
}