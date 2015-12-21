#include "RestrictionAlimentaire.h"

using namespace std;

RestrictionAlimentaire::RestrictionAlimentaire(const Personne* personne) : personne_(personne) {}

bool RestrictionAlimentaire::operator() (const Aliment* aliment) const {
	return (aliment->getSaveur() == personne_->getPreferenceGout() && !personne_->verifierAllergies(aliment->getNomAliment()));
}