#ifndef CONTROLLEURCONSOLE_H
#define CONTROLLEURCONSOLE_H

#include "Controlleur.h"

/** \brief Un controlleur pour jouer dans un terminal.
 */
class ControlleurConsole : public Controlleur
{
    private:
        void traiterChoixMenuPrincipalVue(int choix);

    public:
        /** \brief Constructeur par défaut.
         */
        ControlleurConsole();

        void lancer();
};

#endif // CONTROLLEURCONSOLE_H
