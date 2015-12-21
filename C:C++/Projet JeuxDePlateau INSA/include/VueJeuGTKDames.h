#ifndef VUEJEUGTKDAMES_H
#define VUEJEUGTKDAMES_H

#include "VueJeuGTK.h"

/** \brief Classe dérivée de la classe VueJeuGTK pour jouer dans une fenêtre aux dames.
 */
class VueJeuGTKDames : public VueJeuGTK
{
    public:
        VueJeuGTKDames(Jeu* pJeu, Controlleur* pControlleur);

        virtual ~VueJeuGTKDames();

        void dessinerPiece(const Cairo::RefPtr<Cairo::Context> &cr, Piece* pieceADessiner);

        void afficherJoueurDevantJouer();

        void afficherGagnant();
};

#endif // VUEJEUGTKDAMES_H
