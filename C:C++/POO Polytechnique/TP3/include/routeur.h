#ifndef ROUTEUR_H
#define ROUTEUR_H

#include <vector>

#include "message.h"

//Forward declaration
class Cellulaire;
class Chauffage;
class Maison;

/** \brief Classe représentant un Routeur.
 * \authors Adrien Logut
 * Elliot Sisteron
 * \date 11/10/2015
 */
class Routeur {

public:
    /** \brief Constructeur par défaut
    */
    Routeur();

    /** \brief Retire la connexion au ID donné, ne fait rien si l'id n'est pas co
    * \params id l'id à déconnecter
    */
    void retirerConnexion(unsigned int id);

    /** \brief Achemine le message, affiche aussi si le message a été acheminé
    * de qui vers qui
    * \params message Le message à acheminer
    */
    void acheminerMessage(Message& message);

    /** \brief Accepte une connexion pour une maison
    * Renvoie un message d'erreur et ne fait rien si une maison est déjà co (une seule maison par routeur)
    * \params maison La maison à connecter
    */
    void accepterConnexion(Maison* maison);

    /** \brief Accepte une connexion pour un cellulaire
    * Renvoie un message d'erreur et ne fait rien si le cellulaire en question est déjà co
    * Renvoie un message si le cellulaire est effectivement connecté
    * \params cellulaire Le cellulaire à connecter
    */
    void accepterConnexion(Cellulaire* cellulaire);

    /** \brief Accepte une connexion pour un chauffage
    * Renvoie un message d'erreur et ne fait rien si le chauffage en question est déjà co
    * Renvoie un message si le chauffage est effectivement connecté
    * \params chauffage Le chauffage à connecter
    */
    void accepterConnexion(Chauffage* chauffage);

    /** \brief Renvoie le vecteur de cellulaire en lecture seule
    * \return La liste
    */
    const std::vector<Cellulaire*>& obtenirCellulaires() const;

    /** \brief Renvoie la maison connectée
    * \return maison_
    */
    const Maison* obtenirMaison() const;

private:

    /** \brief Retire le cellulaire de la liste
    * \params it L'itérateur qui pointe sur le cellulaire à retirer
    * it NE DOIT PAS ETRE null OU =std::end
    */
    void retirerElement(std::vector<Cellulaire*>::iterator it);

    /** \brief Retire le chauffage de la liste
    * \params it L'itérateur qui pointe sur le chauffage à retirer
    * it NE DOIT PAS ETRE null OU =std::end
    */
    void retirerElement(std::vector<Chauffage*>::iterator it);

    std::vector<Chauffage*> chauffages_; //!< Liste des chauffages connectés
    std::vector<Cellulaire*> cellulaires_; //!< Liste des cellulaires connectés
    Maison* maison_; //<! Maison connectée au routeur
};

#endif //ROUTEUR_H