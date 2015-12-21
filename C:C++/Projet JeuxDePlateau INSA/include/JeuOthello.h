#ifndef JEUOTHELLO_H
#define JEUOTHELLO_H

#include "Jeu.h"

/** \brief Classe représentant un état du jeu d'othello.
 */
class JeuOthello : public Jeu
{
    private:
        std::set<Piece*> piecesTmp; //!< Variable utilisée pour la méthode piecesAMettreAJour.

    public:
        /** \brief Constructeur de JeuOthello.
         * \param IA1 indique la difficulté du premier joueur artificiel (0 pour un joueur humain).
         * \param IA2 indique la difficulté du deuxième joueur artificiel (0 pour un joueur humain).
         */
        JeuOthello(int IA1, int IA2);

        const std::set<Piece*>& piecesAMettreAJour();

        Piece* pieceDeplaceeParDefaut();

        bool estNul();

        Joueur* joueurGagnant();
};

#endif // JEUOTHELLO_H
