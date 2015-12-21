#include "Humain.h"

#include "Jeu.h"

Humain::Humain(int pCouleurDeSesPieces, Jeu* pJeu) : Joueur(pCouleurDeSesPieces, pJeu){}

bool Humain::estArtificiel() const{
    return false;
}

void Humain::jouer(){
    jeu->passerALEtatSuivant(coupAJouer);
}
