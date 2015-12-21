#ifndef CELLULAIRE_H
#define CELLULAIRE_H

#include <string>
#include "Personne.h"
#include "ObjetConnecte.h"
#include "gps.h"
#include "Observable.h"

class Cellulaire : public ObjetConnecte, public Observable
{
public:
	Cellulaire(unsigned int id);
	Cellulaire(unsigned int id, std::string numero);
	~Cellulaire();
	void recevoirMessage(Message* message);
	std::string obtenirNomClasse() const;

	// TP1
	bool estProche(float position);
	std::string getNumero() const;
	void setNumero(std::string numero);
	Personne* getProprietaire() const;
	void setProprietaire(Personne* personne);
	float getPosition() const;
	void setPosition(float position);

private:
	std::string numero_;
	Personne* proprietaire_;
	GPS gps_;
};

#endif
