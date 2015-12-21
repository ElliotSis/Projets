#include <stdio.h>
#include <stdlib.h>

/* macro pour le maximum de a et b */
#define max(a,b) (((a)<(b))?(b):(a))

/* type coordonnées */
typedef struct { int x, y; } typeCoord;

/* type pour définir les coups à jouer */
/* cinit est la coordonnée initiale du mot sélectionné dans la grille */
/* cfinal est la coordonnée final du mot sélectionné dans la grille */
typedef struct { typeCoord cinit, cfinal; } typeCoup;

/* type pour définir les mots à trouver et s'ils ont été trouvés ou non */
typedef struct {
	char *mot; // chaine de caractère pour le mot
	int trouve; // booléen pour savoir s'il a été trouvé ou non
} typeMot;

/* type pour définir un jeu de mots mêlés */
typedef struct {
	int tailleGrille; // taille de la grille
	char** grille; // matrice dynamique de caractères
	int** grilleTrouve; // matrice dynamique de booléens
	int tailleDico; // nombre de mots à trouver
	typeMot* motsATrouver; // tableau dynamique des mots à trouver
} typeJeu;

/* retourne 1 si un coup est valide,
c'est-à-dire que les 2 coordonnées sont alignées et dans la grille */
int coupValide(typeCoup coup, int tailleGrille);

/* retourne un coup valide saisi par l'utilisateur */
typeCoup saisirCoup(int tailleGrille);

/* retourne l'indice du mot s'il est trouve, nbMots sinon */
int rechercheMot(typeMot *motsATrouver, int nbMots, char *mot);

/* extrait et retourne le mot entre les indices cinit et cfinal du coup
On suppose le coup valide */
char * extraireMot(char **grille, typeCoup coup);

/* met à jour les booléens du mot trouvé dans la grille
On suppose le coup valide */
void motTrouve(int **grilleTrouve, typeCoup coup);

/* retourne 1 si tous les mots sont trouvés, 0 sinon */
int toutTrouve(typeMot *motsATrouver, int nbMots);

/* affiche une grille dont les mots trouvés sont entourés, ainsi que la liste des mots
restants à trouver */
void afficheJeu(typeJeu unJeu);

/* alloue et retourne une grille de tailleGrille x tailleGrille caractères */
char ** alloueGrilleChar(int tailleGrille);

/* alloue et retourne une grille de tailleGrille x tailleGrille entiers */
int ** alloueGrilleInt(int tailleGrille);

/* lit dans un fichier une grille de mots mélés */
char ** lireGrille(FILE *fic, int *tailleGrille);

/* lit dans un fichier les mots à trouver dans la grille de mots mélés */
typeMot * lireMotsATrouver(FILE *fic, int tailleGrille, int *tailleDico);

/* charge à partir d'un fichier une grille de mots mélés
ainsi que la liste des mots à trouver */
int chargeJeu(typeJeu *unJeu);

/* sauvegarde une partie dans un fichier */
int sauveJeu(typeJeu unJeu);