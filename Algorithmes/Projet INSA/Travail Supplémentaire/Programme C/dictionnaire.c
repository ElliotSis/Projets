#include "dictionnaire.h"

char maj(char c){
	char res = c;
	if((c >= 'a') && (c <= 'z')){
		res = res - 'a' + 'A';
	}
	return res;
}

int estUnMot(char* ch){
	int i = 0, lg = strlen(ch);
	while((i < lg) && (ch[i] != ' '))
		i++;
	return (i == lg);
}

void creerDictionnaire(Dictionnaire res){
	int i;
	for(i = 0; i < 26 ; i++)
		res[i] = NULL;
}

int estPresent(Dictionnaire d, char* m){
	ListeChaineeMD curseur;
	curseur = d[maj(m[0]) - 65];
	while((curseur != NULL) && (strcmp(curseur->mot, m) < 0))
		curseur = curseur->suivant;
	return ((curseur != NULL) && (strcmp(curseur->mot, m) == 0));
}

char* obtenirDefinition(Dictionnaire d, char* m){
	char* res = NULL;	
	ListeChaineeMD curseur;
	curseur = d[maj(m[0]) - 65];
	while((curseur != NULL) && (strcmp(curseur->mot, m) < 0))
		curseur = curseur->suivant;
	if ((curseur != NULL) && (strcmp(curseur->mot, m) == 0))
		res = curseur->definition;
	return (res);
}

void inserer(Dictionnaire d, char* m, char* def){
	ListeChaineeMD tmp, curseur;
	curseur = d[maj(m[0]) - 65];
	if ((curseur == NULL) || ((strcmp(curseur->mot, m) > 0))){
		tmp = (ListeChaineeMD)malloc(sizeof(Noeud));
		tmp->mot = m;
		tmp->definition = def;
		d[maj(m[0]) - 65] = tmp;
		tmp->suivant = curseur;
	}
	else{
		if (strcmp(curseur->mot, m) != 0){
			while((curseur->suivant != NULL) && (strcmp((curseur->suivant)->mot, m) < 0))
				curseur = curseur->suivant;
			if ((curseur->suivant == NULL) || (strcmp((curseur->suivant)->mot, m) != 0)){
				tmp = (ListeChaineeMD)malloc(sizeof(Noeud));
				tmp->mot = m;
				tmp->definition = def;
				tmp->suivant = curseur->suivant;
				curseur->suivant = tmp;			
			}
		}
	}	
}

void supprimer(Dictionnaire d, char* m){
	ListeChaineeMD tmp, curseur;
	curseur = d[maj(m[0]) - 65];
	if (curseur != NULL){
		if (strcmp(curseur->mot, m) == 0){
			d[maj(m[0]) - 65] = curseur->suivant;
			free(curseur);
		}
		else{
			while((curseur->suivant != NULL) && (strcmp((curseur->suivant)->mot, m) < 0))
				curseur = curseur->suivant;
			if ((curseur->suivant != NULL) && (strcmp((curseur->suivant)->mot, m) == 0)){
				tmp = curseur->suivant;
				curseur->suivant = (curseur->suivant)->suivant;
				free(tmp);
			}
		}	
	}
}

void ajouterListeMD(Dictionnaire d, ListeChaineeMD l){
	while(l != NULL){
		inserer(d, l->mot, l->definition);
		l = l->suivant;
	}
}

void fusionner(Dictionnaire res, Dictionnaire d1, Dictionnaire d2){
	creerDictionnaire(res);
	int i;
	for(i = 0; i < 26 ; i++){
		ajouterListeMD(res, d1[i]);
		ajouterListeMD(res, d2[i]);
	}
}
