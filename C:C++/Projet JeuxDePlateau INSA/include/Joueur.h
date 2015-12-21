#ifndef JOUEUR_H
#define JOUEUR_H

#include <set>

class Coup;
class Jeu;
class Piece;

/** \brief Classe représentant un joueur du jeu.
 */
class Joueur{
	protected:
		int couleurDeSesPieces; //!< Couleur des pièces du joueur.
		std::set<Piece*> pieces; //!< Les pièces du joueur.
		Jeu* jeu; //!< Le jeu auquel le joueur joue.
		Coup* coupAJouer; //!< Le coup que le joueur va jouer.

	public:
		/** \brief Constructeur de Joueur.
         * \param pCouleurDeSesPieces La valeur à affecter à la variable couleurDeSesPieces.
         * \param pJeu La valeur à affecter à la variable jeu.
         */
        Joueur(int pCouleurDeSesPieces, Jeu* pJeu);

        /** \brief Destructeur par défaut.
         */
        virtual ~Joueur();

		/** \brief Accède à la variable couleurDeSesPieces.
         * \return La valeur de la variable couleurDeSesPieces.
         */
		int getCouleurDeSesPieces() const;

		/** \brief Accède à la variable pieces.
         * \return La valeur de la variable pieces.
         */
        std::set<Piece*>& getPieces();

		/** \brief Modifie la variable coupAJouer.
         * \param pCoupAJouer La nouvelle valeur à affecter à la variable coupAJouer.
         */
		void setCoupAJouer(Coup* pCoupAJouer);

		/** \brief Fait gagner une pièce au joueur.
		 * \param pieceGagnee La piece gagnée par le joueur.
         */
		void gagnerPiece(Piece* pieceGagnee);

		/** \brief Enlève une pièce au joueur.
		 * \param piecePerdue La piece enlevée au joueur.
         */
		void perdrePiece(Piece* piecePerdue);

		/** \brief Accède à la variable adversaire.
         * \return La valeur de la variable adversaire.
         */
		Joueur* adversaire() const;

		/** \brief Fait jouer le joueur.
         */
		virtual void jouer() = 0;

        /** \brief Indique si le joueur est artificiel.
         * \return Un booléen valant true si le joueur est artificiel, false sinon.
         */
		virtual bool estArtificiel() const = 0;
};


#endif // JOUEUR_H
