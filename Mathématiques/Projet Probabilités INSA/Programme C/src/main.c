#include <stdlib.h>
#include <time.h>
#include "IHM.h"
#include "simulation.h"

/*
	Programme principal
*/

int main(int argc, char* argv[]){
	/* Saisie utilisateur */
	double lambda = recupererLambda();
	int nbEssais = recupererNbEssais();

	/* Initialisation de la graine */
	srand(time(NULL));

	/* Calcul et affichage de l'espérance */
	afficherEsperance(simulerEsperanceAt(simulerUnHoraire(), lambda, nbEssais));

	return EXIT_SUCCESS;
}