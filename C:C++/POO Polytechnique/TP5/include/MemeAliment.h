#ifndef MEMEALIMENT_H
#define MEMEALIMENT_H

#include <string>

#include "Aliment.h"

class MemeAliment
{
public:
	MemeAliment(const Aliment* aliment);
	std::string getNomAliment() const;
	bool operator() (const Aliment* aliment) const;
	
private:
	const Aliment* aliment_;
};

#endif