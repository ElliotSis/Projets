#include "Artificiel.h"

#include "Coup.h"
#include "Jeu.h"

#include <limits>
#include <list>

#include <iostream>

using namespace std;

Artificiel::Artificiel(int pCouleurDeSesPieces, Jeu* pJeu, int pProfondeur) :
    Joueur(pCouleurDeSesPieces, pJeu), profondeur(pProfondeur){}

Artificiel::~Artificiel(){}

double Artificiel::alphaBeta(double alpha, double beta){
    bool brancheMaximisante = (jeu->joueurAyantLeTrait() == this)?(true):(false);

    if(jeu->estGagne()){
        if(jeu->joueurGagnant() == this) return numeric_limits<double>::infinity();
        else return -numeric_limits<double>::infinity();
    }
    else if(jeu->estNul()) return 0;
    else if(profondeur == 0) return evaluation();
    else{
        list<Coup*> coupsPossibles;

        for(Coup* c : jeu->getCoupsPossibles()){
            coupsPossibles.push_back(c->copie());
        }

        profondeur--;
        for(Coup* c : coupsPossibles){
            jeu->passerALEtatSuivant(c);
            if(brancheMaximisante) alpha = max(alpha, alphaBeta(alpha, beta));
            else beta = min(beta, alphaBeta(alpha, beta));
            jeu->revenirALEtatPrecedent(c);
            if(alpha >= beta){
                break;
            }
        }
        profondeur++;

        for(Coup* c : coupsPossibles){
            delete c;
        }

        if(brancheMaximisante) return alpha;
        else return beta;
    }
}

Coup* Artificiel::meilleurCoupPossible(){
    double alpha = -numeric_limits<double>::infinity();
    double beta = numeric_limits<double>::infinity();
    double valeurDuJeuSuivant = alpha;
    list<Coup*> coupsPossibles;
    Coup* res = nullptr;

    if(jeu->getCoupsPossibles().size() == 1){
        return jeu->getCoupsPossibles().front()->copie();
    }

    for(Coup* c : jeu->getCoupsPossibles()){
        coupsPossibles.push_back(c->copie());
    }

    profondeur--;
    for(Coup* c : coupsPossibles){
        jeu->passerALEtatSuivant(c);
        valeurDuJeuSuivant = alphaBeta(alpha, beta);
        jeu->revenirALEtatPrecedent(c);
        if(valeurDuJeuSuivant > alpha){
            alpha = valeurDuJeuSuivant;
            res = c;
        }
    }
    profondeur++;

    if(res == nullptr) res = coupsPossibles.front();

    for(Coup* c : coupsPossibles){
        if(c != res) delete c;
    }

    return res;
}

void Artificiel::jouer(){
    coupAJouer = meilleurCoupPossible();
    jeu->passerALEtatSuivant(coupAJouer);
    delete coupAJouer;
}

bool Artificiel::estArtificiel() const{
    return true;
}
