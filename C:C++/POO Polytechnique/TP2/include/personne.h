#ifndef PERSONNE_H
#define PERSONNE_H

#include <iostream>
#include <string>

/** \brief Classe représentant une Personne.
 * \authors Adrien Logut
 * Elliot Sisteron
 * \date 16/09/2015
 */
class Personne {
    public:
        /** \brief Constructeur de Personne.
         * \param prenom La valeur à affecter à la variable prenom_.
         * \param nom La valeur à affecter à la variable nom_.
         * \param numeroCellulaire La valeur à affecter à la variable numeroCellulaire_.
         * \param age La valeur à affecter à la variable age_.
         * \param estALaMaison La valeur à affecter à la variable estALaMaison_.
         */
        Personne(std::string prenom = "inconnu", std::string nom = "inconnu", unsigned int age = 0, 
            std::string numeroCellulaire = "inconnu", bool estALaMaison = false);
        
        /** \brief Destructeur par défaut.
         */
        virtual ~Personne();

        /** \brief Accède à la variable prenom_.
         * \return La valeur de la variable prenom_.
         */
        std::string obtenirPrenom() const;
    
        /** \brief Modifie la variable prenom_.
         * \param prenom La nouvelle valeur à affecter à la variable prenom_.
         */
        void modifierPrenom(std::string prenom);
        
        /** \brief Accède à la variable nom_.
         * \return La valeur de la variable nom_.
         */
        std::string obtenirNom() const;
    
        /** \brief Modifie la variable nom_.
         * \param nom La nouvelle valeur à affecter à la variable nom_.
         */
        void modifierNom(std::string nom);
    
        /** \brief Accède à la variable numeroCellulaire_.
         * \return La valeur de la variable numeroCellulaire_.
         */
        std::string obtenirNumeroCelullaire() const;
    
        /** \brief Modifie la variable numeroCellulaire_.
         * \param numeroCellulaire La nouvelle valeur à affecter à la variable numeroCellulaire_.
         */
        void modifierNumeroCelullaire(std::string numeroCellulaire);
    
        /** \brief Accède à la variable age_.
         * \return La valeur de la variable age_.
         */
        unsigned int obtenirAge() const;
        
        /** \brief Modifie la variable age_.
         * \param age La nouvelle valeur à affecter à la variable age_.
         */
        void modifierAge(unsigned int age);
        
        /** \brief Accède à la variable estALaMaison_.
         * \return La valeur de la variable estALaMaison_.
         */
        bool obtenirEstALaMaison() const;
        
        /** \brief Modifie la variable estALaMaison_.
         * \param estALaMaison La nouvelle valeur à affecter à la variable estALaMaison_.
         */
        void modifierEstALaMaison(bool estALaMaison);

        /** \brief Opérateur d'égalité.
         * \param personne1 La première personne à comparer.
         * \param personne2 La deuxième personne à comparer.
         * \return *true* si les deux personnes sont les mêmes (prenom, nom et age identique), *false* sinon.
         */
        friend bool operator==(Personne const& personne1, Personne const& personne2);

        /** \brief Opérateur de comparaison inférieure stricte.
         * \param personne1 La première personne à comparer.
         * \param personne2 La deuxième personne à comparer.
         * \return *true* si le nom de la première personne est positionné en premier dans l'ordre alphabétique, *false* sinon (dans le cas où les nom sont identiques, on compare les prénoms).
         */
        friend bool operator<(Personne const& personne1, Personne const& personne2);

        /** \brief Opérateur de flux de sortie.
         * \param out Le flux de sortie.
         * \param personne La personne à afficher sur le flux de sortie.
         * \return Le flux de sortie.
         */
        friend std::ostream& operator<<(std::ostream& out, Personne const& personne);


    private:
        std::string prenom_; //!< Prénom de la personne.

        std::string nom_; //!< Nom de la personne.
    
        std::string numeroCellulaire_; //!< Numéro du cellulaire de la personne.

        unsigned int age_; //!< Âge de la personne.

        bool estALaMaison_; //!< Booléen indiquant si la personne est chez elle.

};

#endif // PERSONNE_H
