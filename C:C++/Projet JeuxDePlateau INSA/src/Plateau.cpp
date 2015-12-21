#include "Plateau.h"

#include "Case.h"

Plateau::Plateau(int pNbLignes, int pNbColonnes) : nbLignes(pNbLignes), nbColonnes(pNbColonnes){
    plateau = new Case**[nbLignes];
    Case** tmp = new Case*[nbLignes*nbColonnes];
	for(int i = 0; i < nbLignes; i++){
        plateau[i] = tmp + i*nbColonnes;
	}
}

Plateau::~Plateau(){
    for(int i = 0; i < nbLignes; i++){
        for(int j = 0; j < nbColonnes; j++){
            delete plateau[i][j];
        }
    }
    delete[] plateau[0];
    delete[] plateau;
}

int Plateau::getNbLignes() const{
	return nbLignes;
}

int Plateau::getNbColonnes() const{
	return nbColonnes;
}

Case** Plateau::operator[](int i){
	return plateau[i];
}

bool Plateau::estValide(int i, int j) const{
	return (i >= 0 && i < nbLignes && j >= 0 && j < nbColonnes);
}
