#ifndef PERSONNE_H
#define PERSONNE_H

#include <list>
#include <string>
#include <iostream>

#include "enumTypes.h"

class Personne
{
public:
// TP5 A COMPLETER
	Personne(std::string nom, std::string prenom, unsigned int age, TYPE_GUSTATIF preferenceGout);
	TYPE_GUSTATIF getPreferenceGout() const;
	void setPreferenceGout(TYPE_GUSTATIF preferenceGout);
	bool verifierAllergies(std::string allergie) const;
	void ajouterAllergie(std::string allergie);


	// TP2
	bool operator==(const Personne& personne) const;
	bool operator< (const Personne& personne) const;
	friend std::ostream& operator<<(std::ostream& o, const Personne& personne);

	// TP1
	Personne();
	
	~Personne();

	std::string getNom() const;
	void setNom(std::string nom);
	std::string getPrenom() const;
	void setPrenom(std::string prenom);
	unsigned int getAge() const;
	void setAge(unsigned int age);

	bool estALaMaison() const;
	void setEstALaMaison(bool estmaison);

	void attribuerCellulaire(std::string numeroCellulaire);
	std::string getNumeroCellulaire() const;




private:
	std::string nom_;
	std::string prenom_;
	unsigned int age_;
	bool estALaMaison_;
	std::string numeroCellulaire_;
	std::list<std::string> listeAllergies_;
	TYPE_GUSTATIF preferenceGout_;
};


#endif