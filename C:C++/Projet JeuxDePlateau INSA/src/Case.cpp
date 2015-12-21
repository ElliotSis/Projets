#include "Case.h"

#include "Plateau.h"

Case::Case(int pLigne, int pColonne, Plateau* pPlateau, int pCouleur, Piece* pPiecePosee) :
    ligne(pLigne), colonne(pColonne), plateau(pPlateau), couleur(pCouleur), piecePosee(pPiecePosee){}

int Case::getLigne() const{
    return ligne;
}

int Case::getColonne() const{
    return colonne;
}

Plateau* Case::getPlateau() const{
    return plateau;
}

int Case::getCouleur() const{
    return couleur;
}

Piece* Case::getPiecePosee() const{
    return piecePosee;
}

void Case::setCouleur(int pCouleur){
    couleur = pCouleur;
}

void Case::setPiecePosee(Piece* pPiecePosee){
    piecePosee = pPiecePosee;
}

bool Case::estLibre() const{
    return (piecePosee == nullptr);
}

Case* Case::caseAdjacente(Direction& direction){
    if(plateau->estValide(ligne+direction.first, colonne+direction.second)) return (*plateau)[ligne+direction.first][colonne+direction.second];
    else return nullptr;
}
