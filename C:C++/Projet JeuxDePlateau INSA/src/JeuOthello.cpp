#include "JeuOthello.h"

#include "ArtificielOthello.h"
#include "Couleurs.h"
#include "Coup.h"
#include "Humain.h"
#include "PieceOthello.h"
#include "PlateauOthello.h"

#include <iostream>

using namespace std;

JeuOthello::JeuOthello(int IA1, int IA2) : Jeu(){
    Joueur* j1, *j2;
    plateau = new PlateauOthello();

    if(IA1 == 0) j1 = new Humain(BLANC, this);
    else j1 = new ArtificielOthello(BLANC, this, IA1);

    if(IA2 == 0) j2 = new Humain(NOIR, this);
    else j2 = new ArtificielOthello(NOIR, this, IA2);

    joueurs[0] = j1;
    joueurs[1] = j2;

    for(int i = 3; i < 5; i++){
        for(int j = 3; j < 5; j++){
            if(i == j) new PieceOthello(j1, (*plateau)[i][j]);
            else new PieceOthello(j2, (*plateau)[i][j]);
        }
    }

    for(int i = 0; i < 60; i++){
        ajouterPieceNonAttribuee(new PieceOthello());
    }

    mettreAJourLesCoupsPossibles();
}

const set<Piece*>& JeuOthello::piecesAMettreAJour(){
    piecesTmp.clear();
    if(piecesNonAttribuees.size() > 0){
        Piece* p = *(piecesNonAttribuees.begin());
        p->setJoueurPossedant(joueurAyantLeTrait());
        piecesTmp.insert(p);
    }
    return piecesTmp;
}

Piece* JeuOthello::pieceDeplaceeParDefaut(){
    if(piecesNonAttribuees.size() > 0) return *(piecesNonAttribuees.begin());
    else return nullptr;
}


bool JeuOthello::estNul(){
    return (piecesNonAttribuees.size() == 0  && joueurAyantLeTrait()->getPieces().size() == joueurSuivant()->getPieces().size());
}

Joueur* JeuOthello::joueurGagnant(){
    if(joueurAyantLeTrait()->getPieces().size() == 0 || coupsPossibles.size() == 0) return joueurSuivant();
    else if (piecesNonAttribuees.size() == 0  && joueurAyantLeTrait()->getPieces().size() > joueurSuivant()->getPieces().size()) return joueurAyantLeTrait();
    else if (piecesNonAttribuees.size() == 0  && joueurAyantLeTrait()->getPieces().size() < joueurSuivant()->getPieces().size()) return joueurSuivant();
    else return nullptr;
}
