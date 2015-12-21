#ifndef MAISON_H
#define MAISON_H

#include <string>
#include <vector>

#include "message.h"
#include "objetConnecte.h"
#include "observateur.h"

// Forward declarations
class Cellulaire;
class Personne;

/** \brief Classe représentant une Maison.
 * \authors Benjamin De Leener
 * Adrien Logut
 * Elliot Sisteron
 * \date 16/09/2015
 */
class Maison : public ObjetConnecte, public Observateur {
public:
    /** \brief Constructeur de Maison.
    * \param id L'identifiant de l'objet connecté
     * \param adresse La valeur à affecter à la variable adresse_.
     * \param position La valeur à affecter à la variable position_.
     */
    Maison(unsigned int id, std::string adresse = "inconnue", float position = 0.0);

    /** \brief Destructeur par défaut.
     */
    virtual ~Maison();

    /** \brief Accède à la variable adresse_.
     * \return La valeur de la variable adresse_.
     */
    std::string obtenirAdresse() const;

    /** \brief Modifie la variable adresse_.
     * \param adresse La nouvelle valeur à affecter à la variable adresse_.
     */
    void modifierAdresse(std::string adresse);

    /** \brief Accède à la variable position_.
     * \return La valeur de la variable position_.
     */
    float obtenirPosition() const;

    /** \brief Modifie la variable position_.
     * \param position La nouvelle valeur à affecter à la variable position_.
     */
    void modifierPosition(float position);

    /** \brief Ajoute un occupant à la maison.
     * Si il est impossible d'ajouter un occupant, il ne sera pas ajouté.
     * \param personne La personne à ajouter à la liste des personnes occupant la maison (personnes_).
     */
    void ajouterOccupant(Personne* personne);

    /** \brief Évalue si une personne est un occupant de la maison.
     * \param personne La personne à évaluer.
     * \return *true* si la personne occupe la maison, *false* sinon.
     */
    bool estOccupant(Personne* personne) const;

    /** \brief Évalue si la maison est vide.
     * \return *true* si la maison est vide *false* sinon.
     */
    bool estVide() const;

    /** \brief Trie et affiche la liste des occupants.
     */
    void afficherListeOccupants();

    /** \brief Opérateur d'ajout de personne.
     * Ajoute un occupant.
     * \return La maison avec l'occupant ajouté.
     */
    Maison& operator+=(Personne* personne);


    void mettreAJour(Observable* observable);



private:

    /** Affiche des tirets.
     * \param nbTirets Le nombre de tirets à afficher.
     */
    static void afficherTirets(int nbTirets = 80);

    /** \brief Trie la liste des occupants dans l'ordre alphabétique des noms (et des prénoms si les noms sont identiques).
     * Algorithme utilisé : BubbleSort.
     */
    void trierOccupants();

    std::string adresse_; //!< Adresse de la maison.

    float position_; //!< Position de la maison.

    std::vector<Personne*> personnes_; //!< Liste des occupants de la maison.

    int tempInterieure_; //!< Température intérieure souhaitée
    int tempExterieure_; //!< Température extérieure actuelle

    int nbCellulairesCo_; //!< int donnant le nombre de cellulaires connectés à la maison
};

#endif // MAISON_H