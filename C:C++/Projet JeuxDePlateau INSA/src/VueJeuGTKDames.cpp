#include "VueJeuGTKDames.h"

#include "Case.h"
#include "Couleurs.h"
#include "Jeu.h"
#include "Joueur.h"
#include "PieceDames.h"

using namespace std;

VueJeuGTKDames::VueJeuGTKDames(Jeu* pJeu, Controlleur* pControlleur) : VueJeuGTK(pJeu, pControlleur){}

VueJeuGTKDames::~VueJeuGTKDames(){}

void VueJeuGTKDames::dessinerPiece(const Cairo::RefPtr<Cairo::Context> &cr, Piece* pieceADessiner){
    double r, g, b;
    int i = pieceADessiner->getCaseContenante()->getLigne(), j = pieceADessiner->getCaseContenante()->getColonne();
    const int largeur = cases[i][j].get_allocated_width();
    const int hauteur = cases[i][j].get_allocated_height();
    int xc = largeur/2, yc = hauteur/2, minimum = min(largeur, hauteur);

    intToRGB(pieceADessiner->getJoueurPossedant()->getCouleurDeSesPieces(), r, g, b);
    cr->set_source_rgb(r, g, b);
    cr->arc(xc, yc, minimum/3.0, 0.0, 2.0 * M_PI);
    cr->fill_preserve();

    intToRGB(BEIGE_FONCE, r, g, b);
    cr->set_line_width(1.);
    cr->set_source_rgba(r, g, b, 0.6);
    cr->arc(xc, yc, minimum/3.1, 0.0, 2.0 * M_PI);
    cr->stroke();

    if(((PieceDames*)pieceADessiner)->estUneDame()){
        intToRGB(BEIGE_FONCE, r, g, b);
        cr->set_line_width(1.5);
        cr->set_source_rgba(r, g, b, 0.8);
        cr->arc(xc, yc, minimum/3.6, 0.0, 2.0 * M_PI);
        cr->stroke();
    }
}

void VueJeuGTKDames::afficherJoueurDevantJouer(){
    if(jeu->joueurAyantLeTrait()->estArtificiel()) infosJeu.set_text("L'IA réfléchit…");
    else if(jeu->joueurAyantLeTrait()->getCouleurDeSesPieces() == BLANC) infosJeu.set_text("Joueur blanc, à vous de jouer !");
    else infosJeu.set_text("Joueur noir, à vous de jouer !");
}

void VueJeuGTKDames::afficherGagnant(){
    if(jeu->joueurGagnant()->getCouleurDeSesPieces() == BLANC) infosJeu.set_text("Joueur blanc gagne la partie !");
    else infosJeu.set_text("Joueur noir gagne la partie !");
}
