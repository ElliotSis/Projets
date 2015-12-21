#include "PieceOthello.h"

#include "Case.h"
#include "CoupOthello.h"
#include "Direction.h"
#include "Joueur.h"
#include "Plateau.h"

#include <vector>

using namespace std;

Direction directions[8] = {Direction(1,0), Direction(1,-1), Direction(0,-1), Direction(-1,-1), Direction(-1,0), Direction(-1,1), Direction(0,1), Direction(1, 1)};

set<Case*> PieceOthello::couronne;

PieceOthello::PieceOthello(Joueur* pJoueurPossedant, Case* pCaseContenante) : Piece(pJoueurPossedant, pCaseContenante){
    if(pCaseContenante != nullptr) mettreAJourLaCouronne(pCaseContenante);
}

void PieceOthello::mettreAJourLaCouronne(Case* caseAjoutee){
    couronne.erase(caseAjoutee);
    for(Direction direction : directions){
        Case* caseAdjacente = caseAjoutee->caseAdjacente(direction);
        if(caseAdjacente != nullptr && caseAdjacente->estLibre()) couronne.insert(caseAdjacente);
    }
}

void PieceOthello::annulerLaMiseAJourDeLaCouronne(Case* caseAjoutee){
    couronne.insert(caseAjoutee);
    for(Direction direction : directions){
        Case* caseAdjacente = caseAjoutee->caseAdjacente(direction);
        if(caseAdjacente != nullptr && caseAdjacente->estLibre()){
            bool enleverDeLaCouronne = true;
            for(Direction direction : directions){
                Case* caseAdjacenteAdjacente = caseAdjacente->caseAdjacente(direction);
                if(caseAdjacenteAdjacente != nullptr && caseAdjacenteAdjacente != caseAjoutee && !caseAdjacenteAdjacente->estLibre()){
                    enleverDeLaCouronne = false;
                }
            }
            if(enleverDeLaCouronne) couronne.erase(caseAdjacente);
        }
    }
}

void PieceOthello::creerLesCoups(){
    for(Case* caseCouronne : couronne){
        Case* caseAdjacente = nullptr;
        list<Direction> directionsAEtudier;

        for(Direction direction : directions){
            caseAdjacente = caseCouronne->caseAdjacente(direction);
            while(caseAdjacente != nullptr && !caseAdjacente->estLibre() && caseAdjacente->getPiecePosee()->getJoueurPossedant() != getJoueurPossedant()){
                caseAdjacente = caseAdjacente->caseAdjacente(direction);
            }
            if(caseAdjacente != nullptr && caseAdjacente != caseCouronne->caseAdjacente(direction) && !caseAdjacente->estLibre() && caseAdjacente->getPiecePosee()->getJoueurPossedant() == getJoueurPossedant()){
                directionsAEtudier.push_back(direction);
            }
        }

        if(!directionsAEtudier.empty()){
            CoupOthello* coup = new CoupOthello(this, caseCouronne);
            for(Direction direction : directionsAEtudier){
                caseAdjacente = caseCouronne->caseAdjacente(direction);
                while(caseAdjacente != nullptr && !caseAdjacente->estLibre() && caseAdjacente->getPiecePosee()->getJoueurPossedant() != getJoueurPossedant()){
                    coup->ajouterPieceARetourner((PieceOthello*)(caseAdjacente->getPiecePosee()));
                    caseAdjacente = caseAdjacente->caseAdjacente(direction);
                }
            }
            coups.push_back(coup);
        }
    }
}

void PieceOthello::retourner(){
    joueurPossedant->adversaire()->gagnerPiece(this);
}
