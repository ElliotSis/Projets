#include "VueJeuGTKOthello.h"

#include "Case.h"
#include "Couleurs.h"
#include "Jeu.h"
#include "Joueur.h"
#include "Piece.h"

using namespace std;

VueJeuGTKOthello::VueJeuGTKOthello(Jeu* pJeu, Controlleur* pControlleur) : VueJeuGTK(pJeu, pControlleur){}

VueJeuGTKOthello::~VueJeuGTKOthello(){}

void VueJeuGTKOthello::dessinerPiece(const Cairo::RefPtr<Cairo::Context> &cr, Piece* pieceADessiner){
    double r, g, b;
    int i = pieceADessiner->getCaseContenante()->getLigne(), j = pieceADessiner->getCaseContenante()->getColonne();
    const int largeur = cases[i][j].get_allocated_width();
    const int hauteur = cases[i][j].get_allocated_height();
    int xc = largeur/2, yc = hauteur/2, minimum = min(largeur, hauteur);
    int couleurFondPiece;

    if(pieceADessiner->getJoueurPossedant()->getCouleurDeSesPieces() == BLANC) couleurFondPiece = NOIR;
    else couleurFondPiece = BLANC;

    intToRGB(couleurFondPiece, r, g, b);
    cr->set_source_rgb(r, g, b);
    cr->arc(xc, yc, minimum/3.0, 0.0, 2.0 * M_PI);
    cr->fill();

    intToRGB(pieceADessiner->getJoueurPossedant()->getCouleurDeSesPieces(), r, g, b);
    cr->set_source_rgb(r, g, b);
    cr->arc(xc, yc-1, minimum/3.0, 0.0, 2.0 * M_PI);
    cr->fill_preserve();
}

void VueJeuGTKOthello::afficherJoueurDevantJouer(){
    if(jeu->joueurAyantLeTrait()->estArtificiel()) infosJeu.set_text("L'IA réfléchit…");
    else if(jeu->joueurAyantLeTrait()->getCouleurDeSesPieces() == BLANC) infosJeu.set_text("Joueur blanc, à vous de jouer !");
    else infosJeu.set_text("Joueur noir, à vous de jouer !");
}

void VueJeuGTKOthello::afficherGagnant(){
    if(jeu->joueurGagnant()->getCouleurDeSesPieces() == BLANC) infosJeu.set_text("Joueur blanc gagne la partie !");
    else infosJeu.set_text("Joueur noir gagne la partie !");
}
