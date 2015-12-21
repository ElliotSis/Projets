#include <cstdio>
#include "Personne.h"
#include <algorithm>



using namespace std;
///__________________________________________________________________________________________________________________________
/// TP2
///__________________________________________________________________________________________________________________________
bool Personne::operator==(const Personne& personne) const
{
	bool identique =
		(age_ == personne.age_) &&
		(prenom_ == personne.prenom_) &&
		(nom_ == personne.nom_);

	return identique;
}


bool Personne::operator< (const Personne& personne) const
{
	bool plusPetit;

	if (nom_ == personne.nom_)
	{
		plusPetit = prenom_ < personne.prenom_;
	}
	else
	{
		plusPetit = nom_ < personne.nom_;
	}

	return plusPetit;
}



ostream& operator<<(ostream& o, const Personne& personne)
{
	return o << personne.nom_ << " , " << personne.prenom_
		<< "\t-\t" << personne.age_ << " ans\t\t#" << personne.numeroCellulaire_ << "\n";
}






///__________________________________________________________________________________________________________________________
/// TP1
///__________________________________________________________________________________________________________________________

Personne::Personne() : age_(0), estALaMaison_(false)
{
}


Personne::Personne(string prenom, string nom, unsigned int age, TYPE_GUSTATIF preferenceGout)
	: nom_(nom), prenom_(prenom), age_(age), estALaMaison_(false), preferenceGout_(preferenceGout)
{
}

void Personne::ajouterAllergies(std::string allergie)
{
	// Ajouter l'allergie si elle n'est pas d�j� dans la liste
	if (!estAllergique(allergie))
	{
		listeAllergies_.push_back(allergie);
	}
}

bool Personne::estAllergique(std::string allergie)
{
	return (std::find(listeAllergies_.begin(), listeAllergies_.end(), allergie) != listeAllergies_.end());
}


Personne::~Personne()
{
}


string Personne::getNom() const
{
	return nom_;
}


void Personne::setNom(string nom)
{
	nom_ = nom;
}


string Personne::getPrenom() const
{
	return prenom_;
}


void Personne::setPrenom(string prenom)
{
	prenom_ = prenom;
}


unsigned int Personne::getAge() const
{
	return age_;
}


void Personne::setAge(unsigned int age)
{
	age_ = age;
}


bool Personne::estALaMaison() const
{
	return estALaMaison_;
}


void Personne::setEstALaMaison(bool estmaison)
{
	estALaMaison_ = estmaison;
}


void Personne::attribuerCellulaire(string numeroCellulaire)
{
	numeroCellulaire_ = numeroCellulaire;
}


string Personne::getNumeroCellulaire() const
{
	return numeroCellulaire_;
}
