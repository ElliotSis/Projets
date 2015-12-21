#include "Aliment.h"

using namespace std;

Aliment::Aliment(string nomAliment, TYPE_GUSTATIF saveur) : nomAliment_(nomAliment), saveur_(saveur) {}

string Aliment::getNomAliment() const {
	return nomAliment_;
}

TYPE_GUSTATIF Aliment::getSaveur() const {
	return saveur_;
}

void Aliment::setNomAliment(string nomAliment) {
	nomAliment_ = nomAliment;
}

void Aliment::setSaveur(TYPE_GUSTATIF saveur) {
	saveur_ = saveur;
}

bool operator==(const Aliment& a, const Aliment& b) {
	return (a.saveur_ == b.saveur_ && a.nomAliment_ == b.nomAliment_);
}

ostream& operator<<(ostream& out, const Aliment& a) {
	out << a.nomAliment_;
	return out;
}

ostream& operator<<(ostream& out, const Aliment* a) {
	out << *a;
	return out;
}
