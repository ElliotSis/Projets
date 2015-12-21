#include "ControlleurGTK.h"
#include "ControlleurConsole.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
    Controlleur* controlleur;

    if(argc > 1){
        controlleur = new ControlleurConsole();
    }else{
        controlleur = new ControlleurGTK();
    }

    controlleur->lancer();

    delete controlleur;

    return 0;
}
