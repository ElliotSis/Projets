#include "cellulaire.h"

#include "personne.h"

using namespace std;

Cellulaire::Cellulaire(unsigned int id, string numero) : ObjetConnecte(id), numero_(numero),
						personne_(nullptr), gps_() {}

Cellulaire::~Cellulaire() {}

string Cellulaire::obtenirNumero() const {
	return numero_;
}

void Cellulaire::modifierNumero(string numero) {
	numero_ = numero;
}

Personne* Cellulaire::obtenirPersonne() const {
	return personne_;
}

void Cellulaire::modifierPersonne(Personne* personne) {
	personne_ = personne;
}

float Cellulaire::obtenirPositionGps() const {
	return gps_.obtenirPosition();
}

void Cellulaire::modifierPositionGps(float position) {
	gps_.modifierPosition(position);
}

bool Cellulaire::estProche(float position) {
	return gps_.estProche(position);
}

bool operator==(const Cellulaire& cellulaire1, const Cellulaire& cellulaire2){
    return (cellulaire1.numero_ == cellulaire2.numero_ && *(cellulaire1.personne_) == *(cellulaire2.personne_));
}

bool operator<(const Cellulaire& cellulaire1, const Cellulaire& cellulaire2){
    return (cellulaire1.numero_ < cellulaire2.numero_);
}

ostream& operator<<(ostream& out, const Cellulaire& cellulaire1){
    out << "#" << cellulaire1.numero_ << "\t" << cellulaire1.personne_->obtenirNom() << ", " << cellulaire1.personne_->obtenirPrenom();
    return out;
}

void Cellulaire::seConnecter(Routeur* routeur){
	routeur->accepterConnexion(this);
	routeur_ = routeur;
	connecte_ = true;
}

void Cellulaire::recevoirMessage(Message& message){
    if(message.getType() == NOTIFICATION_VISITEUR)
        std::cout << "Notification visiteur reçue par le cellulaire " << numero_ << std::endl;
}
