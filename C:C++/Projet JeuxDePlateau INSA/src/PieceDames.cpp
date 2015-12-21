#include "PieceDames.h"

#include "Case.h"
#include "CoupDames.h"
#include "DameDames.h"
#include "Joueur.h"
#include "PionDames.h"
#include "Plateau.h"

#include <iostream>

using namespace std;

Direction diagonales[4] = {Direction(1,1), Direction(1,-1), Direction(-1,1), Direction(-1,-1)};

PieceDames::PieceDames(Joueur* pJoueurPossedant, Case* pCaseContenante) : Piece(pJoueurPossedant, pCaseContenante){
    etat = new PionDames(this);
}

PieceDames::~PieceDames(){
    delete etat;
}

void PieceDames::remplirCoups(CoupDames* coupTraite, Direction& directionChoisie){
    bool aucunePrise = true;
    Case* caseInitiale = caseContenante;
    CoupDames* coup = (CoupDames*)(coupTraite->copie());

    for(int i = 0; i < 4; i++){
        Direction direction = diagonales[i];
        Direction directionContraire = -direction;
        PieceDames* piecePrise;
        if(directionContraire == directionChoisie) continue;
        int j = 0;
        for(Case* caseApresPrise : etat->casesApresPrise(direction)){
            if(j == 0) piecePrise = (PieceDames*)(caseApresPrise->caseAdjacente(directionContraire)->getPiecePosee());
            if(aucunePrise) aucunePrise = false;
            else coupTraite = (CoupDames*)(coup->copie());
            coupTraite->ajouterPieceASupprimer(piecePrise);
            piecePrise->disparaitre();
            poserSur(caseApresPrise);
            int l = etat->casesApresPrise(direction).size();
            remplirCoups(coupTraite, direction);
            poserSur(caseInitiale);
            piecePrise->reapparaitre();
            j++;
            if(l > 0) break;
        }
    }

    delete coup;

    if(aucunePrise){
        coupTraite->setCaseArrivee(caseContenante);
        coups.push_back(coupTraite);
    }
}

void PieceDames::creerLesCoups(){
    bool aucunePrise = true;
    Case* caseInitiale = caseContenante;

    for(int i = 0; i < 4; i++){
        Direction direction = diagonales[i];
        Direction directionContraire = -direction;
        PieceDames* piecePrise;
        for(Case* caseApresPrise : etat->casesApresPrise(direction)){
            if(aucunePrise){
                aucunePrise = false;
                piecePrise = (PieceDames*)(caseApresPrise->caseAdjacente(directionContraire)->getPiecePosee());
            }
            CoupDames* suivant = new CoupDames(this);
            suivant->ajouterPieceASupprimer(piecePrise);
            piecePrise->disparaitre();
            poserSur(caseApresPrise);
            remplirCoups(suivant, direction);
            poserSur(caseInitiale);
            piecePrise->reapparaitre();
        }
    }

    if(aucunePrise){
        for(Direction direction : etat->directionsDeDepart()){
            for(Case* caseDeplacement : etat->casesDeplacement(direction)){
                coups.push_back(new CoupDames(this,caseDeplacement));
            }
        }
    }
}

void PieceDames::promouvoir(){
    delete etat;
    etat = new DameDames(this);
}

void PieceDames::retrograder(){
    delete etat;
    etat = new PionDames(this);
}

bool PieceDames::estUnPion(){
    return etat->estUnPion();
}

bool PieceDames::estUneDame(){
    return etat->estUneDame();
}
