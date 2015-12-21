#include "ControlleurConsole.h"

#include "VueJeuConsoleDames.h"
#include "VueJeuConsoleOthello.h"
#include "VuePrincipaleConsole.h"

ControlleurConsole::ControlleurConsole(){
    vue = new VuePrincipaleConsole(this);
}

void ControlleurConsole::traiterChoixMenuPrincipalVue(int choix){
    switch(choix){
        case 1 : vueJeu = new VueJeuConsoleDames(jeu, this);
                break;
        case 2 : vueJeu = new VueJeuConsoleOthello(jeu, this);
            break;
        default: break;
    }
}

void ControlleurConsole::lancer(){
    vue->afficherMenuPrincipal();
}
