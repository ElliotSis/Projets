#include "memeAliment.h"

bool MemeAliment::operator()(Aliment *aliment)
{
	// Vérifie si la personne aime l'aliment et qu'elle n'y est pas allergique
	bool bonAliment = (*aliment_) == (*aliment);

	return bonAliment;
}

