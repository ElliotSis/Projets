#include "CoupDames.h"

#include "Case.h"
#include "Couleurs.h"
#include "Joueur.h"
#include "PieceDames.h"

using namespace std;

int CoupDames::tailleRafleMaximale = 0;

CoupDames::CoupDames(Piece* pPieceADeplacer, Case* pCaseArrivee) : Coup(pPieceADeplacer, pCaseArrivee){
    transformation = false;
}

void CoupDames::ajouterPieceASupprimer(PieceDames* pieceASupprimer){
    piecesASupprimer.push_back(pieceASupprimer);
    if((int)piecesASupprimer.size() > tailleRafleMaximale) tailleRafleMaximale = piecesASupprimer.size();
}

bool CoupDames::estPossible() const{
    return ((int)piecesASupprimer.size() >= tailleRafleMaximale);
}

void CoupDames::jouer(){
    tailleRafleMaximale = 0;
    caseInitiale = pieceADeplacer->getCaseContenante();

    for(PieceDames* p : piecesASupprimer){
        p->disparaitre();
    }

    pieceADeplacer->poserSur(caseArrivee);

    if(((PieceDames*)pieceADeplacer)->estUnPion()){
        if((pieceADeplacer->getJoueurPossedant()->getCouleurDeSesPieces() == BLANC && caseArrivee->getLigne() == 0) || (pieceADeplacer->getJoueurPossedant()->getCouleurDeSesPieces() == NOIR && caseArrivee->getLigne() == 9)){
            ((PieceDames*)pieceADeplacer)->promouvoir();
            transformation = true;
        }
    }
}

void CoupDames::annuler(){
    for(PieceDames* p : piecesASupprimer){
        p->reapparaitre();
    }

    pieceADeplacer->poserSur(caseInitiale);

    if(transformation){
        ((PieceDames*)pieceADeplacer)->retrograder();
    }
}

Coup* CoupDames::copie(){
    return new CoupDames(*this);
}
