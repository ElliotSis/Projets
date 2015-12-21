#ifndef VUEPRINCIPALEGTK_H
#define VUEPRINCIPALEGTK_H

#include "VuePrincipale.h"

#include <gtkmm/aspectframe.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/window.h>

/** \brief Classe dérivée de la classe VuePrincipale pour une utilisation dans une fenêtre.
 */
class VuePrincipaleGTK : public VuePrincipale, public Gtk::Window
{
    private:
        Gtk::AspectFrame menuPrincipalFrame; //!< La frame contenant le menu de choix du jeu.
        Gtk::AspectFrame menuJeuFrame; //!< La frame contenant le menu de choix des joueurs.
        Gtk::ButtonBox menuPrincipal; //!< La boite à bouttons pour le menu de choix du jeu.
        Gtk::ButtonBox menuJeu; //!< La boite à bouttons pour le menu de choix des joueurs.
        Gtk::Button bouttonDames; //!< Le boutton du jeu de dames.
        Gtk::Button bouttonOthello; //!< Le boutton du jeu d'othello.
        Gtk::Button bouttonPuissance4; //!< Le boutton du jeu de puissance 4.
        Gtk::Button bouttonValider; //!< Le boutton pour valider le choix des joueurs.
        Gtk::ComboBoxText listeDeroulanteJ1; //!< Liste déroulante pour choisir le joueur 1.
        Gtk::ComboBoxText listeDeroulanteJ2; //!< Liste déroulante pour choisir le joueur 2.
        int choixJeu; //!< Le jeu choisi.
        int choixJ1; //!< Le joueur 1 choisi.
        int choixJ2; //!< Le joueur 2 choisi.

    public:
         /** \brief Constructeur de VuePrincipaleGTK.
         * \param pControlleur la valeur à affecter à la variable controlleur.
         */
        VuePrincipaleGTK(Controlleur* pControlleur);

        void afficherMenuPrincipal(){}

         /** \brief Gère l'action de choix d'un élément d'une liste déroulante.
         */
        void listeActivee(int joueur);

        /** \brief Gère l'action de click sur un boutton de jeu.
         * \param pChoixJeu Le boutton clické.
         */
        void bouttonJeuPresse(int pChoixJeu);

        /** \brief Gère l'action de click sur le boutton valider.
         */
        void bouttonValiderPresse();
};

#endif // VUEPRINCIPALEGTK_H
