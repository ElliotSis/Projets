#include "Meteo.h"
#include <typeinfo>
#include <climits>

using namespace std;

Meteo::Meteo()
{
}

void Meteo::ajouterVille(std::string ville, int temp, float vent)
{
	mapTempVent_[ville] = pair<int, float>(temp, vent);
	this->notifierChangement();
}
void Meteo::retirerVille(std::string ville)
{
	mapTempVent_.erase(ville);
	this->notifierChangement();
}
int Meteo::getTemp(std::string ville) const
{
    map<string, pair<int, float> >::const_iterator it = mapTempVent_.find(ville);
	if (it == mapTempVent_.end())
	{
		return -1 * INT_MAX;
	}
	return it->second.first;
}
float Meteo::getVent(std::string ville) const
{
    map<string, pair<int, float> >::const_iterator it = mapTempVent_.find(ville);
	if (it == mapTempVent_.end())
	{
		return -1*INT_MAX;
	}
	return it->second.second;
}
void Meteo::setTemp(std::string ville, int temp)
{
    map<string, pair<int, float> >::iterator it = mapTempVent_.find(ville);
	if (it != mapTempVent_.end())
	{
		it->second.first = temp;
		this->notifierChangement();
	}
}
void Meteo::setVent(std::string ville, float vent)
{
    map<string, pair<int, float> >::iterator it = mapTempVent_.find(ville);
	if (it != mapTempVent_.end())
	{
		it->second.second = vent;
		this->notifierChangement();
	}
}

string Meteo::obtenirNomClasse() const
{
	return typeid(Meteo).name();
}
