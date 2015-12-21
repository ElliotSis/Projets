#ifndef MEMEALIMENT_H
#define MEMEALIMENT_H


#include "Aliment.h"
#include <string>

class MemeAliment
{
public:
	MemeAliment(Aliment* aliment) : aliment_(aliment) {};
	bool operator() (Aliment *aliment);
	std::string getNomAliment() const { return aliment_->get_nomAliment(); };

private:
	Aliment* aliment_;

};



#endif // MEMEALIMENT_H