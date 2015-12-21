#ifndef JEUDAMES_H
#define JEUDAMES_H

#include "Jeu.h"

/** \brief Classe représentant un état du jeu de dames.
 */
class JeuDames : public Jeu
{
    public:
        /** \brief Constructeur de JeuDames.
         * \param IA1 indique la difficulté du premier joueur artificiel (0 pour un joueur humain).
         * \param IA2 indique la difficulté du deuxième joueur artificiel (0 pour un joueur humain).
         */
        JeuDames(int IA1, int IA2);

        const std::set<Piece*>& piecesAMettreAJour();

        Piece* pieceDeplaceeParDefaut();

        bool estNul();

        Joueur* joueurGagnant();
};

#endif // JEUDAMES_H
