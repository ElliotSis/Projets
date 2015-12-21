#ifndef ALIMENT_H
#define ALIMENT_H

#include <iostream>
#include <string>

#include "enumTypes.h"

class Aliment
{
public:
	Aliment(std::string nomAliment, TYPE_GUSTATIF saveur);
	std::string getNomAliment() const;
	TYPE_GUSTATIF getSaveur() const;
	void setNomAliment(std::string nomAliment);
	void setSaveur(TYPE_GUSTATIF saveur);
	friend bool operator==(const Aliment& a, const Aliment& b);
	friend std::ostream& operator<<(std::ostream& out, const Aliment& a);
	friend std::ostream& operator<<(std::ostream& out, const Aliment* a);

private:
	std::string nomAliment_;
	TYPE_GUSTATIF saveur_;
};

#endif