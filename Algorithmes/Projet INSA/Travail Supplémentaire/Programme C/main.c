#include <stdio.h>
#include <stdlib.h>
#include "dictionnaire.h"
#include "IHM.h"

int main(){
	int choix;
	char *m, *def, *nomFic;
	Dictionnaire test; 
	creerDictionnaire(test);
	afficherAcceuil();
	while(1){	
		choix = menu();
		switch(choix){
			case 1: 
				afficherDictionnaire(test);
				break;
			case 2: 
				m = recupererChaine("le mot");
				def = recupererChaine("la définition");
				inserer(test, m, def);
				break;
			case 3:
				m = recupererChaine("le mot");
				supprimer(test, m);
				break;
		}
	}
	return 0;
}
