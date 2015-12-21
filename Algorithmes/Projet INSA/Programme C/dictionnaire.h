#ifndef __DICTIONNAIRE__
#define __DICTIONNAIRE__
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Noeud {
	char* mot;
	char* definition;
	struct Noeud* suivant;
} Noeud;
typedef Noeud* ListeChaineeMD;
typedef ListeChaineeMD Dictionnaire[26];

int estUnMot(char* ch);
void creerDictionnaire(Dictionnaire res);
int estPresent(Dictionnaire d, char* m);
char* obtenirDefinition(Dictionnaire d, char* m);
void inserer(Dictionnaire d, char* m, char* def);
void supprimer(Dictionnaire d, char* m);
void fusionner(Dictionnaire res, Dictionnaire d1, Dictionnaire d2);

#endif