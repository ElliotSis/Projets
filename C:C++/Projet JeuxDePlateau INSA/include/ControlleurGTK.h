#ifndef CONTROLLEURGTK_H
#define CONTROLLEURGTK_H

#include "Controlleur.h"

#include <gtkmm/application.h>

/** \brief Un controlleur pour jouer dans une fenêtre, en utilisant la librairie GTKmm.
 */
class ControlleurGTK : public Controlleur
{
    private:
        Glib::RefPtr<Gtk::Application> app; //!< Application GTK nécessaire pour lancer le programme en mode GTK.

        void traiterChoixMenuPrincipalVue(int choix);

    public:
        /** \brief Constructeur par défaut.
         */
        ControlleurGTK();

        void lancer();
};

#endif // CONTROLLEURGTK_H
