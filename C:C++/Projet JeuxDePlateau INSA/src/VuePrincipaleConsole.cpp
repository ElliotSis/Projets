#include "VuePrincipaleConsole.h"

#include "Controlleur.h"

#include <iostream>

using namespace std;

VuePrincipaleConsole::VuePrincipaleConsole(Controlleur* pControlleur) : VuePrincipale(pControlleur){}

void VuePrincipaleConsole::afficherMenuPrincipal(){
    int choixJeu, choixJ1, choixJ2;
    cout << "Sélectionnez le jeu :" << endl;
    cout << " 1 - Dames" << endl;
    cout << " 2 - Othello" << endl;
    cout << " 3 - Puissance 4" << endl;
    cout << endl;
    choixJeu = lireChoixMenuPrincipal();
    cout << "Sélectionnez la difficulté du joueur 1 (0 pour un joueur Humain) : ";
    choixJ1 = lireChoixMenuJeu();
    cout << "Sélectionnez la difficulté du joueur 2 (0 pour un joueur Humain) : ";
    choixJ2 = lireChoixMenuJeu();
    controlleur->traiterChoixMenuPrincipal(choixJeu, choixJ1, choixJ2);
    controlleur->jouer();
}

int VuePrincipaleConsole::lireChoixMenuPrincipal(){
    int choix;
    do{
        cout << "Choix : ";
        cin >> choix; cin.ignore();
    }while(choix != 1 && choix != 2);
    return choix;
}

int VuePrincipaleConsole::lireChoixMenuJeu(){
    int choix;
    do{
        cin >> choix; cin.ignore();
    }while(choix < 0 || choix > 9);
    return choix;
}
