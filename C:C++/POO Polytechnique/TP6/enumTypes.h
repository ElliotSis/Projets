#ifndef ENUMTYPES_H
#define ENUMTYPES_H


/* Enumeration pour les types de messages disponibles
- ALLUMAGE_AUTOMATIQUE: A envoyer pour allumer un/des chauffage(s) automatique.
- ALLUMER_CHAUFFAGE: A envoyer pour allumer un/des chauffage(s) (automatique ou non).
- ETTEINDRE_CHAUFFAGE: A envoyer pour eteindre un/des chauffage(s) (automatique ou non).
- NOTIFICATION_VISITEUR: A envoyer a un cellulaire pour le notifier d'un nouveau visiteur.
*/
enum TYPE_MESSAGE 
{ 
	ALLUMAGE_AUTOMATIQUE,
	ALLUMER_CHAUFFAGE,
	ETTEINDRE_CHAUFFAGE,
	NOTIFICATION_VISITEUR 
};



/* Enumeration pour les types de gouts disponibles
- SUCRE:	Le gout est sucré.
- SALE:		Le gout est salé.
- NEUTRE:	Le gout est ni sucré, ni salé
*/
enum TYPE_GUSTATIF
{
	SUCRE,
	SALE,
	NEUTRE
};



#endif