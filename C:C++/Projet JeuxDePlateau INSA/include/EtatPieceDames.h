#ifndef ETATPIECEDAMES_H
#define ETATPIECEDAMES_H

#include "Direction.h"

#include <vector>

class Case;
class PieceDames;

/** \brief Classe représentant un état d'une pièce aux dames.
 */
class EtatPieceDames
{
    protected:
        PieceDames* piece; //!< La pièce ayant cet état au jeu de dames.
    public:
        /** \brief Constructeur de EtatPieceDames.
         * \param pPiece La valeur à affecter à la variable piece.
         */
        EtatPieceDames(PieceDames* pPiece);

        /** \brief Detructeur par défaut.
         */
        virtual ~EtatPieceDames();

        /** \brief Indique si l'état de la pièce est un pion.
         * \return Un booléen valant true si la pièce est un pion, false sinon.
         */
        virtual bool estUnPion() const = 0;

        /** \brief Indique si la pièce est une dame.
         * \return Un booléen valant true si la pièce est une dame, false sinon.
         */
        virtual bool estUneDame() const = 0;


        /** \brief Renvoie les directions que la pièce peut prendre au départ.
         * \return Un vecteur contenant les directions que la pièce peut prendre au départ.
         */
        virtual const std::vector<Direction> directionsDeDepart() const = 0;

        /** \brief Donne le vecteur des cases où l'on peut se poser après une prise dans une direction.
         * \param direction Direction dans laquelle on cherche les cases après la prise.
         * \return Un vecteur contenant des *pointeurs* sur les cases disponibles après une prise dans cette direction, ce vecteur est vide si il n'y a pas de prise dans cette direction.
         */
        const virtual std::vector<Case*> casesApresPrise(Direction& direction) const = 0;

        /** \brief Donne le vecteur des cases où l'on peut se poser pour un déplacement dans une direction.
         * \param direction Direction dans laquelle on souhaite déplacer la pièce.
         * \return Un vecteur contenant des *pointeurs* sur les cases disponibles si l'on se déplace dans cette direction, ce vecteur est vide si on ne peut pas se déplacer dans cette direction.
         */
        const virtual std::vector<Case*> casesDeplacement(Direction& direction) const = 0;
};

#endif // ETATPIECEDAMES_H
