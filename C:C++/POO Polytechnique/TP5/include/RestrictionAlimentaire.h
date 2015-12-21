#ifndef RESTRICTIONALIMENTAIRE_H
#define RESTRICTIONALIMENTAIRE_H

#include "Aliment.h"
#include "Personne.h"

class RestrictionAlimentaire
{
public:
	RestrictionAlimentaire(const Personne* personne);
	bool operator() (const Aliment* aliment) const;
	

private:
	const Personne* personne_;
};

#endif