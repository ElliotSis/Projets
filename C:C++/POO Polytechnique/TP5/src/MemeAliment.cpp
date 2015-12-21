#include "MemeAliment.h"

using namespace std;

MemeAliment::MemeAliment(const Aliment* aliment) : aliment_(aliment) {}

string MemeAliment::getNomAliment() const {
	return aliment_->getNomAliment();
}

bool MemeAliment::operator() (const Aliment* aliment) const {
	return (*aliment == *aliment_);
}