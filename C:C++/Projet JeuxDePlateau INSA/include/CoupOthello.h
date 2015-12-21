#ifndef COUPOTHELLO_H
#define COUPOTHELLO_H

#include "Coup.h"

#include <list>

class PieceOthello;

class CoupOthello : public Coup
{
    private:
        std::list<PieceOthello*> piecesARetourner; //!< Les pièces à retourner lorsque l'on pose la pièce.

    public:
        /** \brief Constructeur de CoupOthello.
         * \param pPieceADeplacer La valeur à affecter à la variable pieceADeplacer.
         * \param pCaseArrivee La valeur à affecter à la variable caseArrivee.
         */
		CoupOthello(Piece* pPieceADeplacer, Case* pCaseArrivee);

		/** \brief Ajoute une pièce aux pièces à retourner.
         * \param pieceARetourner Un *pointeur* sur la pièce à retourner que l'on ajoute au vecteur piecesARetourner.
         */
		void ajouterPieceARetourner(PieceOthello* pieceARetourner);

        bool estPossible() const;

		void jouer();

		void annuler();

		Coup* copie();
};

#endif // COUPOTHELLO_H
