#include "ArtificielOthello.h"

#include "Jeu.h"

ArtificielOthello::ArtificielOthello(int pCouleurDeSesPieces, Jeu* pJeu, int pProfondeur) :
    Artificiel(pCouleurDeSesPieces, pJeu, pProfondeur){}

double ArtificielOthello::evaluation(){
    double score = this->getPieces().size();
    double scoreAdversaire = adversaire()->getPieces().size();
    return score - scoreAdversaire;
}
