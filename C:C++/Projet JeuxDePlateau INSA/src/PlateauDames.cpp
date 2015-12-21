#include "PlateauDames.h"

#include "Case.h"
#include "Couleurs.h"

PlateauDames::PlateauDames() : Plateau(10, 10){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if((i%2 == 0 && j%2 == 0) || (i%2 != 0 && j%2 != 0)){
                plateau[i][j] = new Case(i, j, this, BEIGE_CLAIR);
            }
            else{
                plateau[i][j] = new Case(i, j, this, BEIGE_FONCE);
            }
        }
    }
}
