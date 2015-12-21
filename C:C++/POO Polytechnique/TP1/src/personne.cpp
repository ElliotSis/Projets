#include "personne.h"

Personne::Personne(const std::string prenom, const std::string nom,
					unsigned int age, const std::string numeroCellulaire, bool estMaison) : prenom_(prenom), 
					nom_(nom), numeroCellulaire_(numeroCellulaire), age_(age),
					estALaMaison_(estMaison) {}

Personne::~Personne() {}

const std::string Personne::obtenirPrenom() const {
	return prenom_;
}

void Personne::modifierPrenom(const std::string prenom) {
	prenom_ = prenom;
}

const std::string Personne::obtenirNom() const {
	return nom_;
}

void Personne::modifierNom(const std::string nom) {
	nom_ = nom;
}

const std::string Personne::obtenirNumeroCelullaire() const {
	return numeroCellulaire_;
}

void Personne::modifierNumeroCelullaire(const std::string numeroCellulaire) {
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
