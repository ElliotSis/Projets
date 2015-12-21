#ifndef ARTIFICIELDAMES_H
#define ARTIFICIELDAMES_H

#include "Artificiel.h"

/** \brief Classe représentant un joueur artificiel au jeu de dames.
 */
class ArtificielDames : public Artificiel
{
    public:
        /** \brief Constructeur de ArtificielDames.
         * \param pCouleurDeSesPieces La valeur à affecter à la variable couleurDeSesPieces.
         * \param pJeu La valeur à affecter à la variable jeu.
         * \param pProfondeur La valeur à affecter à la variable profondeur.
         */
        ArtificielDames(int pCouleurDeSesPieces, Jeu* pJeu, int pProfondeur);

    private:
        double evaluation();
};

#endif // ARTIFICIELDAMES_H
