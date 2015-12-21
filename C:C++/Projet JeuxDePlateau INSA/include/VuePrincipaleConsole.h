#ifndef VUEPRINCIPALECONSOLE_H
#define VUEPRINCIPALECONSOLE_H

#include "VuePrincipale.h"

/** \brief Classe dérivée de la classe VuePrincipale pour une utilisation dans un terminal.
 */
class VuePrincipaleConsole : public VuePrincipale
{
    public:
         /** \brief Constructeur de VuePrincipaleConsole.
         * \param pControlleur la valeur à affecter à la variable controlleur.
         */
        VuePrincipaleConsole(Controlleur* pControlleur);

        void afficherMenuPrincipal();

        /** \brief Récupère le jeu que l'utilisateur choisi.
         */
        int lireChoixMenuPrincipal();

        /** \brief Récupère les joueurs que l'utilisateur choisi.
         */
        int lireChoixMenuJeu();
};

#endif // VUEPRINCIPALECONSOLE_H
