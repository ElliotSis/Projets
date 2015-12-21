#ifndef DAMEDAMES_H
#define DAMEDAMES_H

#include "EtatPieceDames.h"

/** \brief Classe représentant l'état dame d'une pièce du jeu de dames.
 */
class DameDames : public EtatPieceDames
{
    public:
        /** \brief Constructeur de DameDames.
         * \param pPiece La valeur à affecter à la variable piece.
         */
        DameDames(PieceDames* pPiece);

		bool estUnPion() const;

		bool estUneDame() const;

		const std::vector<Direction> directionsDeDepart() const;

        const std::vector<Case*> casesApresPrise(Direction& direction) const;

		const std::vector<Case*> casesDeplacement(Direction& direction) const;
};

#endif // DAMEDAMES_H
