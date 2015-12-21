#ifndef HUMAIN_H
#define HUMAIN_H

#include "Joueur.h"

/** \brief Classe représentant un joueur humain.
 */
class Humain : public Joueur
{
    public:
        /** \brief Constructeur de Humain.
         * \param pCouleurDeSesPieces La valeur à affecter à la variable couleurDeSesPieces.
         * \param pJeu La valeur à affecter à la variable jeu.
         */
        Humain(int pCouleurDeSesPieces, Jeu* pJeu);

        bool estArtificiel() const;

        void jouer();
};

#endif // HUMAIN_H
