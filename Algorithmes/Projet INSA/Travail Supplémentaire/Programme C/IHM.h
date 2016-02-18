#ifndef __IHM__
#define __IHM__
#define MAX 200
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionnaire.h"

void afficherAcceuil();
int menu();
char* recupererChaine(char* titre);
void afficherDictionnaire(Dictionnaire d);

#endif
