#include "Observable.h"
#include <typeinfo>

using namespace std;

void Observable::ajouterObservateur(Observateur* obs)
{
	listeObservateurs_.push_back(obs);
}

void Observable::notifierChangement()
{
	for (size_t i = 0; i < listeObservateurs_.size(); i++) {
		listeObservateurs_[i]->mettreAJour(this);
	}
}

string Observable::obtenirNomClasse() const
{
	return typeid(Observable).name();
}
