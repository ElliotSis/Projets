#include "DameDames.h"

#include "Case.h"
#include "Joueur.h"
#include "PieceDames.h"

using namespace std;

DameDames::DameDames(PieceDames* pPiece) : EtatPieceDames(pPiece){}

bool DameDames::estUnPion() const{
    return false;
}

bool DameDames::estUneDame() const{
    return true;
}

const vector<Direction> DameDames::directionsDeDepart() const{
    return vector<Direction>({Direction(1,-1), Direction(1,1), Direction(-1,-1), Direction(-1,1)});
}

const vector<Case*> DameDames::casesApresPrise(Direction& direction) const{
    vector<Case*> res;
    Case* suivante = piece->getCaseContenante()->caseAdjacente(direction);
    while(suivante != nullptr && suivante->estLibre()){
        suivante = suivante->caseAdjacente(direction);
    }
    if(suivante != nullptr && suivante->getPiecePosee()->getJoueurPossedant()->getCouleurDeSesPieces() != piece->getJoueurPossedant()->getCouleurDeSesPieces()){
        suivante = suivante->caseAdjacente(direction);
        while(suivante != nullptr && suivante->estLibre()){
            res.push_back(suivante);
            suivante = suivante->caseAdjacente(direction);
        }
    }
    return res;
}

const vector<Case*> DameDames::casesDeplacement(Direction& direction) const{
    vector<Case*> res;
    Case* suivante = piece->getCaseContenante()->caseAdjacente(direction);
    while(suivante != nullptr && suivante->estLibre()){
        res.push_back(suivante);
        suivante = suivante->caseAdjacente(direction);
    }
    return res;
}
