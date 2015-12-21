#include "Jeu.h"

#include "Coup.h"
#include "Joueur.h"
#include "Piece.h"
#include "Plateau.h"

using namespace std;

Jeu::Jeu(){
    nbToursJoues = 0;
}

Jeu::~Jeu(){
    for(Joueur* j : joueurs) delete j;
    for(Piece* p : piecesNonAttribuees) delete p;
    delete plateau;
}

Plateau* Jeu::getPlateau() const{
    return plateau;
}

const list<Coup*>& Jeu::getCoupsPossibles() const{
    return coupsPossibles;
}

int Jeu::getNbToursJoues() const{
    return nbToursJoues;
}

void Jeu::enleverPieceNonAttribuee(Piece* pieceAEnlever){
    piecesNonAttribuees.erase(pieceAEnlever);
}


void Jeu::ajouterPieceNonAttribuee(Piece* pieceAAjouter){
    piecesNonAttribuees.insert(pieceAAjouter);
}

Joueur* Jeu::joueurAyantLeTrait(){
    return joueurs[nbToursJoues%2];
}

Joueur* Jeu::joueurSuivant(){
    return joueurs[(nbToursJoues+1)%2];
}

void Jeu::mettreAJourLesCoupsPossibles(){
    coupsPossibles.clear();
    for(Piece* p : piecesAMettreAJour()){
        p->mettreAJourLesCoups();
    }
    for(Piece* p : piecesAMettreAJour()){
        for(Coup* c : p->getCoups()){
            if(c->estPossible()) coupsPossibles.push_back(c);
        }
    }
}

void Jeu::passerALEtatSuivant(Coup* coupAJouer){
    if(coupAJouer != nullptr) coupAJouer->jouer();
    nbToursJoues++;
    mettreAJourLesCoupsPossibles();
}

void Jeu::revenirALEtatPrecedent(Coup* coupJoue){
    if(coupJoue != nullptr) coupJoue->annuler();
    nbToursJoues--;
    for(Piece* p : piecesAMettreAJour()) p->viderCoups();
}

bool Jeu::estGagne(){
    return (joueurGagnant() != nullptr);
}
