#ifndef VUEJEUGTK_H
#define VUEJEUGTK_H

#include "VueJeu.h"

#include <gtkmm/aspectframe.h>
#include <gtkmm/box.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>

class Case;

/** \brief Classe dérivée de la classe VueJeu pour jouer dans une fenêtre avec la librairie GTKmm.
 */
class VueJeuGTK : public VueJeu, public Gtk::Box
{
    protected:
        Gtk::AspectFrame grilleFrame; //!< La frame contenant la grille.
        Gtk::Grid grille; //!< La grille de jeu.
        Gtk::DrawingArea** cases; //!< Les cases à dessiner.
        Gtk::Label infosJeu; //!< Le label affichant des infos pour le jeu.

    public:
        /** \brief Constructeur de VueGTK.
         * \param pJeu La valeur à affecter à la variable jeu.
         * \param pControlleur La valeur à affecter à la variable controlleur.
         */
        VueJeuGTK(Jeu* pJeu, Controlleur* pControlleur);

        /** \brief Detructeur par défaut.
         */
        virtual ~VueJeuGTK();

        void afficherJeu();

        void afficherMatchNul();

        /** \brief Dessine une case.
         * \param cr Le contexte de dessin.
         * \param caseADessiner la case à dessiner.
         * \return Un booléen indiquant si tout s'est bien passé.
         */
        bool dessinerCase(const Cairo::RefPtr<Cairo::Context> &cr, Case* caseADessiner);

        /** \brief Gère l'action de click sur une case.
         */
        bool bouttonPresse(GdkEventButton*, Case* caseSelectionnee);

        /** \brief Dessine une pièce.
         * \param cr Le contexte de dessin.
         * \param pieceADessiner la pièce à dessiner.
         * \return Un booléen indiquant si tout s'est bien passé.
         */
        virtual void dessinerPiece(const Cairo::RefPtr<Cairo::Context> &cr, Piece* pieceADessiner) = 0;

        virtual void afficherJoueurDevantJouer() = 0;

        virtual void afficherGagnant() = 0;
};

#endif // VUEJEUGTK_H
