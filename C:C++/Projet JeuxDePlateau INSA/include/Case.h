#ifndef CASE_H
#define CASE_H

#include "Direction.h"

class Plateau;
class Piece;

/** \brief Classe représentant une case du plateau du jeu.
 */
class Case{
	private:
		int ligne; //!< Ligne où est située la case.
		int colonne; //!< Colonne où est située la case.
		Plateau* plateau; //!< Plateau sur lequel se trouve la case.
		int couleur; //!< Couleur de la case.
		Piece* piecePosee; //!< Pièce posée sur la case (peut être nullptr : pas de pièce posée).

	public:
	    /** \brief Constructeur de Case.
         * \param pLigne La valeur à affecter à la variable ligne.
         * \param pColonne La valeur à affecter à la variable nbColonnes.
         * \param pPlateau La valeur à affecter à la variable plateau.
         * \param pCouleur La valeur à affecter à la variable couleur.
         * \param pPiecePosee La valeur à affecter à la variable piecePosee (optionnel : par défaut, pas de pièce posée sur la case).
         */
		Case(int pLigne, int pColonne, Plateau* pPlateau, int pCouleur, Piece* pPiecePosee = nullptr);

		/** \brief Accède à la variable ligne.
         * \return La valeur de la variable ligne.
         */
		int getLigne() const;

		/** \brief Accède à la variable colonne.
         * \return La valeur de la variable colonne.
         */
		int getColonne() const;

		/** \brief Accède à la variable plateau.
         * \return La valeur de la variable plateau.
         */
		Plateau* getPlateau() const;

		/** \brief Accède à la variable couleur.
         * \return La valeur de la variable couleur.
         */
		int getCouleur() const;

		/** \brief Accède à la variable piecePosee.
         * \return La valeur de la variable piecePosee.
         */
		Piece* getPiecePosee() const;

        /** \brief Modifie la variable couleur.
         * \param pCouleur La nouvelle valeur à affecter à la variable couleur.
         */
		void setCouleur(int pCouleur);

		/** \brief Modifie la variable piecePosee.
         * \param pPiecePosee La nouvelle valeur à affecter à la variable piecePosee.
         */
		void setPiecePosee(Piece* pPiecePosee);

		/** \brief Indique si la case est libre.
         * \return Un booléen valant true si la case est libre, false sinon.
         */
		bool estLibre() const;

		/** \brief Calcule la case adjacente dans une direction donnée.
		 * \param direction La direction dans laquelle on veut la case adjacente.
         * \return Un *pointeur* sur la case adjacente, nullptr si cette case n'existe pas.
         */
		Case* caseAdjacente(Direction& direction);
};

#endif // CASE_H
