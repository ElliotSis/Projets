#ifndef VUEJEUCONSOLE_H
#define VUEJEUCONSOLE_H

#include "VueJeu.h"

#include <string>

/** \brief Classe dérivée de la classe VueJeu pour jouer dans un terminal.
 */
class VueJeuConsole : public VueJeu
{
    public:
        /** \brief Constructeur de VueConsole.
         * \param pJeu La valeur à affecter à la variable jeu.
         * \param pControlleur La valeur à affecter à la variable controlleur.
         */
        VueJeuConsole(Jeu* pJeu, Controlleur* pControlleur);

        /** \brief Detructeur par défaut.
         */
        virtual ~VueJeuConsole();

        void afficherJeu();

        void afficherMatchNul();

        /** \brief Récupère la case que l'utilisateur choisit.
         */
        void lireCase() const;

        /** \brief Affiche une pièce.
         * \param piece Un *pointeur* sur la pièce à afficher.
         */
        virtual void afficherPiece(Piece* piece) = 0;

        virtual void afficherJoueurDevantJouer() = 0;

        virtual void afficherGagnant() = 0;
};

#endif // VUEJEUCONSOLE_H
