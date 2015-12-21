/*
Fichier: message.h
Auteur(s): Karim Keddam
Date de creation: 25 septembre 2015
Date de modification: 11 octobre 2015
Description: Cette classe represente un message permettant de communiquer entre deux objets de type ObjetConnecte.
Adrien LOGUT : Changement de ETTEINDRE_CHAUFFAGE pour ETEINDRE_CHAUFFAGE (simple correction orthographique)
*/

#ifndef MESSAGE_H
#define MESSAGE_H

// Enumeration pour les types de messages disponibles
enum TYPE_MESSAGE {ALLUMAGE_AUTOMATIQUE, ALLUMER_CHAUFFAGE, ETEINDRE_CHAUFFAGE, NOTIFICATION_VISITEUR};

/** \brief Classe représentant un Message.
 * \author Karim Keddam
 * \date 25/09/2015
 */
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

private:
	// Attribut représentant l'ID de l'objet source (expéditeur)
	unsigned int idSrc_;
	// Attribut représentant l'ID de l'objet destination (déstinataire)
	unsigned int idDest_;
	// Attribut relatif au type de message
	TYPE_MESSAGE type_;
};

#endif