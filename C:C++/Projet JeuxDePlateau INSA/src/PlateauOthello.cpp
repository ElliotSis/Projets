#include "PlateauOthello.h"

#include "Case.h"
#include "Couleurs.h"

PlateauOthello::PlateauOthello() : Plateau(8, 8){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            plateau[i][j] = new Case(i, j, this, VERT_FONCE);
        }
    }
}

