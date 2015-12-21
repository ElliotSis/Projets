#ifndef VUEJEU_H
#define VUEJEU_H

class Controlleur;
class Coup;
class Jeu;
class Piece;

/** \brief Classe utilisée dans le cadre du patron de conception MVC.
 *
 * La vue est le "V" de MVC.
 * Elle sert à afficher et récupérer différentes informations utilisées dans le jeu.
 */
class VueJeu
{
    protected:
        Jeu* jeu; //!< Le jeu joué.
        Controlleur* controlleur; //!< Le controlleur chargé de traiter les informations que la vue lui envoie.
    public:
        /** \brief Constructeur de Vue.
         * \param pJeu La valeur à affecter à la variable jeu.
         * \param pControlleur La valeur à affecter à la variable controlleur.
         */
        VueJeu(Jeu* pJeu, Controlleur* pControlleur);

        /** \brief Detructeur par défaut.
         */
        virtual ~VueJeu();

        /** \brief Affiche le jeu.
         */
        virtual void afficherJeu() = 0;

        /** \brief Affiche le match nul.
         */
        virtual void afficherMatchNul() = 0;

        /** \brief Affiche le joueur devant jouer.
         */
        virtual void afficherJoueurDevantJouer() = 0;

        /** \brief Affiche le gagnant.
         */
        virtual void afficherGagnant() = 0;
};

#endif // VUEJEU_H
