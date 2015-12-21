#ifndef ARTIFICIEL_H
#define ARTIFICIEL_H

#include "Joueur.h"

/** \brief Classe représentant un joueur artificiel.
 */
class Artificiel : public Joueur
{
    private:
        int profondeur; //!< Profondeur de l'arbre de recherche du min-max.

        /** \brief Algorithme alpha-beta.
         *
         * Optimisation de l'algorithme min-max destiné à évaluer le meilleur coup jouable par le joueur artificiel.
		 * \return Un entier nécessaire au bon fonctionnement de l'algorithme.
         */
        double alphaBeta(double alpha, double beta);

        /** \brief Calcule le meilleur coup possible en prévoyant *profondeur* coups à l'avance.
         *
         * Il s'agit du meilleur coup jouable au sens de l'heuristique d'évaluation, en utilisant l'algorithme alpha-beta.
         * \return Le meilleur coup possible (au sens de l'heuristique d'évaluation) pour la profondeur de l'instance.
         */
        Coup* meilleurCoupPossible();

    protected:
        /** \brief Évalue l'état du jeu joué.
		 * \return Un réel représentant l'évaluation de l'état du jeu joué.
         */
        virtual double evaluation() = 0;

    public:
        /** \brief Constructeur de Artificiel.
         * \param pCouleurDeSesPieces La valeur à affecter à la variable couleurDeSesPieces.
         * \param pJeu La valeur à affecter à la variable jeu.
         * \param pProfondeur La valeur à affecter à la variable profondeur.
         */
        Artificiel(int pCouleurDeSesPieces, Jeu* pJeu, int pProfondeur);

        /** \brief Destructeur par défaut.
         */
        virtual ~Artificiel();

        bool estArtificiel() const;

        void jouer();
};

#endif // ARTIFICIEL_H
