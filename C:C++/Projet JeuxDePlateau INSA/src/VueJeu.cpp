#include "VueJeu.h"

#include "Controlleur.h"
#include "Jeu.h"

VueJeu::VueJeu(Jeu* pJeu, Controlleur* pControlleur) : jeu(pJeu), controlleur(pControlleur){}

VueJeu::~VueJeu(){}
