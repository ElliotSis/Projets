#include "Joueur.h"

#include "Jeu.h"
#include "Piece.h"

#include <set>

using namespace std;

Joueur::Joueur(int pCouleurDeSesPieces, Jeu* pJeu) : couleurDeSesPieces(pCouleurDeSesPieces), jeu(pJeu){}

Joueur::~Joueur(){
    for(Piece* p : pieces) delete p;
}

int Joueur::getCouleurDeSesPieces() const{
    return couleurDeSesPieces;
}

set<Piece*>& Joueur::getPieces(){
    return pieces;
}

void Joueur::setCoupAJouer(Coup* pCoupAJouer){
    coupAJouer = pCoupAJouer;
}

void Joueur::gagnerPiece(Piece* pieceGagnee){
    pieces.insert(pieceGagnee);
    if(pieceGagnee->appartientAUnJoueur() && pieceGagnee->getJoueurPossedant() != this){
        pieceGagnee->getJoueurPossedant()->getPieces().erase(pieceGagnee);
    }
    pieceGagnee->setJoueurPossedant(this);
    jeu->enleverPieceNonAttribuee(pieceGagnee);
}

void Joueur::perdrePiece(Piece* piecePerdue){
    if(piecePerdue->getJoueurPossedant() == this){
        pieces.erase(piecePerdue);
        piecePerdue->setJoueurPossedant(nullptr);
        jeu->ajouterPieceNonAttribuee(piecePerdue);
    }
}

Joueur* Joueur::adversaire() const{
    return (jeu->joueurAyantLeTrait() == this)?(jeu->joueurSuivant()):(jeu->joueurAyantLeTrait());
}
