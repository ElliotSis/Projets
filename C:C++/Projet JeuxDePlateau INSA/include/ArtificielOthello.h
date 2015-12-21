#ifndef ARTIFICIELOTHELLO_H
#define ARTIFICIELOTHELLO_H

#include "Artificiel.h"

/** \brief Classe représentant un joueur artificiel au jeu d'othello.
 */
class ArtificielOthello : public Artificiel
{
    public:
        /** \brief Constructeur de ArtificielOthello.
         * \param pCouleurDeSesPieces La valeur à affecter à la variable couleurDeSesPieces.
         * \param pJeu La valeur à affecter à la variable jeu.
         * \param pProfondeur La valeur à affecter à la variable profondeur.
         */
        ArtificielOthello(int pCouleurDeSesPieces, Jeu* pJeu, int pProfondeur);

    private:
        double evaluation();
};

#endif // ARTIFICIELOTHELLO_H
