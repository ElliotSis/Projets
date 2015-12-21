#ifndef MAISON_H
#define MAISON_H

#include <string>

#include "chauffage.h"

// Forward declarations
class Cellulaire;
class Personne;

const short NB_OCCUPANTS_MAX = 8; //!< Nombre d'occupants maximum.
const short NB_CELLULAIRES_MAX = 16; //!< Nombre de cellulaires connectés maximum.

/** \brief Classe représentant une Maison.
 * \author Benjamin De Leener
 * \date 16/09/2015
 */
class Maison {
	public:
    	/** \brief Constructeur de Maison.
    	 * \param adresse La valeur à affecter à la variable adresse_.
    	 * \param position La valeur à affecter à la variable position_.
         */
		Maison(const std::string adresse = "inconnue", float position = 0.0);

		/** \brief Destructeur par défaut.
         */
    	virtual ~Maison();

		/** \brief Accède à la variable adresse_.
         * \return La valeur de la variable adresse_.
         */
		const std::string obtenirAdresse() const;

		/** \brief Modifie la variable adresse_.
         * \param adresse La nouvelle valeur à affecter à la variable adresse_.
         */
		void modifierAdresse(const std::string adresse);

		/** \brief Accède à la variable position_.
         * \return La valeur de la variable position_.
         */
		float obtenirPosition() const;

		/** \brief Modifie la variable position_.
         * \param position La nouvelle valeur à affecter à la variable position_.
         */
		void modifierPosition(float position);
    
    	/** \brief Ajoute un occupant à la maison.
    	 * Si il est impossible d'ajouter un occupant, il ne sera pas ajouté.
         * \param personne La personne à ajouter à la liste des personnes occupant la maison (personnes_).
         */
        void ajouterOccupant(Personne* personne);

        /** \brief Ajoute un cellulaire observé à la maison.
    	 * Si il est impossible d'ajouter un cellulaire, il ne sera pas ajouté.
         * \param cellulaire Le cellulaire à ajouter à la liste des cellulaires observés par la maison (cellulaires_).
         */
    	void ajouterCellulaire(Cellulaire* cellulaire);

    	/** \brief Évalue si une personne est un occupant de la maison.
    	 * \param personne La personne à évaluer.
         * \return *true* si la personne occupe la maison, *false* sinon.
         */
		bool estOccupant(Personne* personne) const;

		/** \brief Évalue si la maison est vide.
         * \return *true* si la maison est vide *false* sinon.
         */
		bool estVide() const;

    	/** \brief Analyse en boucle les cellulaires observés pour savoir si ils sont proches.
    	 * Si un cellulaire est proche, la maison vérifie si la personne à qui il appartient occupe la maison.
    	 * Les cellulaires sont observés pour un temps déterminé.
    	 * Par défaut, la durée est de 60 secondes.
    	 * \param tempsObservation la durée (*en secondes*) d'observation des cellulaires.
    	 */
    	void observerCellulaires(float tempsObservation = 60.0f);
    
	private:
		std::string adresse_; //!< Adresse de la maison.
   		
   		float position_; //!< Position de la maison.

		Personne* personnes_[NB_OCCUPANTS_MAX]; //!< Liste des occupants de la maison.
    
		Cellulaire* cellulaires_[NB_CELLULAIRES_MAX]; //!< Liste des cellulaires observés par la maison.
    
		Chauffage chauffage_; //!< Chauffage de la maison.
};

#endif // MAISON_H