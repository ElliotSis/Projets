/*
	Module : simulation
	Utilité : Simuler des lois de probabilités
*/

double simulerUneLoiUniforme(double a, double b);
double simulerUneLoiExp(double lambda);
double simulerUnHoraire();
double simulerAt(double t, double lambda);
double simulerEsperanceAt(double t, double lambda, int nbEssais);