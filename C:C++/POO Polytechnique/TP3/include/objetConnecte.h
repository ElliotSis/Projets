#ifndef OBJETCONNECTE_H
#define OBJETCONNECTE_H

#include "message.h"
#include "routeur.h"

/** \brief Classe représentant un Objet Connecté.
 * \authors Adrien Logut
 * Elliot Sisteron
 * \date 16/10/2015
 */
class ObjetConnecte {
public:
	/** \brief Constructeur de objetConnecte
	 * \param id L'identifiant unique de l'objet
     */
	ObjetConnecte(unsigned int id);

	/** \brief Se connecte au routeur
	 * \param routeur Le routeur auquel on se connecte
	 */
	virtual void seConnecter(Routeur* routeur);

	/** \brief Se déconnecte du routeur
	 */
	void seDeconnecter();

	/** \brief Accède à la variable id
     * \return La valeur de la variable id_.
     */
	unsigned int obtenirId() const;

	/** \brief Envoie un message
	 * \param message Le message à envoyer
	 */
	void envoyerMessage(Message& message);

	/** \brief Reçois un message
	 * \param message Le message à recevoir
	 */
	virtual void recevoirMessage(Message& message);

	/** \brief Est connecté
	 * return connecte_
	 */
	bool estConnecte();

protected:
	unsigned int id_;
	bool connecte_;
	Routeur* routeur_;
};
#endif