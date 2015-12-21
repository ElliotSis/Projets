#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <vector>
#include <string>
#include "Observateur.h"

class Observable
{
public:
	void ajouterObservateur(Observateur*);
	void notifierChangement();
	virtual std::string obtenirNomClasse() const;
private:
	std::vector<Observateur*> listeObservateurs_;
};
#endif