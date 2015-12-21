#ifndef PERSONNE_H
#define PERSONNE_H

#include <string>
#include <iostream>
#include <list>
#include "enumTypes.h"

class Personne
{
public:
	// TP5
	Personne(std::string prenom, std::string nom, unsigned int age, TYPE_GUSTATIF preferenceGout);
	void ajouterAllergies(std::string allergie);
	bool estAllergique(std::string allergie);
	TYPE_GUSTATIF getTypeGustatif() const { return preferenceGout_; };
	TYPE_GUSTATIF setTypeGustatif(const TYPE_GUSTATIF preferenceGout)  { preferenceGout_ = preferenceGout; };

	// TP2
	bool operator==(const Personne& personne) const;
	bool operator< (const Personne& personne) const;
	friend std::ostream& operator<<(std::ostream& o, const Personne& personne);
	friend std::ostream& operator<<(std::ostream& o, Personne* personne){
		return o << *personne;
	}

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

	// TP5
	std::list<std::string> listeAllergies_;
	TYPE_GUSTATIF preferenceGout_;
};


#endif