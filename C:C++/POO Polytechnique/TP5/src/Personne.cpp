#include <cstdio>
#include "Personne.h"



using namespace std;

///__________________________________________________________________________________________________________________________
/// TP5
///__________________________________________________________________________________________________________________________

// TP5 A COMPLETER
Personne::Personne(string nom, string prenom, unsigned int age, TYPE_GUSTATIF preferenceGout) : 
	nom_(nom), prenom_(prenom), age_(age), preferenceGout_(preferenceGout) {}

TYPE_GUSTATIF Personne::getPreferenceGout() const {
	return preferenceGout_;
}

void Personne::setPreferenceGout(TYPE_GUSTATIF preferenceGout) {
	preferenceGout_ = preferenceGout;
}

bool Personne::verifierAllergies(std::string allergie) const {
	return (find(listeAllergies_.begin(), listeAllergies_.end(), allergie) != listeAllergies_.end());
}

void Personne::ajouterAllergie(std::string allergie) {
	if (!verifierAllergies(allergie)) {
		listeAllergies_.push_back(allergie);
	}
}



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