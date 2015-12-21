#ifndef MAISON_H
#define MAISON_H

#include <string>
#include <vector>

// Forward declarations
class Cellulaire;
class Chauffage;
class Personne;

/** \brief Classe représentant une Maison.
 * \authors Benjamin De Leener
 * Adrien Logut
 * Elliot Sisteron
 * \date 16/09/2015
 */
class Maison {
	public:
    	/** \brief Constructeur de Maison.
    	 * \param adresse La valeur à affecter à la variable adresse_.
    	 * \param position La valeur à affecter à la variable position_.
         * \param nbChauffages Le nombre de chauffages de la maison.
         */
		Maison(std::string adresse = "inconnue", float position = 0.0, unsigned int nbChauffages = 1);

        /** \brief Constructeur par copie.
         * \param maison La maison à copier
         */
        Maison(const Maison& maison);

		/** \brief Destructeur par défaut.
         */
    	virtual ~Maison();

		/** \brief Accède à la variable adresse_.
         * \return La valeur de la variable adresse_.
         */
		std::string obtenirAdresse() const;

		/** \brief Modifie la variable adresse_.
         * \param adresse La nouvelle valeur à affecter à la variable adresse_.
         */
		void modifierAdresse(std::string adresse);

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

        /** \brief Trie et affiche la liste des occupants.
         */
        void afficherListeOccupants();

        /** \brief Affiche la liste des cellulaires.
         */
        void afficherListeCellulaires() const;

        /** \brief Évalue si au moins un chauffage est allumé.
         * \return *true* si un chauffage est allumé, *false* sinon.
         */
        bool estChauffageAllume() const;

        /** \brief Opérateur d'ajout de personne.
         * Ajoute un occupant.
         * \return La maison avec l'occupant ajouté.
         */
        Maison& operator+=(Personne* personne);

        /** \brief Opérateur d'ajout de cellulaire.
         * Ajoute un cellulaire.
         * \return La maison avec le cellulaire ajouté.
         */
        Maison& operator+=(Cellulaire* cellulaire);

        /** \brief Opérateur d'affectation.
         * \param maison La maison à copier.
         * \return La maison copiée.
         */
        Maison& operator=(const Maison& maison);
    
	private:
        /** \brief Allume les chauffages.
         */
        void allumerChauffages();

        /** \brief Éteint les chauffages.
         */
        void eteindreChauffages();

        /** Affiche des tirets.
         * \param nbTirets Le nombre de tirets à afficher.
         */
        static void afficherTirets(int nbTirets = 80);

        /** \brief Trie la liste des occupants dans l'ordre alphabétique des noms (et des prénoms si les noms sont identiques).
         * Algorithme utilisé : BubbleSort.
         */
        void trierOccupants();

		std::string adresse_; //!< Adresse de la maison.
   		
   		float position_; //!< Position de la maison.

		std::vector<Personne*> personnes_; //!< Liste des occupants de la maison.
    
		std::vector<Cellulaire*> cellulaires_; //!< Liste des cellulaires observés par la maison.
    
		std::vector<Chauffage*> chauffages_; //!< Chauffage de la maison.
};

#endif // MAISON_H