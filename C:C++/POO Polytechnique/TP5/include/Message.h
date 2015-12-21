/*
Fichier: message.h
Auteur(s): Karim Keddam
Date de creation: 25 septembre 2015
Date de modification: 02 octobre 2015
Description: Cette classe represente un message permettant de communiquer entre deux objets de type ObjetConnecte.
*/

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include "enumTypes.h"

class Message
{
public:
	// Contrcuteur
	Message(unsigned int src, unsigned int dest, TYPE_MESSAGE type);
	// Destructeur
	~Message();

	// Accesseurs
	unsigned int getSrc() const;
	unsigned int getDest() const;
	TYPE_MESSAGE getType() const;

// TP5 A COMPLETER
	virtual std::string obtenirNomClasse() const;
private:
	// Attribut représentant l'ID de l'objet source (expéditeur)
	unsigned int idSrc_;
	// Attribut représentant l'ID de l'objet destination (déstinataire)
	unsigned int idDest_;
	// Attribut relatif au type de message
	TYPE_MESSAGE type_;
};

#endif