#include "JeuDames.h"

#include "ArtificielDames.h"
#include "Couleurs.h"
#include "Coup.h"
#include "Humain.h"
#include "PieceDames.h"
#include "PlateauDames.h"

#include <iostream>

using namespace std;

JeuDames::JeuDames(int IA1, int IA2) : Jeu(){
    Joueur* j1, *j2;
    plateau = new PlateauDames();

    if(IA1 == 0) j1 = new Humain(BLANC, this);
    else j1 = new ArtificielDames(BLANC, this, IA1);

    if(IA2 == 0) j2 = new Humain(NOIR, this);
    else j2 = new ArtificielDames(NOIR, this, IA2);

    joueurs[0] = j1;
    joueurs[1] = j2;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 10; j++){
            if((i%2 == 0 && j%2 != 0) || (i%2 != 0 && j%2 == 0)){
                new PieceDames(j2, (*plateau)[i][j]);
            }
        }
    }

    for(int i = 9; i > 5; i--){
        for(int j = 0; j < 10; j++){
            if((i%2 == 0 && j%2 != 0) || (i%2 != 0 && j%2 == 0)){
                new PieceDames(j1, (*plateau)[i][j]);
            }
        }
    }

    mettreAJourLesCoupsPossibles();
}

const set<Piece*>& JeuDames::piecesAMettreAJour(){
    return joueurAyantLeTrait()->getPieces();
}

Piece* JeuDames::pieceDeplaceeParDefaut(){
    return nullptr;
}

bool JeuDames::estNul(){
    return (nbToursJoues >= 200);
}

Joueur* JeuDames::joueurGagnant(){
    if(joueurAyantLeTrait()->getPieces().size() == 0 || coupsPossibles.size() == 0) return joueurSuivant();
    else return nullptr;
}
