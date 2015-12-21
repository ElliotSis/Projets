#include "Controlleur.h"

#include "Case.h"
#include "Coup.h"
#include "JeuDames.h"
#include "JeuOthello.h"
#include "Joueur.h"
#include "Piece.h"
#include "VueJeu.h"
#include "VuePrincipale.h"

Controlleur::Controlleur() : jeu(nullptr), vueJeu(nullptr), vue(nullptr){}

Controlleur::~Controlleur(){
    delete jeu;
    delete vueJeu;
    delete vue;
}

VueJeu* Controlleur::getVueJeu() const{
    return vueJeu;
}

void Controlleur::traiterChoixMenuPrincipal(int choixJeu, int choixJ1, int choixJ2){
    switch(choixJeu){
        case 1 : jeu = new JeuDames(choixJ1, choixJ2);
                break;
        case 2 : jeu = new JeuOthello(choixJ1, choixJ2);
            break;
        default: break;
    }
    traiterChoixMenuPrincipalVue(choixJeu);
}

bool Controlleur::traiterCaseChoisie(Case* caseChoisie){
    if(jeu->joueurAyantLeTrait()->estArtificiel()) return false;
    else if(caseChoisie == nullptr) return false;
    else if(!caseChoisie->estLibre()){
        Piece* pieceChoisie = caseChoisie->getPiecePosee();
        for(Coup* c : jeu->getCoupsPossibles()){
            if(c->getPieceADeplacer() == pieceChoisie) pieceADeplacer = pieceChoisie;
        }
        return false;
    }
    else{
        if(pieceADeplacer == nullptr) return false;
        for(Coup* c : jeu->getCoupsPossibles()){
            if(c->getPieceADeplacer() == pieceADeplacer && c->getCaseArrivee() == caseChoisie){
                jeu->joueurAyantLeTrait()->setCoupAJouer(c);
                fairePasserAuTourSuivant();
                pieceADeplacer = jeu->pieceDeplaceeParDefaut();
                return true;
            }
        }
        return false;
    }
}

void Controlleur::fairePasserAuTourSuivant(){
    if(!jeu->estGagne() && !jeu->estNul()){
        jeu->joueurAyantLeTrait()->jouer();
        vueJeu->afficherJeu();
        if(jeu->estGagne()) vueJeu->afficherGagnant();
        else if (jeu->estNul()) vueJeu->afficherMatchNul();
        else if (jeu->joueurAyantLeTrait()->estArtificiel()) fairePasserAuTourSuivant();
    }
}

void Controlleur::jouer(){
    vueJeu->afficherJeu();
    if(jeu->joueurAyantLeTrait()->estArtificiel()) fairePasserAuTourSuivant();
    pieceADeplacer = jeu->pieceDeplaceeParDefaut();
}
