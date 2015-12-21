#ifndef PIONDAMES_H
#define PIONDAMES_H

#include "EtatPieceDames.h"

/** \brief Classe représentant l'état pion d'une pièce du jeu de dames.
 */
class PionDames : public EtatPieceDames
{
    public:
        /** \brief Constructeur de PionDames.
         * \param pPiece La valeur à affecter à la variable piece.
         */
        PionDames(PieceDames* pPiece);

		bool estUnPion() const;

		bool estUneDame() const;

        const std::vector<Direction> directionsDeDepart() const;

        const std::vector<Case*> casesApresPrise(Direction& direction) const;

		const std::vector<Case*> casesDeplacement(Direction& direction) const;
};

#endif // PIONDAMES_H
