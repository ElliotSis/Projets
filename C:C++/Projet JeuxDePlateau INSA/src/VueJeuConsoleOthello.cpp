#include "VueJeuConsoleOthello.h"

#include "Case.h"
#include "Couleurs.h"
#include "Coup.h"
#include "Piece.h"
#include "Plateau.h"
#include "Jeu.h"
#include "Joueur.h"

#include <iostream>

using namespace std;

VueJeuConsoleOthello::VueJeuConsoleOthello(Jeu* pJeu, Controlleur* pControlleur) : VueJeuConsole(pJeu, pControlleur){}

VueJeuConsoleOthello::~VueJeuConsoleOthello(){}

void VueJeuConsoleOthello::afficherPiece(Piece* piece){
    if(piece == nullptr) cout << " ";
    else{
        if(piece->getJoueurPossedant()->getCouleurDeSesPieces() == BLANC) cout << "b";
        else cout << "n";
    }
}

void VueJeuConsoleOthello::afficherJoueurDevantJouer(){
    if(jeu->joueurAyantLeTrait()->estArtificiel()) cout << "L'IA réfléchit…" << endl;
    else if(jeu->joueurAyantLeTrait()->getCouleurDeSesPieces() == BLANC) cout << "Joueur blanc, à vous de jouer !" << endl;
    else cout << "Joueur noir, à vous de jouer !" << endl;
}

void VueJeuConsoleOthello::afficherGagnant(){
    if(jeu->joueurGagnant()->getCouleurDeSesPieces() == BLANC)  cout << "Joueur blanc gagne la partie !" << endl;
    else cout << "Joueur noir gagne la partie !" << endl;
}
