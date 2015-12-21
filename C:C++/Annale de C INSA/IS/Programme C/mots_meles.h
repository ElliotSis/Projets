#include <stdio.h>

/* macro pour la taille de la grille */
#define TAILLEGRILLE 5

/* macro pour le nombre de mots à trouver */
#define LGDICO 5

/* type énuméré pour choisir la direction : E=0, W=1, N=2, S=3, NE=4, SE=5, NW=6, SW=7 */
typedef enum 
{ E, W, N, S, NE, SE, NW, SW } DIRECTION;

/* type coordonnées */
typedef struct
{ int x, y; } typeCoord;

/* type pour définir les coups à jouer */
/* x et y sont l'origine du mot sélectionné dans la grille */
/* dx et dy sont la direction dans laquelle on sélectionne le mot : 0, -1 ou 1 pour chacun */
/* lg est la longueur du mot sélectionné */
typedef struct
{ int x, y, dx, dy, lg; } typeCoup;

/* typeMot pour définir les mots à trouver ainsi que leur longueur et s'ils ont été trouvés ou non */
typedef struct{ 
	int tailleMot;
	char mot[TAILLEGRILLE];
	int trouve; 
} typeMot;

int verifCoord(int x, int y, int tailleGrille);
/* retourne vrai (1) si les coordonnées x, y sont dans la grille, faux (0) sinon */

typeCoord calculeDirection(DIRECTION dir);
/* direction (E=0,1 - W=0,-1 - N=-1,0 - S=1,0, NE=-1,1 - SE=1,1 NW=-1,-1 - SW=1,-1) */

int compareMots(char mot1[TAILLEGRILLE], int lgMot1, char mot2[TAILLEGRILLE], int lgMot2);
/* retourne 1 si les mots sont identiques, 0 sinon */

int rechercheMot(typeMot motsATrouver[LGDICO], char mot[TAILLEGRILLE], int lgMot);
/* retourne l'indice du mot s'il est trouve, LGDICO sinon */

int extraireMot(char grille[TAILLEGRILLE][TAILLEGRILLE], int x, int y , int dx, int dy, char mot[TAILLEGRILLE], int
lgMot);
/* extrait et stocke dans mot la suite de lgMot caractères commencant à l'indice x,y dans la direction dx,dy
retourne la longueur du mot extrait (au plus lgMot caractère) */

void motTrouve(int grilleTrouve[TAILLEGRILLE][TAILLEGRILLE], int x, int y , int dx, int dy, int lg);
/* met à jour les booléens du mot trouvé dans la grille */

void afficheMot(char mot[TAILLEGRILLE], int lgMot);
/* affiche le mot */

void afficheGrille(char grille[TAILLEGRILLE][TAILLEGRILLE], int grilleTrouve[TAILLEGRILLE][TAILLEGRILLE],
typeMot motsATrouver[LGDICO]);
/* affiche une grille dont les mots trouvés sont entourés, ainsi que la liste des mots restants à trouver */

int toutTrouve(typeMot motsATrouver[LGDICO]);
/* retourne 1 si tous les mots ont été trouvés, 0 sinon */

typeCoup saisirCoup();