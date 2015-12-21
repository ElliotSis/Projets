#include "ArtificielDames.h"

#include "PieceDames.h"
#include "Jeu.h"

ArtificielDames::ArtificielDames(int pCouleurDeSesPieces, Jeu* pJeu, int pProfondeur) :
    Artificiel(pCouleurDeSesPieces, pJeu, pProfondeur){}

double ArtificielDames::evaluation(){
    double res = 0;
    for(Piece* p : this->getPieces()){
        if(((PieceDames*)p)->estUneDame()) res += 10;
        else res += 1;
    }
    for(Piece* p : adversaire()->getPieces()){
        if(((PieceDames*)p)->estUneDame()) res -= 10;
        else res -= 1;
    }
    return res;
}
