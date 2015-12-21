#include "chauffage.h"

#include <iostream>

Chauffage::Chauffage(unsigned int id) : ObjetConnecte(id), estAllume_(false), automatique_(false) {}

Chauffage::~Chauffage() {}

bool Chauffage::obtenirEstAllume() const {
	return estAllume_;
}

void Chauffage::allume() {
	//if(!estAllume_) {
	//	cout << "Le chauffage est maintenant allumé" << endl;
	//}
	estAllume_ = true;
}

void Chauffage::eteindre() {
	//if(estAllume_) {
	//	cout << "Le chauffage est maintenant éteint" << endl;
	//}
	estAllume_ = false;
}

Chauffage& Chauffage::operator++() {
	allume();
	return *this;
}

Chauffage& Chauffage::operator--() {
	eteindre();
	return *this;
}

bool Chauffage::obtenirAutomatique() const{
	return automatique_;
}

void Chauffage::modifierAutomatique(bool automatique){
	automatique_ = automatique;
}

void Chauffage::seConnecter(Routeur* routeur){
	routeur->accepterConnexion(this);
	routeur_ = routeur;
	connecte_ = true;
}

void Chauffage::recevoirMessage(Message& message){
	if(message.getType() == ALLUMER_CHAUFFAGE && !estAllume_){
		allume();
		std::cout << "Le chauffage id:" << id_ << " est maintenant allumé" << std::endl;
	} else if(message.getType() == ETEINDRE_CHAUFFAGE && estAllume_){
		eteindre();
		std::cout << "Le chauffage id:" << id_ << " est maintenant éteint" << std::endl;
	} else if(message.getType() == ALLUMAGE_AUTOMATIQUE && automatique_){
		allume();
		std::cout << "Le chauffage id:" << id_ << " est maintenant allumé de manière auto" << std::endl;
	}
}
