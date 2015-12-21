#ifndef COULEURS_H
#define COULEURS_H

const int BLANC = 16777215; //!< Entier représentant la couleur blanche.
const int NOIR = 0; //!< Entier représentant la couleur noire.
const int BEIGE_CLAIR = 14597508; //!< Entier représentant la couleur beige clair.
const int BEIGE_FONCE = 12424282; //!< Entier représentant la couleur beige foncé.
const int VERT_FONCE = 3175228; //!< Entier représentant la couleur vert foncé.

/** \brief Calcule la couleur au format RGB double d'une couleur au format entier.
 * \param La couleur au format entier dont on souhaite obtenir le format RGB double.
 * \param r La variable stockant le rouge.
 * \param g La variable stockant le vert.
 * \param b La variable stockant le bleu.
 */
void intToRGB(int couleur, double& r, double& g, double& b);

#endif // COULEURS_H
