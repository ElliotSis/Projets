/*
Fichier: gps.h
Auteur(s): Benjamin De Leener
Date de creation: 26 aout 2015
Date de modification: 28 aout 2015
Description: Cette classe represente un systeme GPS. Elle permet de localiser une personne dans l'espace, grace a un simulateur de position.
*/
//  Modified by Dominique Beaini on 2015-09-18.
//

#ifndef inf1010_tp1_gps_h
#define inf1010_tp1_gps_h

#include <ctime>

class GPS
{
public:
	// Constructeur par defaut
	GPS();

	// Constructeur par parametre
	GPS(float position);

	// Destructeur
	~GPS();

	// La fonction estProche() permet de savoir si le GPS est proche d'une position. La notion de proximite est donnee par une variable constante, dans le fichier cpp.
	bool estProche(float position);

	// modificateur et accesseur de la position
	float getPosition() const;
	void setPosition(float position);

private:
	// Attribut de position
	float position_;

	// Attribut de temps. Permet au simulateur de position de fonctionner.
	time_t temps_;
};

#endif