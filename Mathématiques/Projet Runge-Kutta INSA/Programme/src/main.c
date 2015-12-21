#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NINIT 10000

/* Fonction f
Entrées :
	x : la variable scalaire
	y : une application

Sortie :
	Un réel */
double f(double x, double y){
	return y;
}

/* Procédure rungeKutta34
Entrées :
	a, b : l'intervalle [a,b]
	y0 : la condition de Cauchy
	seuil : le seuil fixé pour l'erreur de consistance
	f : la fonction f(x,y)

Sortie :
	Les x_k, y_k dans le fichier pointsRK34
	Les erreurs de consistances dans le fichier erreurs
	Le pas utilisé dans le fichier pas */
void rungeKutta34(double a, double b, double y0, double seuil, double (*f)(double,double)){
	/* Déclarations
	Variables de type simple
		x : x_k que l'on affiche au fur et à mesure
		y : y_k que l'on affiche au fur et à mesure
		h : le pas h_k
		xtmp : x_{k,i}
		ytmp : y_{k,i}
		phi3 : la fonction phi de la méthode d'ordre 3
		phi4 : la fonction phi de la méthode d'ordre 4
		erreur : l'erreur de consistance
		e : erreur/seuil
		i, j : pour les boucles
		ficPoints, ficErreurs, ficPas : pour les fichiers

	Tableaux
		fct : un tableau pour limiter les appels de la fonction f (couteux)
		rk34 : un tableau constant à double dimension contenant tous les coefficients de la méthode RK34 */
	double x, y, h, xtmp, ytmp, phi3, phi4, erreur, e;
	double fct[4];
	double rk34[6][6];
	int i, j;
	FILE *ficPoints, *ficErreurs, *ficPas;

	/* Initialisation du tableau constant de la méthode RK34
	On initialise que les variables qui nous seront utiles */
	rk34[0][0] = 0.;
	rk34[1][0] = 2./7.;
	rk34[2][0] = 4./7.;
	rk34[3][0] = 6./7.;
	rk34[1][1] = 2./7.;
	rk34[2][1] = -8./35.;
	rk34[3][1] = 29./42.;
	rk34[4][1] = 1./6.;
	rk34[5][1] = 11./96.;
	rk34[2][2] = 4./5.;
	rk34[3][2] = -2./3.;
	rk34[4][2] = 1./6.;
	rk34[5][2] = 7./24.;
	rk34[3][3] = 5./6.;
	rk34[4][3] = 5./12.;
	rk34[5][3] = 35./96.;
	rk34[4][4] = 1./4.;
	rk34[5][4] = 7./48.;
	rk34[5][5] = 1./12.;

	/* Ouverture des fichiers */
	ficPoints = fopen("../data/pointsRK34", "w");
	ficErreurs = fopen("../data/erreursRK34", "w");
	ficPas = fopen("../data/pas", "w");

	/* Initialisation des variables */
	x = a;
	y = y0;
	h = (b-a)/(NINIT);

	/* Écriture du point initial et du pas initial */
	fprintf(ficPoints, "%.50f %.50f\n", x, y);
	fprintf(ficPas, "%.50f\n", h);
	
	/* Boucle principale : parcours de l'intervalle [a,b] */
	while(x<b){
		/* Initialisation des variables */
		xtmp = 0.;
		ytmp = 0.;
		phi3 = 0.;
		phi4 = 0.;

		/* Boucle pour le calcul points intermédiaires */
		for(i = 0 ; i < 4 ; i++){
			/* Calcul de x_{k,i} */
			xtmp = x + h*rk34[i][0];

			/* Calcul de y_{k,i} */
			for(j = 1 ; j <= i ; j++){
				ytmp += rk34[i][j]*fct[j-1];
			}
			ytmp = y + h*ytmp;

			/* Appel de la fonction f puis stockage dans un tableau */
			fct[i] = (*f)(xtmp, ytmp);

			/* Calcul de phi ordre 3 et 4 */
			phi3 += rk34[4][i+1]*fct[i];
			phi4 += rk34[5][i+1]*fct[i];
		}

		/* Calcul de x_{k+1} et y_{k+1} */
		x += h;
		y += h*phi3;

		/* Calcul de l'erreur de consistance */
		phi4 += rk34[5][5]*((*f)(x,y));
		erreur = fabs(h*(phi4 - phi3));

		/* Écriture de l'erreur de consistance */
		fprintf(ficErreurs, "%.50f\n", erreur);

		/* Calcul du coefficient pour calculer le h optimal */
		e = erreur/seuil;

		if((e > 1) && (e > 0)){
			/* Calcul de h optimal */
			h = 0.9*h*pow(1./e, 1./4.);
		}
		else {
			if ((e < 0.9) && (e > 0)){
				/* Calcul de h optimal */
				h = 0.9*h*pow(1./e, 1./4.);
			}
			if(x <= b){
				/* Écriture du point si il respecte la condition du seuil */
				fprintf(ficPoints, "%.50f %.50f\n", x, y);
			}
		}

		/* Écriture du pas */
		fprintf(ficPas, "%.50f\n", h);
	}

	/* Fermeture des fichiers */
	fclose(ficPoints);
	fclose(ficErreurs);
	fclose(ficPas);
}

