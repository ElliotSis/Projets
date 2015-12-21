#include "routeur.h"
#include "maison.h"
#include "cellulaire.h"
#include "chauffage.h"
#include "personne.h"

#include <iostream>

Routeur::Routeur() : maison_(nullptr) {};

void Routeur::retirerConnexion(unsigned int id){
	if(maison_ != nullptr && maison_->obtenirId() == id){
		std::cout << "La maison est maintenant déconnectée..." << std::endl;
		maison_ = nullptr;
		return;
	}
	for(std::vector<Cellulaire*>::iterator it = cellulaires_.begin(); it != cellulaires_.end(); ++it){
		if(*it != nullptr && (*it)->obtenirId() == id){
			std::cout << "Cellulaire deconnecté : " << id << std::endl;
            std::cout << "Au revoir " << (*it)->obtenirPersonne()->obtenirPrenom() << " "
                << (*it)->obtenirPersonne()->obtenirNom() << std::endl << std::endl;
			retirerElement(it);
			return;
		}
	}
	for(std::vector<Chauffage*>::iterator it = chauffages_.begin(); it != chauffages_.end(); ++it){
		if(*it != nullptr && (*it)->obtenirId() == id){
			std::cout << "Chauffage deconnecté : " << id << std::endl;
			retirerElement(it);
			return;
		}
	}
}

void Routeur::acheminerMessage(Message& message){
    std::cout << "Routeur : Acheminement du message de " << message.getSrc() << " à " << message.getDest() << std::endl;
	bool trouve = false;
	for(std::vector<Cellulaire*>::iterator it = cellulaires_.begin(); it != cellulaires_.end(); ++it){
		if(*it != nullptr && ((*it)->obtenirId() == message.getDest() || message.getDest() == 0)){
			(*it)->recevoirMessage(message);
			trouve = true;
			if(message.getDest() != 0)
				break;
			trouve = false;
		}
	}
	if(!trouve) {
		for (std::vector<Chauffage *>::iterator it = chauffages_.begin(); it != chauffages_.end(); ++it) {
			if (*it != nullptr && ((*it)->obtenirId() == message.getDest() || message.getDest() == 0)) {
				(*it)->recevoirMessage(message);
				trouve = true;
				if (message.getDest() != 0)
					return;
			}
		}
	}
}

void Routeur::accepterConnexion(Maison* maison){
	if(maison_ != nullptr){
		std::cout << "Une maison est déjà connectée à ce routeur" << std::endl;
	} else {
        std::cout << "Maison connectée : " << maison->obtenirId() << std::endl;
		maison_ = maison;
	}
}

void Routeur::accepterConnexion(Cellulaire* cellulaire){
	if(cellulaire == nullptr){
		std::cout << "Ce cellulaire est null, rien n'est fait" << std::endl;
		return;
	}
	for(std::vector<Cellulaire*>::iterator it = cellulaires_.begin(); it != cellulaires_.end(); ++it){
		if(*it != nullptr && (*it)->obtenirId() == cellulaire->obtenirId()){
			std::cout << "Cellulaire déjà connecté : " << cellulaire->obtenirId() << std::endl;
			return;
		}
	}
	std::cout << "Cellulaire connecté : " << cellulaire->obtenirId() << std::endl;
    std::cout << "Bonjour " << cellulaire->obtenirPersonne()->obtenirPrenom() << " "
                << cellulaire->obtenirPersonne()->obtenirNom() << std::endl << std::endl;
	cellulaires_.push_back(cellulaire);
}
void Routeur::accepterConnexion(Chauffage* chauffage){
	if(chauffage == nullptr){
		std::cout << "Ce chauffage est null, rien n'est fait" << std::endl;
		return;
	}
	for(std::vector<Chauffage*>::iterator it = chauffages_.begin(); it != chauffages_.end(); ++it){
		if(*it != nullptr && (*it)->obtenirId() == chauffage->obtenirId()){
			std::cout << "Chauffage déjà connecté : " << chauffage->obtenirId() << std::endl;
			return;
		}
	}
	std::cout << "Chauffage connecté : " << chauffage->obtenirId() << std::endl;
	chauffages_.push_back(chauffage);
}

const std::vector<Cellulaire*>& Routeur::obtenirCellulaires() const{
	return cellulaires_;
}

const Maison* Routeur::obtenirMaison() const{
	return maison_;
}

void Routeur::retirerElement(std::vector<Cellulaire *>::iterator it) {
	*it = cellulaires_.back();
	cellulaires_.pop_back();
}

void Routeur::retirerElement(std::vector<Chauffage *>::iterator it) {
	*it = chauffages_.back();
	chauffages_.pop_back();
}
