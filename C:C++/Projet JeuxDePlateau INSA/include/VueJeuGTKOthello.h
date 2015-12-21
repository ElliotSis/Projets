#ifndef VUEJEUGTKOTHELLO_H
#define VUEJEUGTKOTHELLO_H

#include "VueJeuGTK.h"

/** \brief Classe dérivée de la classe VueJeuGTK pour jouer dans une fenêtre à l'othello.
 */
class VueJeuGTKOthello : public VueJeuGTK
{
    public:
        VueJeuGTKOthello(Jeu* pJeu, Controlleur* pControlleur);

        virtual ~VueJeuGTKOthello();

        void dessinerPiece(const Cairo::RefPtr<Cairo::Context> &cr, Piece* pieceADessiner);

        void afficherJoueurDevantJouer();

        void afficherGagnant();
};

#endif // VUEJEUGTKOTHELLO_H
