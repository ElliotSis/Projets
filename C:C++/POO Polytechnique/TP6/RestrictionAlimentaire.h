#ifndef RESTRICTIONALIMENTAIRE_H
#define RESTRICTIONALIMENTAIRE_H


#include "Personne.h"
#include "Aliment.h"

class RestrictionAlimentaire
{
public:
	RestrictionAlimentaire(Personne* personne) : personne_(personne) {};
	bool operator() (Aliment *aliment);


private:
	Personne* personne_;

};



#endif // RESTRICTIONALIMENTAIRE_H