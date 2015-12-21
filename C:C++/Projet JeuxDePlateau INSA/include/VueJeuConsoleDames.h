#ifndef VUEJEUCONSOLEDAMES_H
#define VUEJEUCONSOLEDAMES_H

#include "VueJeuConsole.h"

/** \brief Classe dérivée de la classe VueJeuConsole pour jouer aux dames dans un terminal.
 */
class VueJeuConsoleDames : public VueJeuConsole
{
    public:
        /** \brief Constructeur de VueJeuConsoleDames.
         * \param pJeu La valeur à affecter à la variable jeu.
         * \param pControlleur La valeur à affecter à la variable controlleur.
         */
        VueJeuConsoleDames(Jeu* pJeu, Controlleur* pControlleur);

        virtual ~VueJeuConsoleDames();

        void afficherPiece(Piece* piece);

        void afficherJoueurDevantJouer();

        void afficherGagnant();
};

#endif // VUEJEUCONSOLEDAMES_H
