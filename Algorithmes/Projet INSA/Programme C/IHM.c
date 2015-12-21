#include "IHM.h"

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
        c = getchar();
}

void afficherAcceuil(){
	printf(" –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
	printf("|===========================================================|\n");
	printf("|============== GESTIONNAIRE DE DICTIONNAIRES ==============|\n");
	printf("|===========================================================|\n");
	printf(" –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
}

int menu(){
	int res;
	do{
		printf("|\n|\n|  1: Afficher le dictionnaire\n");
		printf("|  2: Rentrer un mot et sa définition dans le dictionnaire\n");
		printf("|  3: Supprimer un mot\n");
		printf("|\n|\n");
		printf("| Votre choix ? ");
		scanf("%d", &res);
		viderBuffer();
	}while((res < 1) || (res > 6));
	return res;
}

char* recupererChaine(char* titre){
	char buffer[MAX];
	char* res = NULL;
	char* positionEntree = NULL;
	printf("| Rentrez %s : ", titre);
	if (fgets(buffer, MAX, stdin) != NULL){
		positionEntree = strchr(buffer, '\n');
        if (positionEntree != NULL){
        		*positionEntree = '\0';
        		res = (char*)malloc(strlen(buffer)*sizeof(char));
        		strcpy(res, buffer);
        }
		else
			viderBuffer();
	}
	else
		viderBuffer();
	return res;
}

void afficherDictionnaire(Dictionnaire d){
	char i;
	ListeChaineeMD curseur;
	printf("|\n");
	for(i = 0; i < 26 ; i++){
		curseur = d[i];
		printf("| Mots commençant par %c : \n|\n", i + 'A');
		while(curseur != NULL){
			printf("| Mot : %s\n", curseur->mot);
			printf("| Définition : %s\n|\n", curseur->definition);
			curseur = curseur->suivant;
		}
	}
}

