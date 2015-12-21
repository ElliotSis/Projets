//
//  maison.h
//  inf1010_tp1
//
//  Created by Benjamin De Leener on 2015-08-26.
//  Modified by Dominique Beaini on 2015-09-18.
//  Modified by Karim Keddam on 2015-09-26.
//

#ifndef MAISON_H
#define MAISON_H

#include <vector>
#include <string>
#include "Personne.h"
#include "ObjetConnecte.h"
#include "Cellulaire.h"
#include "Observateur.h"

class Maison : public ObjetConnecte, public Observateur
{
public:
	// M�thodes TP4
	void mettreAJour(Observable*);

	// !!!!!!!!!! A FAIRE !!!!!!!!!!!!
	// Vous devez modifier le constructeur pour permettre l'envoie de signaux.
    Maison(unsigned int id, const std::string& adresse, float position, std::string ville);
	void recevoirMessage(Message* message) {};

	// M�thodes TP2:
	~Maison();

	void ajouterOccupant(Personne* personne);

	// cette fonction permet de savoir si une personne, passee en parametre, fait partie des occupants de la maison.
	bool estOccupant(const Personne* personne) const;

	// cette fonction permet de savoir si la maison est vide, c'est-�-dire si aucun occupant n'est present dans la maison.
	bool estVide() const;

	// M�thodes TP1:
	// accesseurs et modificateurs
	std::string getAdresse() const;
	void setAdresse(std::string adresse);

	float getPosition() const;
	void setPosition(float position);

private:
	//TP5
	std::string ville_;

	//TP4
	int temperatureExterieure_;
	int temperatureAGarder_;

	// TP1 et TP2
	std::string adresse_;
	std::list<Personne*> occupants_;

	// position de la maison. La maison est positionnee simplement selon un chiffre.
	float position_;
};

#endif
