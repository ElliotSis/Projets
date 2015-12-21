//
// Created by adrien on 15-10-28.
//

#ifndef TP4_OBSERVATEUR_H
#define TP4_OBSERVATEUR_H

class Observable;

class Observateur{
public:
    virtual void mettreAJour(Observable* observable) = 0;
};

#endif //TP4_OBSERVATEUR_H
