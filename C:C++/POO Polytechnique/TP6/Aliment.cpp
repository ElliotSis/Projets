#include <cstdio>
#include "Aliment.h"



Aliment::Aliment(TYPE_GUSTATIF saveur, std::string nomAliment): saveur_(saveur), nomAliment_(nomAliment)
{

}


std::string Aliment::get_nomAliment() const
{ 
	return nomAliment_;
}


TYPE_GUSTATIF Aliment::get_saveur() const 
{
	return saveur_; 
}

bool Aliment::operator==(const Aliment & aliment) const
{
	return ((saveur_ == aliment.saveur_) && (nomAliment_ == aliment.nomAliment_));
}



// Opérateur <<
ostream& operator<<(ostream& o, const Aliment& aliment)
{
	return o << aliment.get_nomAliment();
}

ostream& operator<<(ostream& o, Aliment *aliment)
{
	return o << *aliment;
}

