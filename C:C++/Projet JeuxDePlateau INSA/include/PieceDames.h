#ifndef PIECEDAMES_H
#define PIECEDAMES_H

#include "Piece.h"

#include <vector>

class CoupDames;
class EtatPieceDames;

/** \brief Classe représentant une pièce du jeu de dames.
 */
class PieceDames : public Piece
{
    private:
        EtatPieceDames* etat; //!< L'état de la pièce.

        /** \brief Méthode récursive utilisée par la méthode mettreAJourLesCoups.
         *
         * Cette méthode remplit les coups de la pièce récursivement en parcourant l'arbre des coups réalisable depuis la pièce du jeu de dames.
         * \param coupAModifier Le coup que l'on va modifier.
         * \param directionChoisie La direction dans laquelle la pièce s'est déplacée précedemment.
         */
        void remplirCoups(CoupDames* coupTraite, Direction& directionChoisie);

    public:
        /** \brief Constructeur de PieceDames.
         * \param pJoueurPossedant La valeur à affecter à la variable joueurPossedant (optionnel : par défaut, pas de joueur possédant la pièce).
         * \param pCaseContenante La valeur à affecter à la variable caseContenante (optionnel : par défaut, pas de case contenant la pièce).
         */
		PieceDames(Joueur* pJoueurPossedant = nullptr, Case* pCaseContenante = nullptr);

        /** \brief Destructeur par défaut.
         */
        ~PieceDames();

        void creerLesCoups();

        /** \brief Transforme la pièce en dame.
         */
        void promouvoir();

        /** \brief Transforme la pièce en pion.
         */
        void retrograder();

        /** \brief Indique si la pièce est un pion.
         * \return Un booléen valant true si la pièce est un pion, false sinon.
         */
        bool estUnPion();

        /** \brief Indique si la pièce est une dame.
         * \return Un booléen valant true si la pièce est une dame, false sinon.
         */
        bool estUneDame();
};

#endif // PIECEDAMES_H
