#ifndef CELLULAIRE_H
#define CELLULAIRE_H

#include <iostream>
#include <string>

#include "gps.h"
#include "message.h"
#include "objetConnecte.h"
#include "observable.h"

// Forward declaration
class Personne;

/** \brief Classe représentant un Cellulaire.
 * \author Adrien Logut 
 * \date 16/09/2015
 */
class Cellulaire : public ObjetConnecte, public Observable{
public:
    /** \brief Constructeur de Cellulaire.
     * \param id L'identifiant de l'objet connecté
     * \param numero La valeur à affecter à la variable numero_.
     */
    Cellulaire(unsigned int id, std::string numero);

    /** \brief Destructeur par défaut.
     */
    virtual ~Cellulaire();

    /** \brief Accède à la variable numero_.
     * \return La valeur de la variable numero_.
     */
    std::string obtenirNumero() const;

    /** \brief Modifie la variable numero_.
     * \param numero La nouvelle valeur à affecter à la variable numero_.
     */
    void modifierNumero(std::string numero);

    /** \brief Accède à la variable personne_.
     * \return La valeur de la variable personne_.
     */
    Personne* obtenirPersonne() const;

    /** \brief Modifie la variable personne_.
     * \param personne La nouvelle valeur à affecter à la variable personne_.
     */
    void modifierPersonne(Personne* personne);

    /** \brief Accède à la variable position_ de la variable gps_.
     * \return La valeur de la variable position_ de la variable gps_.
     */
    float obtenirPositionGps() const;

    /** \brief Modifie la variable position_ de la variable gps_.
     * \param position La nouvelle valeur à affecter à la variable position_ de la variable gps_.
     */
    void assignerPosition(float position);

    /** \brief Évalue si le cellulaire est proche d'une position.
     * \param position La position à évaluer.
     * \return *true* si le cellulaire est proche de la position, *false* sinon.
     */
    bool estProche(float position);

    /** \brief Opérateur d'égalité.
     * \param cellulaire1 Le premier cellulaire à comparer.
     * \param cellulaire2 Le deuxième cellulaire à comparer.
     * \return Un booléen valant true si les numéros sont identiques et sont assimilés à la même personne, false sinon.
     */
    friend bool operator==(const Cellulaire& cellulaire1, const Cellulaire& cellulaire2);

    /** \brief Opérateur de comparaison inférieure stricte.
     * \param cellulaire1 Le premier cellulaire à comparer.
     * \param cellulaire2 Le deuxième cellulaire à comparer.
     * \return Un booléen valant true si le numéro1 est plus petit (au sens string et arithmétique) que numéro2, false sinon.
     */
    friend bool operator<(const Cellulaire& cellulaire1, const Cellulaire& cellulaire2);

    /** \brief Opérateur de flux de sortie.
  * \param out Le flux de sortie.
  * \param cellulaire Le cellulaire à afficher sur le flux de sortie.
  * \return Le flux de sortie.
  */
    friend std::ostream& operator<<(std::ostream& out, const Cellulaire& cellulaire);

    /** \brief Affiche une notification
    * \param message Le message à afficher
    */
    void recevoirMessage(Message& message);

    std::string obtenirNomClasse() const;

private:
    std::string numero_; //!< Numéro du cellulaire.

    Personne* personne_; //!< Personne propriétaire du cellulaire.

    GPS gps_; //!< GPS intégré au cellulaire
};

#endif // CELLULAIRE_H