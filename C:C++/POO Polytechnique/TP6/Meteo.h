#ifndef METEO_H
#define METEO_H

#include "Observable.h"
#include <map>

class Meteo : public Observable
{
public:
	// Constructeur
	Meteo();

	// Get et set
	void ajouterVille(std::string ville, int temp, float vent);
	void retirerVille(std::string ville);
	int getTemp(std::string ville) const;
	float getVent(std::string ville) const;
	void setTemp(std::string ville, int temp);
	void setVent(std::string ville, float vent);

	// Autres m�thodes
	std::string obtenirNomClasse() const;

private:
	// Atributs
    std::map<std::string, std::pair<int, float> > mapTempVent_;
};
#endif
