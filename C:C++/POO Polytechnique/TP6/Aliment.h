#ifndef ALIMENT_H
#define ALIMENT_H

#include <string>
#include <iostream>
#include "enumTypes.h"


using namespace std;

class Aliment
{
public:
	// Constructeurs et destructeurs
	Aliment(TYPE_GUSTATIF saveur, std::string nomAliment);
	~Aliment() {};

	// Get et Set
	std::string get_nomAliment() const ;
	TYPE_GUSTATIF get_saveur() const ;

	// Autres m�thodes
	bool operator==(const Aliment& aliment) const;
	friend ostream& operator<<(ostream& o, const Aliment & aliment);
	friend ostream& operator<<(ostream& o, Aliment *aliment);

private:
	// Attributs
	std::string nomAliment_;
	TYPE_GUSTATIF saveur_;
};


#endif  // ALIMENT_H


