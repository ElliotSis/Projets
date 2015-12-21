#ifndef COUP_H
#define COUP_H

class Piece;
class Case;

/** \brief Classe représentant un coup du jeu.
 *
 * Un coup est une pièce que l'on déplace sur une case.
 */
class Coup{
	protected:
		Piece* pieceADeplacer; //!< La pièce à l'origine du déplacement.
		Case* caseArrivee; //!< La case d'arrivée.
	public:
	    /** \brief Constructeur de Coup.
         * \param pPieceADeplacer La valeur à affecter à la variable pieceADeplacer.
         * \param pCaseArrivee La valeur à affecter à la variable caseArrivee.
         */
		Coup(Piece* pPieceADeplacer, Case* pCaseArrivee);

        /** \brief Detructeur par défaut.
         */
		virtual ~Coup();

		/** \brief Accède à la variable pieceADeplacer.
         * \return La valeur de la variable pieceADeplacer.
         */
		Piece* getPieceADeplacer() const;

		/** \brief Accède à la variable caseArrivee.
         * \return La valeur de la variable caseArrivee.
         */
		Case* getCaseArrivee() const;

		/** \brief Modifie la variable caseArrivee.
         * \param pCaseArrivee La nouvelle valeur à affecter à la variable caseArrivee.
         */
		void setCaseArrivee(Case* pCaseArrivee);

		/** \brief Indique si il est possible de jouer le coup.
         * \return Un booléen valant true si le coup est jouable, false sinon.
         */
		virtual bool estPossible() const = 0;

		/** \brief Joue le coup.
         */
		virtual void jouer() = 0;

		/** \brief Annule le coup (après l'avoir joué).
         */
		virtual void annuler() = 0;

        /** \brief Renvoie une copie du coup.
         * \return  Un *pointeur* sur la copie du coup.
         */
		virtual Coup* copie() = 0;
};

#endif // COUP_H
