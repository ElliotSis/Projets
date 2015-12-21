#ifndef GPS_H
#define GPS_H

#include <ctime>

const float PROXIMITE = 3.0f; //!< Notion de proximité pour le GPS.

/** \brief Classe représentant un système GPS. 
 * Elle permet de localiser une personne dans l'espace, grâce à un simulateur de position.
 * \author Benjamin De Leener
 * \date 16/09/2015
 */
class GPS {
    public:    
        /** \brief Constructeur de GPS.
         * \param position La valeur à affecter à la variable position_.
         */
        GPS(float position = 0.0);
    
        /** \brief Destructeur par défaut.
         */
        virtual ~GPS();
    
        /** \brief Évalue si le GPS est proche d'une position.
         * La notion de proximité est définie par une la variable constante PROXIMITE.
         * \param position La position à évaluer.
         * \return *true* si le GPS est proche de la position, *false* sinon.
         */
        bool estProche(float position);
    
        /** \brief Accède à la variable position_.
         * \return La valeur de la variable position_.
         */
        float obtenirPosition() const;

        void modifierPosition(float position);
    
    private:
        float position_; //!< Position du GPS.
    
        time_t temps_; //!< Notion de temps, qui permet au simulateur de position de fonctionner.

        /** \brief Permet de simuler le déplacement du GPS dans le temps et dans l'espace. 
         * Cette méthode est appelée par la fonction estProche(). 
         * La position est calculée en additionnant la position actuelle par la multiplication du temps avec une vitesse aléatoire entre 3 et 5.
         */
        void simulateurDePosition();
};

#endif // GPS_H
