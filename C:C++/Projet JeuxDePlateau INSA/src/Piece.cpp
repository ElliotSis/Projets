#include "Piece.h"

#include "Case.h"
#include "Coup.h"
#include "Joueur.h"

using namespace std;

Piece::Piece(Joueur* pJoueurPossedant, Case* pCaseContenante) : joueurPossedant(pJoueurPossedant), caseContenante(pCaseContenante){
    if(appartientAUnJoueur()) joueurPossedant->gagnerPiece(this);
    if(estPoseeSurUneCase()) poserSur(caseContenante);
}

Piece::~Piece(){
    viderCoups();
}

Joueur* Piece::getJoueurPossedant() const{
    return joueurPossedant;
}

Case* Piece::getCaseContenante() const{
    return caseContenante;
}

const std::list<Coup*>& Piece::getCoups() const{
    return coups;
}

void Piece::setJoueurPossedant(Joueur* pJoueurPossedant){
    joueurPossedant = pJoueurPossedant;
}

void Piece::setCaseContenante(Case* pCaseContenante){
    caseContenante = pCaseContenante;
}

void Piece::viderCoups(){
    for(Coup* c : coups){
        delete c;
    }
    coups.clear();
}

bool Piece::appartientAUnJoueur() const{
    return (joueurPossedant != nullptr);
}

bool Piece::estPoseeSurUneCase() const{
    return (caseContenante != nullptr);
}

void Piece::poserSur(Case* caseArrivee){
    if(caseArrivee->estLibre()){
        if(estPoseeSurUneCase()) caseContenante->setPiecePosee(nullptr);
        caseArrivee->setPiecePosee(this);
        caseContenante = caseArrivee;
    }
}

void Piece::disparaitre(){
    if(appartientAUnJoueur()){
        Joueur* jTmp = joueurPossedant;
        joueurPossedant->perdrePiece(this);
        joueurPossedant = jTmp;
    }
    if(estPoseeSurUneCase()) caseContenante->setPiecePosee(nullptr);
}

void Piece::reapparaitre(){
    if(appartientAUnJoueur()) joueurPossedant->gagnerPiece(this);
    if(estPoseeSurUneCase()) caseContenante->setPiecePosee(this);
}

void Piece::mettreAJourLesCoups(){
    viderCoups();
    creerLesCoups();
}
