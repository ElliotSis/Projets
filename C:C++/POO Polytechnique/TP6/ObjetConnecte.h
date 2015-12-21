#ifndef OBJETCONNECTE_H
#define OBJETCONNECTE_H

#include <string>
#include "Message.h"
#include <QObject>


// !!!!!!!!!! A FAIRE !!!!!!!!!!!!
// Vous devez modifier la classe pour qu'elle hérite de QObject
// Vous devez aussi ajouter la définition des signaux suivants :
// signal_bonjour() et signal_aurevoir()
	
class Routeur;
class ObjetConnecte : public QObject
{
    Q_OBJECT
public:
    explicit ObjetConnecte(unsigned int id);
	bool seConnecter(Routeur* routeur);
    void seDeconnecter();
	void envoyerMessage(Message* message);
    virtual void recevoirMessage(Message* message) = 0;

	unsigned int getId() const;
	bool isConnected() const;

	void setIsConnected(bool value);

signals:
    void signal_bonjour();
    void signal_aurevoir();

protected:
	unsigned int id_;
	Routeur *routeur_;
	bool estConnecte_;
};
#endif
