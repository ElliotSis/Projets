/*
Fichier: gps.cpp
Auteur(s): Benjamin De Leener
Date de creation: 26 aout 2015
Date de modification: 28 aout 2015
Description: Cette classe represente un systeme GPS. Elle permet de localiser une personne dans l'espace, grace a un simulateur de position.
*/

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "gps.h"

#define PROXIMITE 20

using namespace std;

GPS::GPS() : position_(0.0)
{
	srand((time(NULL)));
	time(&temps_);  /* get current time; same as: timer = time(NULL)  */
}


GPS::GPS(float position) : position_(position)
{
	srand((time(NULL)));
	time(&temps_);  /* get current time; same as: timer = time(NULL)  */
}


GPS::~GPS()
{
}


bool GPS::estProche(float position)
{
	bool resultat_position = false;
	if (position_ >= position - PROXIMITE && position_ <= position + PROXIMITE)
		resultat_position = true;
	return resultat_position;
}


float GPS::getPosition() const
{
	return position_;
}


void GPS::setPosition(float position)
{
	position_ = position;
}
