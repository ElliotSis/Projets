#include "VueJeuConsoleDames.h"

#include "Case.h"
#include "Couleurs.h"
#include "Coup.h"
#include "PieceDames.h"
#include "PlateauDames.h"
#include "JeuDames.h"
#include "Joueur.h"

#include <iostream>

using namespace std;

VueJeuConsoleDames::VueJeuConsoleDames(Jeu* pJeu, Controlleur* pControlleur) : VueJeuConsole(pJeu, pControlleur){}

VueJeuConsoleDames::~VueJeuConsoleDames(){}

void VueJeuConsoleDames::afficherPiece(Piece* piece){
    if(piece == nullptr) cout << " ";
    else if(((PieceDames*)piece)->estUnPion()){
        if(piece->getJoueurPossedant()->getCouleurDeSesPieces() == BLANC) cout << "b";
        else cout << "n";
    }
    else{
        if(piece->getJoueurPossedant()->getCouleurDeSesPieces() == BLANC) cout << "B";
        else cout << "N";
    }
}

void VueJeuConsoleDames::afficherJoueurDevantJouer(){
    if(jeu->joueurAyantLeTrait()->estArtificiel()) cout << "L'IA réfléchit…" << endl;
    else if(jeu->joueurAyantLeTrait()->getCouleurDeSesPieces() == BLANC) cout << "Joueur blanc, à vous de jouer !" << endl;
    else cout << "Joueur noir, à vous de jouer !" << endl;
}

void VueJeuConsoleDames::afficherGagnant(){
    if(jeu->joueurGagnant()->getCouleurDeSesPieces() == BLANC)  cout << "Joueur blanc gagne la partie !" << endl;
    else cout << "Joueur noir gagne la partie !" << endl;
}
