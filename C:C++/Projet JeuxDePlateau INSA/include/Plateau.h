#ifndef PLATEAU_H
#define PLATEAU_H

class Case;

/** \brief Classe représentant le plateau du jeu.
 */
class Plateau
{
    protected:
        int nbLignes; //!< Nombre de lignes du plateau.
        int nbColonnes; //!< Nombre de colonnes du plateau.
        Case*** plateau; //!< Aire rectangulaire de *pointeurs* sur Case, de taille nbLignes*nbColonnes.
    public:
        /** \brief Constructeur de Plateau.
         * \param pNbLignes La valeur à affecter à la variable nbLignes.
         * \param pNbColonnes La valeur à affecter à la variable nbColonnes.
         */
        Plateau(int pNbLignes, int pNbColonnes);

        /** \brief Destructeur par défaut.
         */
        virtual ~Plateau();

        /** \brief Accède à la variable nbLignes.
         * \return La valeur de la variable nbLignes.
         */
        int getNbLignes() const;

        /** \brief Accède à la variable nbColonnes.
         * \return La valeur de la variable nbColonnes.
         */
        int getNbColonnes() const;

        /** \brief Accède à une ligne de l'aire de jeu.
         *
         * Surdéfinition de l'opérateur [].
         * \return Une ligne de l'aire du jeu.
         */
        Case** operator[](int i);

        /** \brief Vérifie qu'une coordonnée soit incluse dans les bornes du plateau.
         * \param ligne La ligne de la coordonnée.
         * \param colonne La colonne de la coordonnée.
         * \return Un booléen valant true si la coordonnée est incluse dans les bornes du plateau, false sinon.
         */
		bool estValide(int ligne, int colonne) const;
};

#endif // PLATEAU_H
