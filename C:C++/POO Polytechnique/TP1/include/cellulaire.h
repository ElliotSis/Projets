#ifndef CELLULAIRE_H
#define CELLULAIRE_H

#include <string>

#include "gps.h"

// Forward declaration
class Personne;

/** \brief Classe représentant un Cellulaire.
 * \author Adrien Logut 
 * \date 16/09/2015
 */
class Cellulaire {
	public:
		/** \brief Constructeur de Cellulaire.
         * \param numero La valeur à affecter à la variable numero_.
         */
		Cellulaire(const std::string numero = "inconnu", Personne* personne = nullptr);
		
		/** \brief Destructeur par défaut.
         */
		virtual ~Cellulaire();

		/** \brief Accède à la variable numero_.
         * \return La valeur de la variable numero_.
         */
		const std::string obtenirNumero() const;

		/** \brief Modifie la variable numero_.
         * \param numero La nouvelle valeur à affecter à la variable numero_.
         */
		void modifierNumero(const std::string numero);

		/** \brief Accède à la variable personne_.
         * \return La valeur de la variable personne_.
         */
		Personne* obtenirPersonne() const;

		/** \brief Modifie la variable personne_.
         * \param personne La nouvelle valeur à affecter à la variable personne_.
         */
		void modifierPersonne(Personne* personne);

		/** \brief Accède à la variable position_ de la variable gps_.
         * \return La valeur de la variable position_ de la variable gps_.
         */
		float obtenirPositionGps() const;

		/** \brief Modifie la variable position_ de la variable gps_.
         * \param position La nouvelle valeur à affecter à la variable position_ de la variable gps_.
         */
		void modifierPositionGps(float position);

		/** \brief Évalue si le cellulaire est proche d'une position.
		 * \param position La position à évaluer.
         * \return *true* si le cellulaire est proche de la position, *false* sinon.
         */
		bool estProche(float position);

	private:
		std::string numero_; //!< Numéro du cellulaire.

		Personne* personne_; //!< Personne propriétaire du cellulaire.
		
		GPS gps_; //!< GPS intégré au cellulaire
};

#endif // CELLULAIRE_H