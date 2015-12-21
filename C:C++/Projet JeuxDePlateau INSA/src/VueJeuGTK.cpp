#include "VueJeuGTK.h"

#include "Case.h"
#include "Controlleur.h"
#include "Couleurs.h"
#include "Coup.h"
#include "Jeu.h"
#include "Plateau.h"

#include <gtkmm/main.h>
#include <gtkmm/stock.h>
#include <string>

using namespace std;

VueJeuGTK::VueJeuGTK(Jeu* pJeu, Controlleur* pControlleur) : VueJeu(pJeu, pControlleur), Gtk::Box(Gtk::ORIENTATION_VERTICAL, 15),
grilleFrame("Nombre de tours joués : 0"){
    Plateau* plateau = jeu->getPlateau();
    int nbLignes = plateau->getNbLignes();
    int nbColonnes = plateau->getNbColonnes();

    Gtk::DrawingArea* tmp = new Gtk::DrawingArea[nbLignes*nbColonnes];
    cases = new Gtk::DrawingArea*[nbLignes];

    for(int i = 0; i < nbLignes; i++){
        cases[i] = tmp+i*nbColonnes;
        for(int j = 0; j < nbColonnes; j++){
            cases[i][j].signal_draw().connect(sigc::bind<Case*>(sigc::mem_fun(*this, &VueJeuGTK::dessinerCase), (*plateau)[i][j]));
            cases[i][j].set_hexpand(); cases[i][j].set_vexpand();
            cases[i][j].set_events(Gdk::BUTTON_PRESS_MASK);
            grille.attach(cases[i][j], j, i, 1, 1);
            cases[i][j].signal_button_press_event().connect(sigc::bind<Case*>(sigc::mem_fun(*this, &VueJeuGTK::bouttonPresse), (*plateau)[i][j]));
        }
    }

    grille.set_border_width(10);
    grilleFrame.add(grille);
    pack_start(grilleFrame);

    pack_start(infosJeu, Gtk::PACK_SHRINK);

    show_all();
}

VueJeuGTK::~VueJeuGTK(){
    delete[] cases[0];
    delete[] cases;
}

void VueJeuGTK::afficherJeu(){
    Plateau* plateau = jeu->getPlateau();
    int nbLignes = plateau->getNbLignes();
    int nbColonnes = plateau->getNbColonnes();

    grilleFrame.set_label("Nombre de tours joués : " + to_string(jeu->getNbToursJoues()));

    for(int i = 0; i < nbLignes; i++){
        for(int j = 0; j < nbColonnes; j++){
            cases[i][j].queue_draw();
        }
    }

    afficherJoueurDevantJouer();

    while(Gtk::Main::events_pending())
		Gtk::Main::iteration();
}

bool VueJeuGTK::dessinerCase(const Cairo::RefPtr<Cairo::Context> &cr, Case* caseADessiner){
    double r, g, b;
    int i = caseADessiner->getLigne(), j = caseADessiner->getColonne();
    const int largeur = cases[i][j].get_allocated_width();
    const int hauteur = cases[i][j].get_allocated_height();

    // fond
    cr->rectangle(0, 0, largeur, hauteur);
    intToRGB(caseADessiner->getCouleur(), r, g, b);
    cr->set_source_rgb(r, g, b);
    cr->fill_preserve();

    // contour
    cr->set_line_width(1.);
    intToRGB(NOIR, r, g, b);
    cr->set_source_rgba(r, g, b, 0.3);
    cr->stroke();

    if(!caseADessiner->estLibre()){
        dessinerPiece(cr, caseADessiner->getPiecePosee());
    }

    return true;
}

bool VueJeuGTK::bouttonPresse(GdkEventButton*, Case* caseSelectionnee){
    controlleur->traiterCaseChoisie(caseSelectionnee);
    return true;
}

void VueJeuGTK::afficherMatchNul(){
    infosJeu.set_text("Match nul !");
}
