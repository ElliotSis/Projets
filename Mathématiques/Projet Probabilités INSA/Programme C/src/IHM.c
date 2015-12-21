#include <stdio.h>
#include "IHM.h"

/*
	Récuper lambda
	Sortie : Un réel positif lambda saisi par l'utilisateur
*/
double recupererLambda(){
	double lambda;
	printf("La valeur de lambda : ");
	scanf("%lf", &lambda);
	return lambda;
}

/*
	Récuper le nombre d'essais
	Sortie : Un entier positif nbEssais saisi par l'utilisateur
*/
int recupererNbEssais(){
	int nbEssais;
	printf("Nombre de simulations pour le calcul de l'esperance : ");
	scanf("%d", &nbEssais);
	return nbEssais;
}

/*
	Afficher l'espérance
	Entrée : Un réel esp
*/
void afficherEsperance(double esp){
	printf("L'esperance est de : %f \n", esp);
}