#include "cellulaire.h"

#include "personne.h"

Cellulaire::Cellulaire(const std::string numero, Personne* personne) :
						numero_(numero), 
						personne_(personne), gps_() {}

Cellulaire::~Cellulaire() {}

const std::string Cellulaire::obtenirNumero() const {
	return numero_;
}

void Cellulaire::modifierNumero(const std::string numero) {
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
