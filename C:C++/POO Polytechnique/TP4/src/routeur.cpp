#include "routeur.h"
#include "objetConnecte.h"

#include <iostream>

Routeur::Routeur(){};

void Routeur::accepterConnexion(ObjetConnecte* objetConnecte){
    std::cout << "Objet connecte : " << objetConnecte->obtenirId() << std::endl;
    objetsConnectes_.push_back(objetConnecte);
}

void Routeur::retirerConnexion(unsigned int id){
	for(std::vector<ObjetConnecte*>::iterator it = objetsConnectes_.begin(); it != objetsConnectes_.end(); ++it){
		if(*it != nullptr && (*it)->obtenirId() == id){
			std::cout << "Objet deconnecté : " << id << std::endl;
			retirerElement(it);
			return;
		}
	}
}

void Routeur::acheminerMessage(Message& message){
    std::cout << "Routeur : Acheminement du message de " << message.getSrc() << " à " << message.getDest() << std::endl;
    for(std::vector<ObjetConnecte*>::iterator it = objetsConnectes_.begin(); it != objetsConnectes_.end(); ++it){
        if((*it != nullptr) && ((*it)->obtenirId() == message.getDest() || message.getDest() == 0)){
            (*it)->recevoirMessage(message);
            if(message.getDest() != 0)
                break;
        }
    }
}

void Routeur::retirerElement(std::vector<ObjetConnecte *>::iterator it) {
	*it = objetsConnectes_.back();
    objetsConnectes_.pop_back();
}

