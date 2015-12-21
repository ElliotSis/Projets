#ifndef CHAUFFAGE_H
#define CHAUFFAGE_H

/** \brief Classe représentant le Chauffage d'une Maison.
 * \author Elliot Sisteron
 * \date 16/09/2015
 */

 #include "message.h"
#include "objetConnecte.h"


class Chauffage : public ObjetConnecte{
	public:
		/** \brief Constructeur par paramètre
		* \param id L'identifiant de l'objet connecté
         */
		Chauffage(unsigned int id);

		/** \brief Destructeur par défaut.
         */
		virtual ~Chauffage();

		/** \brief Accède à la variable estAllume_.
         * \return La valeur de la variable estAllume_.
         */
		bool obtenirEstAllume() const;

		/** \brief Allume le chauffage.
		 * Ne change rien si le chauffage est déjà allumé.
         */
		void allume();
		
		/** \brief Éteint le chauffage.
		 * Ne change rien si le chauffage est déjà éteint.
         */
		void eteindre();

		/** \brief Accède à la variable automatique.
         * \return La valeur de la variable automatique_.
         */
		bool obtenirAutomatique() const;

		/** \brief Défini si le chauffage est auto ou non
         * \param automatique la valeur
         */
        void modifierAutomatique(bool automatique);

		/** \brief Opérateur d'incrémentation préfixe.
		 * Allume le chauffage.
		 * \return Le chauffage allumé.
		 */
		Chauffage& operator++();

		/** \brief Opérateur de décrémentation préfixe.
		 * Éteint le chauffage.
		 * \return Le chauffage éteint.
		 */
		Chauffage& operator--();

	    /** \brief Allume/eteint le chauffage en fonction du message
	      * \param message Le message à afficher
	      */
      	void recevoirMessage(Message& message);



	private:
		bool estAllume_; //!< État du chauffage.
		bool automatique_; //!< Si le chauffage est automatique ou non
};

#endif // CHAUFFAGE_H
