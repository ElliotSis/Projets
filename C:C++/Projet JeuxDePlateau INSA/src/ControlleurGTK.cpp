#include "ControlleurGTK.h"

#include "Jeu.h"
#include "Joueur.h"
#include "VueJeuGTKDames.h"
#include "VueJeuGTKOthello.h"
#include "VuePrincipaleGTK.h"

ControlleurGTK::ControlleurGTK(){
	/*int argc = 1;
	char** argv = new char*[1];
	argv[0] = "inutile";
    app = Gtk::Application::create(argc, argv);*/
	app = Gtk::Application::create();
    vue = new VuePrincipaleGTK(this);
}

void ControlleurGTK::traiterChoixMenuPrincipalVue(int choix){
    switch(choix){
        case 1 : vueJeu = new VueJeuGTKDames(jeu, this);
                break;
        case 2 : vueJeu = new VueJeuGTKOthello(jeu, this);
            break;
        default: break;
    }
}

void ControlleurGTK::lancer(){
    app->run(*((VuePrincipaleGTK*)vue));
}
