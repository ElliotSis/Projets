#ifndef JEU_H
#define JEU_H

#include <list>
#include <set>
#include <unordered_set>
#include <vector>

class Coup;
class Joueur;
class Piece;
class Plateau;

/** \brief Classe représentant un état de jeu de plateau.
 */
class Jeu{
	protected:
		Plateau* plateau; //!< Le plateau du jeu.
		Joueur* joueurs[2]; //!< Les joueurs du jeu.
		std::list<Coup*> coupsPossibles; //!< Les coups possibles pour passer à l'état de jeu suivant.
		std::unordered_set<Piece*> piecesNonAttribuees; //!< Pieces n'appartenant à aucun joueur.
		int nbToursJoues; //!< Le nombre de tours joués depuis le début du jeu.

	public:
	    /** \brief Constructeur par défaut.
         */
		Jeu();

		/** \brief Destructeur par défaut.
         */
		virtual ~Jeu();

        /** \brief Accède à la variable plateau.
		 * \return La valeur de la variable plateau.
         */
		Plateau* getPlateau() const;

		/** \brief Accède à la variable coupsPossibles.
		 * \return La valeur de la variable coupsPossibles.
         */
        const std::list<Coup*>& getCoupsPossibles() const;

		/** \brief Accède à la variable nbToursJoues.
		 * \return La valeur de la variable nbToursJoues.
         */
		int getNbToursJoues() const;

		/** \brief Ajoute une pièce aux pièces non attribuées.
		 * \param pieceAAjouter La pièce à ajouter à l'ensemble piecesNonAttribuees.
         */
        void ajouterPieceNonAttribuee(Piece* pieceAAjouter);

        /** \brief Enlève une pièce aux pièces non attribuées.
		 * \param pieceAEnlever La pièce à enlever à l'ensemble piecesNonAttribuees.
         */
        void enleverPieceNonAttribuee(Piece* pieceAEnlever);

		/** \brief Accède au joueur ayant le trait.
		 * \return Un *pointeur* sur le joueur ayant le trait.
         */
		Joueur* joueurAyantLeTrait();

        /** \brief Accède au joueur suivant.
         * \return Un *pointeur* sur le joueur suivant.
         */
		Joueur* joueurSuivant();

		/** \brief Met à jour la liste des coups possibles.
         */
		void mettreAJourLesCoupsPossibles();

        /** \brief Passe à l'état suivant du jeu.
		 * \param coupAJouer Un *pointeur* sur le coup à jouer pour passer à l'état suivant du jeu.
         */
        void passerALEtatSuivant(Coup* coupAJouer);

        /** \brief Revient à l'état précédent du jeu.
		 * \param coupJoue Un *pointeur* sur le coup joué à l'état précédent.
         */
        void revenirALEtatPrecedent(Coup* coupJoue);

        /** \brief Indique si le jeu est gagné par le joueur ayant le trait.
		 * \return Un booléen valant true si le jeu est gagné par le joueur ayant le trait, false sinon.
         */
		bool estGagne();

        /** \brief Donne la liste des pièces à mettre à jour pour passer à l'état suivant du jeu.
		 * \return La liste des pièces à mettre à jour pour passer à l'état suivant du jeu.
         */
		virtual const std::set<Piece*>& piecesAMettreAJour() = 0;

		/** \brief Donne la pièce déplacée par défaut.
		 * \return Un *pointeur* sur la pièce déplacée par défaut, nullptr quand il n'y a pas de pièce déplacée par défaut.
         */
		virtual Piece* pieceDeplaceeParDefaut() = 0;

		/** \brief Indique si l'état du jeu est un match nul.
		 * \return Un booléen valant true si le jeu est un match nul, false sinon.
         */
		virtual bool estNul() = 0;

		/** \brief Indique le joueur gagnant.
		 * \return Un *pointeur* sur le joueur gagnant, nullptr si il n'y a pas de gagnant.
         */
		virtual Joueur* joueurGagnant() = 0;
};

#endif // JEU_H
