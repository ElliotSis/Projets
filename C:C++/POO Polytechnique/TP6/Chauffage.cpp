#include "Chauffage.h"
#include "Routeur.h"

using namespace std;

Chauffage::Chauffage(unsigned int id) : ObjetConnecte(id)
{
}

Chauffage::~Chauffage()
{
}

void Chauffage::recevoirMessage(Message* message)
{
	if ((message->getType() == ALLUMAGE_AUTOMATIQUE && automatique_ && !allume_))
	{
		cout << "Chauffage# " << id_ << ". Allume." << endl;
		allume_ = true;
	}
	else if (message->getType() == ALLUMER_CHAUFFAGE && !allume_)
	{
		cout << "Chauffage# " << id_ << ". Allume." << endl;
		allume_ = true;
	}
	else if (message->getType() == ETTEINDRE_CHAUFFAGE && allume_)
	{
		cout << "Chauffage# " << id_ << ". Etteint." << endl;
		allume_ = false;
	}
}

bool Chauffage::estAutomatique() const
{
	return automatique_;
}

void Chauffage::setAutomatique(bool value)
{
	automatique_ = value;
}