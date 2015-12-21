#include <stdio.h>
#include <stdlib.h>
#include "mots_meles.h"

int coupValide(typeCoup coup, int tailleGrille){
	int xi = coup.cinit.x, yi = coup.cinit.y, xf = coup.cfinal.x, yf = coup.cfinal.y;
	int dansGrille = (xi >= 0) && (xi < tailleGrille) && (yi >= 0) && (yi < tailleGrille)
					 && (xf >= 0) && (xf < tailleGrille) && (yf >= 0) && (yf < tailleGrille);
	int memeHorizontale = (yi == yf);
	int memeVerticale = (xi == xf);
	int memeDiagonale = (max(xf - xi, xi - xf) == max(yf - yi, yi - yf));
	return (dansGrille && (memeVerticale || memeHorizontale || memeDiagonale));
}

typeCoup saisirCoup(int tailleGrille){
	typeCoup res;
	do{
		printf("Début du mot (x,y) : ");
		scanf("%d,%d", &(res.cinit.x), &(res.cinit.y));
		printf("fin du mot (x,y) : ");
		scanf("%d,%d", &(res.cfinal.x), &(res.cfinal.y));
	}while(!coupValide(res, tailleGrille));
	return res;
}

int rechercheMot(typeMot *motsATrouver, int nbMots, char *mot){
	int i,j;
	for(i = 0; i<nbMots; i++){
		j = 0;
		while(mot[j] && motsATrouver[i].mot[j] && mot[j] == motsATrouver[i].mot[j])
			j++;
		if(!(mot[j] || motsATrouver[i].mot[j]))
			return i;
	}
	return nbMots;
}

char* extraireMot(char **grille, typeCoup coup){
	int i;
	int xi = coup.cinit.x, yi = coup.cinit.y, xf = coup.cfinal.x, yf = coup.cfinal.y;
	int dx = xf - xi, dy = yf - yi;
	int lgRes = max(max(dx, -dx), max(dy, -dy)) + 1;
	char* res = (char*)malloc((lgRes+1)*sizeof(char));

	if (dx != 0)
		dx = ((dx<0)?(-1):1);
	if (dy != 0)
		dy = ((dy<0)?(-1):1);

	for(i = 0 ; i < lgRes ; i++)
		res[i] = grille[xi + i*dx][yi + i*dy];

	res[lgRes] = '\0';

	return res;
}

void motTrouve(int** grilleTrouve, typeCoup coup){
	int i;
	int xi = coup.cinit.x, yi = coup.cinit.y, xf = coup.cfinal.x, yf = coup.cfinal.y;
	int dx = xf - xi, dy = yf - yi;
	int lgRes = max(max(dx, -dx), max(dy, -dy)) + 1;

	if (dx != 0)
		dx = ((dx<0)?-1:1);
	if (dy != 0)
		dy = ((dy<0)?-1:1);

	for(i = 0 ; i < lgRes ; i++)
		grilleTrouve[xi + i*dx][yi + i*dy] = 1;
}

char ** alloueGrilleChar(int tailleGrille){
	int i;
	char** res = (char**)malloc(tailleGrille*sizeof(char*));
	char* tmp = (char*)malloc(tailleGrille*tailleGrille*sizeof(char));
	if (res == NULL || tmp == NULL)
		return NULL;
	for(i = 0 ; i < tailleGrille ; i++)
		res[i] = &tmp[i*tailleGrille];
	return res;
}

int ** alloueGrilleInt(int tailleGrille){
	int i;
	int** res = (int**)malloc(tailleGrille*sizeof(int*));
	int* tmp = (int*)malloc(tailleGrille*tailleGrille*sizeof(int));
	if (res == NULL || tmp == NULL)
		return NULL;
	for(i = 0 ; i < tailleGrille ; i++)
		res[i] = &tmp[i*tailleGrille];
	return res;
}

void afficheJeu(typeJeu unJeu){
	int i,j;
	printf("mot mêlés :\n");
	printf("   X ");
	for (i = 0; i < unJeu.tailleGrille; i++)
		printf("%d  ", i);
	printf("\n");
	for (i = 0; i < unJeu.tailleGrille; i++){
		printf("   %d", i);
		for (j = 0; j < unJeu.tailleGrille; j++)
			if(unJeu.grilleTrouve[i][j])
				printf("(%c)", unJeu.grille[i][j]);
			else
				printf(" %c ", unJeu.grille[i][j]);
		printf("\t\t");
		if(!(unJeu.motsATrouver[i].trouve)){
			j = 0;
			while (unJeu.motsATrouver[i].mot[j]){
				printf("%c", unJeu.motsATrouver[i].mot[j]);
				j++;
			}
		}
		printf("\n");
	}
}

int toutTrouve(typeMot *motsATrouver, int nbMots){
	int i = 0;
	while(i < nbMots && motsATrouver[i].trouve)
		i++;
	return (i == nbMots);
}

