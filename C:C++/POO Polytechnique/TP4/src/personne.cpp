#include "personne.h"

using namespace std;

Personne::Personne(string prenom, string nom, unsigned int age, string numeroCellulaire, bool estMaison) : prenom_(prenom), 
					nom_(nom), numeroCellulaire_(numeroCellulaire), age_(age),
					estALaMaison_(estMaison) {}

Personne::~Personne() {}

string Personne::obtenirPrenom() const {
	return prenom_;
}

void Personne::modifierPrenom(string prenom) {
	prenom_ = prenom;
}

string Personne::obtenirNom() const {
	return nom_;
}

void Personne::modifierNom(string nom) {
	nom_ = nom;
}

string Personne::obtenirNumeroCelullaire() const {
	return numeroCellulaire_;
}

void Personne::modifierNumeroCelullaire(string numeroCellulaire) {
	numeroCellulaire_ = numeroCellulaire;
}

unsigned int Personne::obtenirAge() const {
	return age_;
}

void Personne::modifierAge(unsigned int age) {
	age_ = age;
}

bool Personne::obtenirEstALaMaison() const {
	return estALaMaison_;
}

void Personne::modifierEstALaMaison(bool estALaMaison) {
	estALaMaison_ = estALaMaison;
}

bool operator==(Personne const& personne1, Personne const& personne2){
	return (personne1.prenom_ == personne2.prenom_ && personne1.nom_ == personne2.nom_ && personne1.age_ == personne2.age_);
}

bool operator<(Personne const& personne1, Personne const& personne2){
	if (personne1.nom_ < personne2.nom_) {
		return true;
	}
	else {
		return (personne1.nom_ == personne2.nom_ && personne1.prenom_ < personne2.prenom_);
	}
}

ostream& operator<<(ostream& out, Personne const& personne){
	out << personne.nom_ << " , " << personne.prenom_ << "\t-\t" << personne.age_ << " ans \t\t #" << personne.numeroCellulaire_;
	return out;
}
