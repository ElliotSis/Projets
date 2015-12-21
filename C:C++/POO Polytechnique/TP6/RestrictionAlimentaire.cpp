#include "RestrictionAlimentaire.h"




bool RestrictionAlimentaire::operator()(Aliment *aliment)
{
	// V�rifie si la personne aime l'aliment et qu'elle n'y est pas allergique
	bool bonAliment = 
		((aliment->get_saveur() == personne_->getTypeGustatif()) 
			&& (!personne_->estAllergique(aliment->get_nomAliment())));
	
	return bonAliment;
}
