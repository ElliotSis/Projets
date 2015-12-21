#include "chauffage.h"

#include <iostream>

using namespace std;

Chauffage::Chauffage() : estAllume_(false) {}

Chauffage::~Chauffage() {}

bool Chauffage::obtenirEstAllume() const {
	return estAllume_;
}

void Chauffage::allume() {
	if(!estAllume_) {
		cout << "Le chauffage est maintenant allumé" << endl;
	}
	estAllume_ = true;
}

void Chauffage::eteindre() {
	if(estAllume_) {
		cout << "Le chauffage est maintenant éteint" << endl;
	}
	estAllume_ = false;
}
