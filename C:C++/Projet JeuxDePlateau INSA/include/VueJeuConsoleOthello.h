#ifndef VUEJEUCONSOLEOTHELLO_H
#define VUEJEUCONSOLEOTHELLO_H

#include "VueJeuConsole.h"

/** \brief Classe dérivée de la classe VueJeuConsole pour jouer à l'othello dans un terminal.
 */
class VueJeuConsoleOthello : public VueJeuConsole
{
    public:
        /** \brief Constructeur de VueJeuConsoleOthello.
         * \param pJeu La valeur à affecter à la variable jeu.
         * \param pControlleur La valeur à affecter à la variable controlleur.
         */
        VueJeuConsoleOthello(Jeu* pJeu, Controlleur* pControlleur);

        virtual ~VueJeuConsoleOthello();

        void afficherPiece(Piece* piece);

        void afficherJoueurDevantJouer();

        void afficherGagnant();
};

#endif // VUEJEUCONSOLEOTHELLO_H
