#include "PionDames.h"

#include "Case.h"
#include "Couleurs.h"
#include "Joueur.h"
#include "PieceDames.h"

using namespace std;

PionDames::PionDames(PieceDames* pPiece) : EtatPieceDames(pPiece){}

bool PionDames::estUnPion() const{
    return true;
}

bool PionDames::estUneDame() const{
    return false;
}

const vector<Direction> PionDames::directionsDeDepart() const{
    if(piece->getJoueurPossedant()->getCouleurDeSesPieces() == BLANC) return vector<Direction>({Direction(-1,-1), Direction(-1,1)});
    else return vector<Direction>({Direction(1,-1), Direction(1,1)});
}

const vector<Case*> PionDames::casesApresPrise(Direction& direction) const{
    vector<Case*> res;
    Case* suivante = piece->getCaseContenante()->caseAdjacente(direction);
    if(suivante != nullptr && !(suivante->estLibre()) && suivante->getPiecePosee()->getJoueurPossedant()->getCouleurDeSesPieces() != piece->getJoueurPossedant()->getCouleurDeSesPieces()){
        suivante = suivante->caseAdjacente(direction);
        if(suivante != nullptr && suivante->estLibre()){
            res.push_back(suivante);
        }
    }
    return res;
}

const vector<Case*> PionDames::casesDeplacement(Direction& direction) const{
    vector<Case*> res;
    Case* suivante = piece->getCaseContenante()->caseAdjacente(direction);
    if(suivante != nullptr && suivante->estLibre()){
        res.push_back(suivante);
    }
    return res;
}
