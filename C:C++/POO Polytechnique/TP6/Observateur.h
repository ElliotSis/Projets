#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H

class Observable;
class Observateur
{
public:
	virtual void mettreAJour(Observable*) = 0;
private:

};
#endif