char ** lireGrille(FILE *fic, int *tailleGrille){
	char** res;
	int i,j;
	fscanf(fic, "[TAILLEGRILLE=%d]\n", tailleGrille);
	res = alloueGrilleChar(*tailleGrille);
	for(i = 0; i < *tailleGrille ; i++){
		for (j = 0; j < *tailleGrille ; j++)
			fscanf(fic, "%c ", &(res[i][j]));
		fscanf(fic, "\n");
	}
	return res;
}

typeMot * lireMotsATrouver(FILE *fic, int tailleGrille, int *tailleDico){
	typeMot* res;
	int i,j;
	fscanf(fic, "[TAILLEDICO=%d]\n", tailleDico);
	res = (typeMot*)malloc((*tailleDico)*sizeof(typeMot));
	for (i = 0 ; i < *tailleDico ; i++){
		res[i].mot = (char*)malloc(tailleGrille*sizeof(char));
		fscanf(fic, "%s %d\n", res[i].mot, &(res[i].trouve));
	}
	return res;
}

int chargeJeu(typeJeu *unJeu){
	int trouve;
	FILE* fic = fopen("GRILLE.DATA", "r");
	if (fic != NULL){
		unJeu->grille = lireGrille(fic, &(unJeu->tailleGrille));
		fscanf(fic, "[TROUVE=%d]\n", &trouve);
		unJeu->grilleTrouve = alloueGrilleInt(unJeu->tailleGrille);
		int i,j;
		if (trouve){
			for(i = 0; i < unJeu->tailleGrille ; i++){
				for (j = 0; j < unJeu->tailleGrille ; j++)
						fscanf(fic, "%d ", &(unJeu->grilleTrouve[i][j]));
				fscanf(fic, "\n");
			}
		}
		else{
			for(i = 0; i < unJeu->tailleGrille ; i++)
				for (j = 0; j < unJeu->tailleGrille ; j++)
						unJeu->grilleTrouve[i][j] = 0;
		}
		unJeu->motsATrouver = lireMotsATrouver(fic, unJeu->tailleGrille, &(unJeu->tailleDico));
	}
	else return 0;
	fclose(fic);
	return 1;
}

int sauveJeu(typeJeu unJeu){
	FILE* fic = fopen("GRILLE.DATA", "w");
	if (fic != NULL){
		int i, j, trouve = 0;
		fprintf(fic, "[TAILLEGRILLE=%d]\n", unJeu.tailleGrille);
		for(i = 0 ; i < unJeu.tailleGrille ; i++){
			for(j = 0 ; j < unJeu.tailleGrille ; j++)
				fprintf(fic, "%c ", unJeu.grille[i][j]);
			fprintf(fic, "\n");
		}
		i = 0;
		while (i < unJeu.tailleDico && !trouve){
			trouve = trouve || unJeu.motsATrouver[i].trouve;
			i++;
		}
		fprintf(fic, "[TROUVE=%d]\n", trouve);
		if (trouve){
			for(i = 0; i < unJeu.tailleGrille ; i++){
				for (j = 0; j < unJeu.tailleGrille ; j++)
					fprintf(fic, "%d ", unJeu.grilleTrouve[i][j]);
				fprintf(fic, "\n");
			}
		}
		fprintf(fic, "[TAILLEDICO=%d]\n", unJeu.tailleDico);
		for (i = 0; i < unJeu.tailleDico; i++){
			fprintf(fic, "%s %d\n", unJeu.motsATrouver[i].mot, unJeu.motsATrouver[i].trouve);
		}
	}
	else return 0;
	fclose(fic);
	return 1;
}

int main () {
	int i, j;
	int lg;
	int encore=1;
	typeJeu jeu;
	typeCoup coup;
	char *motATrouver;
	
	if (chargeJeu(&jeu)==0)
		printf("Pas de grille\n");
	else{
		afficheJeu(jeu);
		if (toutTrouve(jeu.motsATrouver, jeu.tailleDico))
			printf("BRAVO !!! Vous avez trouvé tous les mots\n");
		else{ 
			do{
				coup=saisirCoup(jeu.tailleGrille);
				motATrouver=extraireMot(jeu.grille, coup);
				i=rechercheMot(jeu.motsATrouver, jeu.tailleDico, motATrouver);
				if (i<jeu.tailleDico){
					printf("\nBravo, %s trouvé !!!\n\n", motATrouver);
					motTrouve(jeu.grilleTrouve, coup);
					jeu.motsATrouver[i].trouve=1;
				}
				else printf("%s pas un mot à trouver\n", motATrouver);
				afficheJeu(jeu);
				if (toutTrouve(jeu.motsATrouver, jeu.tailleDico)){
					printf("BRAVO !!! Vous avez trouvé tous les mots\n");
					encore=-1;
				}
				else{
					printf("continue ? (oui 1/ non 0) : ");
					scanf("%d", &encore);
				}
			} while (encore==1);
			sauveJeu(jeu);
		}
	}
}