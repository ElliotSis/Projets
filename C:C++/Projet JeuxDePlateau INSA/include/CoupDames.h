#ifndef COUPDAMES_H
#define COUPDAMES_H

#include "Coup.h"

#include <list>

class PieceDames;

/** \brief Classe représentant un coup du jeu de dames.
 */
class CoupDames : public Coup
{
    private:
        static int tailleRafleMaximale; //!< La taille de la rafle maximale.
        std::list<PieceDames*> piecesASupprimer; //!< Les pièces à supprimer avant de poser la pièce.
        Case* caseInitiale; //!< La case de la pièce de départ (pour annulation du coup).
        bool transformation; //!< Booléen permettant de savoir si il y a eu une transformation de pion en dame (pour annulation du coup).
    public:
        /** \brief Constructeur de CoupDames.
         * \param pPieceADeplacer La valeur à affecter à la variable pieceADeplacer.
         * \param pCaseArrivee La valeur à affecter à la variable caseArrivee.
         */
		CoupDames(Piece* pPieceADeplacer, Case* pCaseArrivee = nullptr);

		/** \brief Ajoute une pièce de aux pièces à supprimer.
         * \param pieceASupprimer Un *pointeur* sur la pièce à supprimer que l'on ajoute au vecteur piècesASupprimer.
         */
		void ajouterPieceASupprimer(PieceDames* pieceASupprimer);

        bool estPossible() const;

		void jouer();

		void annuler();

		Coup* copie();
};

#endif // COUPDAMES_H
