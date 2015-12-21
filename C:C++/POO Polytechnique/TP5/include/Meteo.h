#ifndef METEO_H
#define METEO_H

#include <iostream>
#include <map>
#include <string>
#include <utility>

#include "Observable.h"

class Meteo : public Observable
{
public:
	Meteo();

// TP5 A COMPLETER

	std::string obtenirNomClasse() const;
	void ajouterVille(std::string ville, double temperature, double vent = 0.0);
	void enleverVille(std::string ville);
	std::pair<double,double> getTempVent(std::string ville) const;
	void setTempVent(std::string ville, double temperature, double vent = 0.0);
	friend std::ostream& operator<<(std::ostream& out, const Meteo& meteo);

private:
	std::map<std::string, std::pair<double,double>> mapTempVent_;

};
#endif