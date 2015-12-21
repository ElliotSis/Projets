#ifndef PIECEOTHELLO_H
#define PIECEOTHELLO_H

#include "Piece.h"

#include <set>

/** \brief Classe représentant une pièce du jeu d'othello.
 */
class PieceOthello : public Piece
{
    private:
        static std::set<Case*> couronne; //!< Les cases libres à vérifier lors de la création des coups.

    public:
        /** \brief Constructeur de PieceOthello.
         * \param pJoueurPossedant La valeur à affecter à la variable joueurPossedant (optionnel : par défaut, pas de joueur possédant la pièce).
         * \param pCaseContenante La valeur à affecter à la variable caseContenante (optionnel : par défaut, pas de case contenant la pièce).
         */
		PieceOthello(Joueur* pJoueurPossedant = nullptr, Case* pCaseContenante = nullptr);

        void creerLesCoups();

        /** \brief Met à jour la couronne.
         * \param caseAjoutee la case sur laquelle un pion a été posé.
         */
        static void mettreAJourLaCouronne(Case* caseAjoutee);

        /** \brief Annule la mise à jour la couronne.
         * \param caseAjoutee la case sur laquelle un pion a été enlevé.
         */
        static void annulerLaMiseAJourDeLaCouronne(Case* caseAjoutee);

        /** \brief Retourne le pion.
         */
        void retourner();
};

#endif // PIECEOTHELLO_H
