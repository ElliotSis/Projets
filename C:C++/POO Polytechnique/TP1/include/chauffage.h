#ifndef CHAUFFAGE_H
#define CHAUFFAGE_H

/** \brief Classe représentant le Chauffage d'une Maison.
 * \author Elliot Sisteron
 * \date 16/09/2015
 */
class Chauffage {
	public:
		/** \brief Constructeur par défaut.
         */
		Chauffage();

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

	private:
		bool estAllume_; //!< État du chauffage.
};

#endif // CHAUFFAGE_H
