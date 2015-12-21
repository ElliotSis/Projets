#ifndef VUEPRINCIPALE_H
#define VUEPRINCIPALE_H

class Controlleur;

/** \brief Classe utilisée dans le cadre du patron de conception MVC.
 *
 * La vue est le "V" de MVC.
 * Elle sert à afficher et récupérer différentes informations utilisées dans le menu principal.
 */
class VuePrincipale
{
    protected:
        Controlleur* controlleur; //!< Le controlleur chargé de gérer la vue principale.

    public:
        /** \brief Constructeur de VuePrincipale.
         * \param pControlleur la valeur à affecter à la variable controlleur.
         */
        VuePrincipale(Controlleur* pControlleur);


        /** \brief Destructeur par défaut.
         */
        virtual ~VuePrincipale();

        /** \brief Affiche le menu principal.
         */
        virtual void afficherMenuPrincipal() = 0;
};

#endif // VUEPRINCIPALE_H
