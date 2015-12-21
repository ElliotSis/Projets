#include "CoupOthello.h"

#include "Joueur.h"
#include "PieceOthello.h"

#include "Case.h"
#include <iostream>

using namespace std;

CoupOthello::CoupOthello(Piece* pPieceADeplacer, Case* pCaseArrivee) : Coup(pPieceADeplacer, pCaseArrivee){}

void CoupOthello::ajouterPieceARetourner(PieceOthello* pieceARetourner){
    piecesARetourner.push_back(pieceARetourner);
}

bool CoupOthello::estPossible() const{
    return true;
}

void CoupOthello::jouer(){
    Joueur* joueur = pieceADeplacer->getJoueurPossedant();
    pieceADeplacer->setCaseContenante(nullptr);
    joueur->gagnerPiece(pieceADeplacer);
    pieceADeplacer->poserSur(caseArrivee);
    PieceOthello::mettreAJourLaCouronne(caseArrivee);
    for(PieceOthello* piece : piecesARetourner) piece->retourner();
}

void CoupOthello::annuler(){
    PieceOthello::annulerLaMiseAJourDeLaCouronne(caseArrivee);
    for(PieceOthello* piece : piecesARetourner) piece->retourner();
    pieceADeplacer->disparaitre();
}

Coup* CoupOthello::copie(){
    return new CoupOthello(*this);
}
