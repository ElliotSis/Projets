#include "VuePrincipaleGTK.h"

#include "Controlleur.h"
#include "VueJeuGTK.h"

#include <string>

using namespace std;

VuePrincipaleGTK::VuePrincipaleGTK(Controlleur* pControlleur) :
VuePrincipale(pControlleur), menuPrincipalFrame("Sélectionnez le jeu"), menuJeuFrame("Sélectionnez les joueurs"),
menuPrincipal(Gtk::ORIENTATION_VERTICAL), menuJeu(Gtk::ORIENTATION_VERTICAL),
bouttonDames("Jeu de dames"), bouttonOthello("Jeu d'othello"), bouttonPuissance4("Jeu de Puissance 4"), bouttonValider("OK"){
    set_title("Jeux de plateau");
    set_border_width(10);
    set_size_request(550, 550);

    menuPrincipal.set_layout(Gtk::BUTTONBOX_SPREAD);
    menuJeu.set_layout(Gtk::BUTTONBOX_SPREAD);

    //rentrer les bouttons dans la boite
    menuPrincipal.add(bouttonDames);
    menuPrincipal.add(bouttonOthello);
    menuPrincipal.add(bouttonPuissance4);

    menuPrincipalFrame.add(menuPrincipal);

    //connecter les bouttons
    bouttonDames.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &VuePrincipaleGTK::bouttonJeuPresse), 1));
    bouttonOthello.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &VuePrincipaleGTK::bouttonJeuPresse), 2));

    bouttonValider.signal_clicked().connect(sigc::mem_fun(*this, &VuePrincipaleGTK::bouttonValiderPresse));

    //initialiser les listesderoulantes
    listeDeroulanteJ1.append("Humain");
    listeDeroulanteJ2.append("Humain");
    for(int i = 1; i < 10; i++){
        listeDeroulanteJ1.append("IA difficulté " + to_string(i));
        listeDeroulanteJ2.append("IA difficulté " + to_string(i));
    }
    //rentrer ça dans une boite
    menuJeu.add(listeDeroulanteJ1);
    menuJeu.add(listeDeroulanteJ2);
    menuJeu.add(bouttonValider);

    //connecter les listes
    listeDeroulanteJ1.signal_changed().connect(sigc::bind<int>(sigc::mem_fun(*this, &VuePrincipaleGTK::listeActivee), 1));
    listeDeroulanteJ2.signal_changed().connect(sigc::bind<int>(sigc::mem_fun(*this, &VuePrincipaleGTK::listeActivee), 2));

    //initialiser le titre des listes
    listeDeroulanteJ1.set_active_text("Humain");
    listeDeroulanteJ2.set_active_text("Humain");

    menuJeuFrame.add(menuJeu);

    add(menuPrincipalFrame);

    menuPrincipalFrame.show_all();

    show();
}

void VuePrincipaleGTK::listeActivee(int joueur){
    if(joueur == 1){
        string choix = listeDeroulanteJ1.get_active_text();
        if(choix == "Humain") choixJ1 = 0;
        else{
            for(int i = 1; i < 10; i++){
                if("IA difficulté " + to_string(i) == choix) choixJ1 = i;
            }
        }
    }else{
        string choix = listeDeroulanteJ2.get_active_text();
        if(choix == "Humain") choixJ2 = 0;
        else{
            for(int i = 1; i < 10; i++){
                if("IA difficulté " + to_string(i) == choix) choixJ2 = i;
            }
        }
    }
}

void VuePrincipaleGTK::bouttonJeuPresse(int pChoixJeu){
    choixJeu = pChoixJeu;
    remove();
    add(menuJeuFrame);
    menuJeuFrame.show_all();
}

void VuePrincipaleGTK::bouttonValiderPresse(){
    remove();
    controlleur->traiterChoixMenuPrincipal(choixJeu, choixJ1, choixJ2);
    add(*((VueJeuGTK*)(controlleur->getVueJeu())));
    controlleur->jouer();
}
