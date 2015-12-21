#include "Coup.h"

Coup::Coup(Piece* pPieceADeplacer, Case* pCaseArrivee) : pieceADeplacer(pPieceADeplacer), caseArrivee(pCaseArrivee){}

Coup::~Coup(){}

Piece* Coup::getPieceADeplacer() const{
    return pieceADeplacer;
}

Case* Coup::getCaseArrivee() const{
    return caseArrivee;
}

void Coup::setCaseArrivee(Case* pCaseArrivee){
    caseArrivee = pCaseArrivee;
}
