#include <stdio.h>
#include "mots_meles.h" /* Erreur : le mauvais fichier .h était inclus */

int verifCoord(int x, int y, int tailleGrille){
	return (x >= 0) && (x < tailleGrille) && (y >= 0) && (y < tailleGrille);
}

typeCoord calculeDirection(DIRECTION dir){
	typeCoord res;
	switch(dir){
		case E : res.x = 0; res.y = 1;
				break;
		case W : res.x = 0; res.y = -1;
				break;
		case N : res.x = -1; res.y = 0;
				break;
		case S : res.x = 1; res.y = 0;
				break;
		case NE : res.x = -1; res.y = 1;
				break;
		case SE : res.x = 1; res.y = 1;
				break;
		case NW : res.x = -1; res.y = -1;
				break;
		case SW : res.x = 1; res.y = -1;
				break;
	}
	return res;
}

int compareMots(char mot1[TAILLEGRILLE], int lgMot1, char mot2[TAILLEGRILLE], int lgMot2){
	if(lgMot1 != lgMot2)
		return 0;
	else{
		int i = 0;
		while (i < lgMot1 && mot1[i] == mot2[i])
			i++;
		return (i == lgMot1);
	}
}

int rechercheMot(typeMot motsATrouver[LGDICO], char mot[TAILLEGRILLE], int lgMot){
	int i;
	for(i = 0; i<LGDICO; i++)
		if(compareMots(motsATrouver[i].mot, motsATrouver[i].tailleMot, mot, lgMot))
			return i;
	return LGDICO;
}

int extraireMot(char grille[TAILLEGRILLE][TAILLEGRILLE], int x, int y , int dx, int dy, char mot[TAILLEGRILLE], int lgMot){
	int i = 0;
	while(i < lgMot && verifCoord(x + i*dx,y + i*dy,TAILLEGRILLE)){
		mot[i] = grille[x + i*dx][y + i*dy];
		i++;
	}	
	return i;
}

void motTrouve(int grilleTrouve[TAILLEGRILLE][TAILLEGRILLE], int x, int y , int dx, int dy, int lg){
	int xActuel = x, yActuel = y;
	int i;
	for(i = 0; i < lg ; i++){
		grilleTrouve[xActuel][yActuel] = 1;
		xActuel += dx;
		yActuel += dy;
	}
}

void afficheMot(char mot[TAILLEGRILLE], int lgMot){
	int i;
	for(i = 0; i<lgMot ; i++)
		printf("%c", mot[i]);
}

void afficheGrille(char grille[TAILLEGRILLE][TAILLEGRILLE], int grilleTrouve[TAILLEGRILLE][TAILLEGRILLE],
typeMot motsATrouver[LGDICO]){
	int i,j;
	printf("mot mêlés :\n");
	printf("   X ");
	for (i = 0; i < TAILLEGRILLE; i++)
		printf("%d  ", i);
	printf("\n");
	for (i = 0; i < TAILLEGRILLE; i++){
		printf("   %d", i);
		for (j = 0; j < TAILLEGRILLE; j++)
			if(grilleTrouve[i][j])
				printf("(%c)", grille[i][j]);
			else
				printf(" %c ", grille[i][j]);
		printf("\t\t");
		if(!(motsATrouver[i].trouve))
			afficheMot(motsATrouver[i].mot, motsATrouver[i].tailleMot);
		printf("\n");
	}
}

int toutTrouve(typeMot motsATrouver[LGDICO]){
	int i = 0;
	while(i < LGDICO && motsATrouver[i].trouve)
		i++;
	return (i == LGDICO);
}

typeCoup saisirCoup(){
	typeCoup res;
	typeCoord tmp;
	int i;
	printf("Début du mot (x,y) : ");
	scanf("%d,%d", &(res.x), &(res.y));
	printf("direction (E=0, W=1, N=2, S=3, NE=4, SE=5, NW=6, SW=7) : ");
	scanf("%d", &i);
	tmp = calculeDirection((DIRECTION)i);
	res.dx = tmp.x;
	res.dy = tmp.y;
	printf("longueur : ");
	scanf("%d", &res.lg);
	return res;
}

int main () {
	int i, j;
	int lg;
	int encore;
	typeCoup coup;
	char grilleJeu[TAILLEGRILLE][TAILLEGRILLE]={ {'A', 'I', 'N', 'T', 'J'},
												 {'R', 'F', 'H', 'S', 'E'},
												 {'K', 'A', 'H', 'N', 'U'},
												 {'P', 'A', 'H', 'O', 'T'},
												 {'E', 'S', 'A', 'C', 'Y'} };
	typeMot motsATrouver[LGDICO]={ {2, {'I', 'F'}, 0},
								   {3, {'I', 'N', 'T'}, 0},
								   {4, {'C', 'H', 'A', 'R'}, 0}, /* Erreur : il manquait une virgule */
								   {4, {'C', 'A', 'S', 'E'}, 0},
								   {5, {'C', 'O', 'N', 'S', 'T'}, 0} };
	int grilleTrouve[TAILLEGRILLE][TAILLEGRILLE]; /* Erreur : pas de .. mais [][] */
	char motATrouver[TAILLEGRILLE]; 

	for (i=0; i<TAILLEGRILLE; i++) /* Erreur : on met des ; dans les for, pas des virgules */
		for (j=0; j<TAILLEGRILLE; j++) /* Erreur : pas de ; à la fin de la ligne */
			grilleTrouve[i][j]=0;

	afficheGrille(grilleJeu, grilleTrouve, motsATrouver);
	
	do {
		coup=saisirCoup();
		lg=extraireMot(grilleJeu, coup.x, coup.y, coup.dx, coup.dy, motATrouver, coup.lg);
		i=rechercheMot(motsATrouver, motATrouver, lg);

		if (i<LGDICO)
		{
			printf("\nBravo, ");
			afficheMot(motATrouver, lg);
			printf(" trouvé !!!\n\n");
			motTrouve(grilleTrouve, coup.x, coup.y, coup.dx, coup.dy, lg);
			motsATrouver[i].trouve=1;
		}
		else { /* Erreur : il manquait des accolades */
			afficheMot(motATrouver, lg);
			printf(" pas dans la grille\n");
		}

		afficheGrille(grilleJeu, grilleTrouve, motsATrouver);

		if (toutTrouve(motsATrouver)) {
			printf("BRAVO !!! Vous avez trouvé tous les mots\n");
			encore=0;
		}
		else { 
			printf("continue ? (oui 1/ non 0) : ");
			scanf("%d", &encore); /* 2 Erreurs : c'est un %d et il manquait un & devant encore */
		}
	} while (encore!=0);
}