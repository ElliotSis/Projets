#include <iostream>
#include "objetConnecte.h"
#include "routeur.h"

ObjetConnecte::ObjetConnecte(unsigned int id) : id_(id), connecte_(false),
				routeur_(nullptr) {}

void ObjetConnecte::seConnecter(Routeur* routeur){
    routeur->accepterConnexion(this);
    routeur_ = routeur;
    connecte_ = true;
}

void ObjetConnecte::seDeconnecter(){
	if(connecte_) {
		routeur_->retirerConnexion(id_);
		connecte_ = false;
	}
}

unsigned int ObjetConnecte::obtenirId() const{
	return id_;
}

bool ObjetConnecte::estConnecte() {
    return connecte_;
}

void ObjetConnecte::envoyerMessage(Message &message) {
    routeur_->acheminerMessage(message);
}

void ObjetConnecte::recevoirMessage(Message &message) {
    return;
}