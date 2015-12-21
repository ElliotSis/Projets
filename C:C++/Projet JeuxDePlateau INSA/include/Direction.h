#ifndef DIRECTION_H
#define DIRECTION_H

#include <iostream>

/** \brief Représente une direction pour un déplacement sur le plateau.
 */
typedef std::pair<int,int> Direction;

/** \brief Opérateur pour calculer la direction opposée d'une direction.
 * \param direction La direction dont on calcule l'opposé.
 * \return La direction opposée.
 */
Direction operator - (const Direction& direction);

#endif // DIRECTION_H
