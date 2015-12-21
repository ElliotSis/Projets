#include "VueJeuConsole.h"

#include "Case.h"
#include "Controlleur.h"
#include "Jeu.h"
#include "Joueur.h"
#include "Piece.h"
#include "Plateau.h"

#include <iostream>

using namespace std;

VueJeuConsole::VueJeuConsole(Jeu* pJeu, Controlleur* pControlleur) : VueJeu(pJeu, pControlleur){}

VueJeuConsole::~VueJeuConsole(){}

void VueJeuConsole::afficherJeu(){
    Plateau* plateau = jeu->getPlateau();
    int nbLignes = plateau->getNbLignes();
    int nbColonnes = plateau->getNbColonnes();

    cout << endl;
    cout << "Nombre de tours joués : " << jeu->getNbToursJoues() << endl;
    cout << endl;

    cout << "  ";
    for(int j = 0; j < nbColonnes; j++){
        cout << "  " << j << " ";
    }
    cout << endl;

    for(int i = 0; i < nbLignes; i++){
        cout << "   ";
        for(int j = 0; j < nbColonnes; j++){
            cout << "----";
        }
        cout << endl;
        cout << i << " |";
        for(int j = 0; j < nbColonnes; j++){
            cout << " ";
            afficherPiece((*plateau)[i][j]->getPiecePosee());
            cout << " |";
        }
        cout << endl;
    }
    cout << "   ";
    for(int j = 0; j < nbColonnes; j++){
        cout << "----";
    }
    cout << endl;

    cout << endl;

    afficherJoueurDevantJouer();

    if(!jeu->joueurAyantLeTrait()->estArtificiel()) lireCase();
}

void VueJeuConsole::afficherMatchNul(){
    cout << "Match nul !" << endl;
}

void VueJeuConsole::lireCase() const{
    Plateau* plateau = jeu->getPlateau();
    int ligne;
    int colonne;
    Case* caseChoisie;

    do{
        cout << "Case choisie (ligne,colonne) : ";
        cin.ignore();
        cin >> ligne;
        cin.ignore();
        cin >> colonne;
        cin.ignore();
        cin.ignore();
        caseChoisie = (*plateau)[ligne][colonne];
    }while(!controlleur->traiterCaseChoisie(caseChoisie));
}
