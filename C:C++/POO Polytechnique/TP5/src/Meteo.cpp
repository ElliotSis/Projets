#include "Meteo.h"

#include <iterator>

using namespace std;

Meteo::Meteo()
{
}

// TP5 A COMPLETER
string Meteo::obtenirNomClasse() const
{
	return typeid(Meteo).name();
}

void Meteo::ajouterVille(string ville, double temperature, double vent) {
	if (mapTempVent_.find(ville) == mapTempVent_.end()) {
		mapTempVent_.insert(make_pair(ville, make_pair(temperature, vent)));
	}
	this->notifierChangement();
}

void Meteo::enleverVille(string ville) {
	map<string, pair<double, double>>::iterator it = mapTempVent_.find(ville);
	if (it != mapTempVent_.end()) {
		mapTempVent_.erase(it);
	}
	this->notifierChangement();
}

pair<double,double> Meteo::getTempVent(string ville) const {
	map<string, pair<double, double>>::const_iterator it = mapTempVent_.find(ville);
	if (it != mapTempVent_.end()) {
		return it->second;
	} else {
		cout << "La ville n'existe pas dans la map !" << endl;
	}
}
void Meteo::setTempVent(string ville, double temperature, double vent) {
	map<string, pair<double, double>>::iterator it = mapTempVent_.find(ville);
	if (it != mapTempVent_.end()) {
		it->second.first = temperature;
		it->second.second = vent;
	} else {
		mapTempVent_.insert(make_pair(ville, make_pair(temperature, vent)));
	}
	this->notifierChangement();
}

ostream& operator<<(ostream& out, const Meteo& meteo) {
	for_each(meteo.mapTempVent_.begin(), meteo.mapTempVent_.end(), 
		[&] (pair<string, pair<double,double>> p) { 
			out << p.first <<  " :  température "  << p.second.first << ", vent " << p.second.second << endl;
		});
	return out;
}