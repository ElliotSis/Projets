#ifndef CONTROLLEUR_H
#define CONTROLLEUR_H

class Case;
class Jeu;
class VuePrincipale;
class VueJeu;
class Piece;

/** \brief Classe utilisée dans le cadre du patron de conception MVC.
 *
 * Le controlleur est le "C" de MVC.
 * Il sert à instancier la vue et le jeu.
 * Il traite les informations reçues par la vue, puis les envoie au jeu et à la vue pour qu'ils se mettent à jour.
 */
class Controlleur
{
    protected:
        Jeu* jeu; //!< Le jeu que le controlleur arbitre.
        VueJeu* vueJeu; //!< La vue du jeu.
        VuePrincipale* vue; //!< La vue principale.
        Piece* pieceADeplacer; //!< Variable temporaire servant à se souvenir du premier choix de l'utilisateur lorsqu'il joue un coup : la pièce à déplacer.

        /** \brief Traite le choix du menu principal.
         *
         * Cette fonction sert à instancier la vue une fois que l'utilisateur a choisi le jeu auquel il souhaite jouer.
         * \param choix Un entier représentant le jeu joué (1 : jeu de dames, 2 : jeu d'othello, 3 : jeu du Puissance 4).
         */
        virtual void traiterChoixMenuPrincipalVue(int choix) = 0;

        /** \brief Fait jouer le joueur ayant le trait et rend la main à l'adversaire.
         */
        void fairePasserAuTourSuivant();

    public:
        /** \brief Constructeur par défaut.
         */
        Controlleur();

        /** \brief Destructeur par défaut.
         */
        virtual ~Controlleur();

        /** \brief Accède à la variable vueJeu.
         * \return La valeur de la variable vueJeu.
         */
        VueJeu* getVueJeu() const;

        /** \brief Traite le choix du menu principal.
         *
         * Cette fonction sert à instancier et lancer le jeu une fois que l'utilisateur l'a choisi.
         * \param choix Un entier représentant le jeu joué (1 : jeu de dames, 2 : jeu d'othello, 3 : jeu du Puissance 4).
         * \param choixJ1 Un entier représentant le joueur choisi pour commencer la partie (0 : joueur humain, 1-15 : un joueur artificiel avec une profondeur de recherche choixJ1).
         * \param choixJ2 Un entier représentant le joueur choisi comme adversaire au joueur 1 (0 : joueur humain, 1-15 : un joueur artificiel avec une profondeur de recherche choixJ2).
         */
        void traiterChoixMenuPrincipal(int choixJeu, int choixJ1, int choixJ2);

        /** \brief Traite un coup rentré par l'utilisateur.
         *
         * Si il y a une pièce sur la case choisie et que celle-ci est jouable, la variable temporaire pièce à déplacer est modifiée.
         * Si la pièce à déplacer est déjà définie et que la case d'arrivée est valide : le coup est joué.
         * \param caseChoisie un *pointeur* sur la case que l'utilisateur a selectionné.
         * \return Un booléen valant true si le coup est joué, false sinon.
         */
        bool traiterCaseChoisie(Case* caseChoisie);

        /** \brief Lance une partie du jeu.
         */
        void jouer();

        /** \brief Lance le programme.
         */
        virtual void lancer() = 0;
};

#endif // CONTROLLEUR_H
