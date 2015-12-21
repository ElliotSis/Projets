#ifndef ROUTEUR_H
#define ROUTEUR_H

#include <vector>

#include "message.h"

/** \brief Classe représentant un Routeur.
 * \authors Adrien Logut
 * Elliot Sisteron
 * \date 11/10/2015
 */

//Forward declaration
class ObjetConnecte;

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

    /** \brief Accepte une connexion pour l'objetConnecte
    * \params objetConnecte l'objetConnecte à connecter
    */
    void accepterConnexion(ObjetConnecte* objetConnecte);

private:

    /** \brief Retire l'objetConnecte de la liste
    * \params it L'itérateur qui pointe sur l'objetConnecte à retirer
    * it NE DOIT PAS ETRE null OU =std::end
    */
    void retirerElement(std::vector<ObjetConnecte*>::iterator it);

    std::vector<ObjetConnecte*> objetsConnectes_; //!< Liste des objets connectés
};

#endif //ROUTEUR_H