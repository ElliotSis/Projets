#ifndef PIECE_H
#define PIECE_H

#include "Direction.h"

#include <list>

class Case;
class Coup;
class Joueur;

/** \brief Classe représentant une pièce du jeu.
 */
class Piece{
	protected:
		Joueur* joueurPossedant; //!< Le joueur possédant la pièce (peut être nullptr : pas de joueur possédant la pièce).
		Case* caseContenante; //!< La case sur laquelle la pièce est posée (peut être nullptr : pièce non posée).
		std::list<Coup*> coups; //!< Les coups que l'on peut éventuellement jouer avec la pièce.

	public:
	    /** \brief Constructeur de Piece.
         * \param pJoueurPossedant La valeur à affecter à la variable joueurPossedant (optionnel : par défaut, pas de joueur possédant la pièce).
         * \param pCaseContenante La valeur à affecter à la variable caseContenante (optionnel : par défaut, pas de case contenant la pièce).
         */
		Piece(Joueur* pJoueurPossedant = nullptr, Case* pCaseContenante = nullptr);

        /** \brief Destructeur par défaut
         */
        virtual ~Piece();

		/** \brief Accède à la variable joueurPossedant.
         * \return La valeur de la variable joueurPossedant.
         */
		Joueur* getJoueurPossedant() const;

		/** \brief Accède à la variable caseContenante.
         * \return La valeur de la variable caseContenante.
         */
		Case* getCaseContenante() const;

        /** \brief Accède à la variable coups.
         * \return La valeur de la variable coups.
         */
        const std::list<Coup*>& getCoups() const;

        /** \brief Modifie la variable joueurPossedant.
         * \param pJoueurPossedant La nouvelle valeur à affecter à la variable joueurPossedant.
         */
        void setJoueurPossedant(Joueur* pJoueurPossedant);

		/** \brief Modifie la variable caseContenante.
         * \param pCaseContenante La nouvelle valeur à affecter à la variable caseContenante.
         */
		void setCaseContenante(Case* pCaseContenante);

        /** \brief Supprime tous les coups de la pièce.
         */
		void viderCoups();

        /** \brief Indique si la pièce est appartient à un joueur.
         * \return Un booléen valant true si la pièce appartient à un joueur, false sinon.
         */
		bool appartientAUnJoueur() const;

        /** \brief Indique si la pièce est posée sur une case.
         * \return Un booléen valant true si la pièce est posée sur une case, false sinon.
         */
		bool estPoseeSurUneCase() const;

		/** \brief Pose la pièce sur une case.
		 * \param caseArrivee La case sur laquelle la pièce va être posée.
         */
		virtual void poserSur(Case* caseArrivee);

        /** \brief Fait disparaitre la pièce du plateau et du joueur.
         */
        void disparaitre();

        /** \brief Fait réapparaitre la pièce sur le plateau et pour le joueur.
         */
        void reapparaitre();

        /** \brief Met à jour les coups.
		 *
		 * Les anciens coups de la pièce sont supprimés pour laisser la place aux nouveaux qui sont créés.
         */
		void mettreAJourLesCoups();

		/** \brief Créé les coups.
		 *
		 * Il s'agit d'une méthode purement abstraite se chargeant de créer les coups de la pièce.
         */
		virtual void creerLesCoups() = 0;
};

#endif // PIECE_H