/* Procédure rungeKutta3
	Même méthode à pas constant */
void rungeKutta3(double a, double b, double y0, int n, double (*f)(double,double)){
	double x, y, h, xtmp, ytmp, phi3, phi4, erreur;
	double fct[4];
	double rk34[6][6];
	int i, j, k;
	FILE *ficPoints, *ficErreurs;

	/* Initialisation du tableau constant de la méthode RK34
	On initialise que les variables qui nous seront utiles */
	rk34[0][0] = 0.;
	rk34[1][0] = 2./7.;
	rk34[2][0] = 4./7.;
	rk34[3][0] = 6./7.;
	rk34[1][1] = 2./7.;
	rk34[2][1] = -8./35.;
	rk34[3][1] = 29./42.;
	rk34[4][1] = 1./6.;
	rk34[5][1] = 11./96.;
	rk34[2][2] = 4./5.;
	rk34[3][2] = -2./3.;
	rk34[4][2] = 1./6.;
	rk34[5][2] = 7./24.;
	rk34[3][3] = 5./6.;
	rk34[4][3] = 5./12.;
	rk34[5][3] = 35./96.;
	rk34[4][4] = 1./4.;
	rk34[5][4] = 7./48.;
	rk34[5][5] = 1./12.;

	/* Ouverture des fichiers */
	ficPoints = fopen("../data/pointsRK3", "w");
	ficErreurs = fopen("../data/erreursRK3", "w");

	/* Initialisation des variables */
	x = a;
	y = y0;
	h = (b-a)/n;

	/* Écriture du point initial */
	fprintf(ficPoints, "%.50f %.50f\n", x, y);
	
	/* Boucle principale : parcours de l'intervalle [a,b] */
	for (k = 0 ; k < n ; k++){
		/* Initialisation des variables */
		xtmp = 0.;
		ytmp = 0.;
		phi3 = 0.;
		phi4 = 0.;

		/* Boucle pour le calcul points intermédiaires */
		for(i = 0 ; i < 4 ; i++){
			/* Calcul de x_{k,i} */
			xtmp = x + h*rk34[i][0];

			/* Calcul de y_{k,i} */
			for(j = 1 ; j <= i ; j++){
				ytmp += rk34[i][j]*fct[j-1];
			}
			ytmp = y + h*ytmp;

			/* Appel de la fonction f puis stockage dans un tableau */
			fct[i] = (*f)(xtmp, ytmp);

			/* Calcul de phi ordre 3 et 4 */
			phi3 += rk34[4][i+1]*fct[i];
			phi4 += rk34[5][i+1]*fct[i];
		}

		/* Calcul de x_{k+1} et y_{k+1} */
		x += h;
		y += h*phi3;

		/* Calcul de l'erreur de consistance */
		phi4 += rk34[5][5]*((*f)(x,y));
		erreur = fabs(h*(phi4 - phi3));

		/* Écriture de l'erreur de consistance */
		fprintf(ficErreurs, "%.50f\n", erreur);

		/* Écriture du point */
		fprintf(ficPoints, "%.50f %.50f\n", x, y);
	}

	/* Fermeture des fichiers */
	fclose(ficPoints);
	fclose(ficErreurs);
}


int main(int argc, char* argv[]){
	double a, b, y0, seuil;
	int n;

	/* Récupération des variables */
	printf("a : ");
	scanf("%lf", &a);
	printf("b : ");
	scanf("%lf", &b);
	printf("y0 : ");
	scanf("%lf", &y0);
	printf("seuil pas variable : ");
	scanf("%lf", &seuil);
	printf("nombre d'itérations pas constant : ");
	scanf("%d", &n);

	/* Appel de la procédure rungeKutta34 */
	rungeKutta34(a, b, y0, seuil, f);

	/* Appel de la procédure rungeKutta3 */
	rungeKutta3(a, b, y0, n, f);

	return EXIT_SUCCESS;
}