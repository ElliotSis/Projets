#ifndef PLATEAUOTHELLO_H
#define PLATEAUOTHELLO_H

#include "Plateau.h"

/** \brief Classe représentant un plateau du jeu d'othello.
 */
class PlateauOthello : public Plateau
{
    public:
        /** \brief Constructeur par défaut.
         */
        PlateauOthello();

        void poserSur(Case* caseArrivee);
};

#endif // PLATEAUOTHELLO_H
