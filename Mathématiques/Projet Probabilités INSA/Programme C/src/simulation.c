#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "simulation.h"

/*
	Constante : temps maximal
*/
double const T_MAX = 1000;


/*
	Simuler une loi uniforme
	Entrée : l'intervalle [a,b]
	Sortie : Un réel au hasard dans cet intervalle
*/
double simulerUneLoiUniforme(double a, double b){
	return (a + (b-a)*(rand()/((double)RAND_MAX)));
}

/*
	Simuler un horaire
	Sortie : Un réel au hasard dans l'intervalle [0,T_MAX]
*/
double simulerUnHoraire(){
	return (simulerUneLoiUniforme(0,T_MAX));
}

/*
	Simuler une loi exponentielle
	Entrée : Un réel lambda
	Sortie : Un réel au hasard suivant la loi exponentielle de paramètre lambda
*/
double simulerUneLoiExp(double lambda){
	return (-log(simulerUneLoiUniforme(0,1))/lambda);
}

/*
	Simuler la variable aléatoire At
	Entrée : Un horaire réel positif t
			 Un réel lambda
	Sortie : Un réel au hasard en suivant la loi de At
*/


double simulerAt(double t, double lambda){
	double sum = 0;
	while (t > sum)
		sum += simulerUneLoiExp(lambda);
	return (sum - t);
}

/*
	Simuler l'espérance de la variable aléatoire At
	Entrée : Un horaire réel positif t
			 Un réel lambda
			 Un nombre de simulations de At
	Sortie : Un réel calculant l'espérance de At
*/
double simulerEsperanceAt(double t, double lambda, int nbEssais){
	int i = 0;
	double sum = 0;
	for (i = 0 ; i < nbEssais ; i++)
		sum += simulerAt(t, lambda);
	return (sum/nbEssais);
}