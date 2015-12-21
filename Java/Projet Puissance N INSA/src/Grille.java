
public class Grille {
	
	/*
	 * VARIABLES D'INSTANCE
	 */
	
	private int m_lignes;
	private int m_colonnes;
	private Pion[][] m_tabPions;
	
	/*
	 * CONSTRUCTEURS
	 */
	
	// Instancier la grille
	public Grille(int lignes, int colonnes) {	
		this.m_lignes = lignes;
		this.m_colonnes = colonnes;
		this.m_tabPions = new Pion[lignes][colonnes];
		this.initialise();
	}
	
	/*
	 * ACCESSEURS ET MUTATEURS
	 */
	
	// *** Accesseurs ***
	
	// Retourner le nombre de lignes
	public int getLignes(){
		return this.m_lignes;
	}
		
	// Retourner le nombre de colonnes
	public int getColonnes(){
		return this.m_colonnes;
	}
		
	// Retourner le pion à l'emplacement d'un coup (par surcharge de méthode)
	public Pion getPionAt(Coup coup){
		return this.m_tabPions[coup.getLigne()][coup.getColonne()];
	}
	
	// *** Mutateurs ***
	
	// Ajouter un pion à l'emplacement d'un coup (par surcharge de méthode)
	public void setPionAt(Pion pion, Coup coup){		
		this.m_tabPions[coup.getLigne()][coup.getColonne()] = pion;
	}
	
	/*
	 * MÉTHODES D'INSTANCE
	 */
	
	// Initialiser la grille
	public void initialise(){
		for (int i = 0 ; i < this.m_lignes ; i++) {
			for (int j = 0 ; j < this.m_colonnes ; j++)
				this.m_tabPions[i][j] = Pion.Rien;
		}
	}
	
	// Trouver la ligne associée à la colonne jouée
	public int trouveLigne(int colonne){
		int ligne = 0;
		
		// On vérifie que la colonne soit bien définie
		if ((colonne < 0) || (colonne >= this.m_colonnes))
			return -1;
			
		// On vérifie que la colonne soit libre
		for (int i = 0 ; i < this.m_lignes ; i++) {
			if (!(this.m_tabPions[i][colonne].equals(Pion.Rien)))
				ligne++;
		}
			
		if ((ligne < 0) || (ligne >= this.m_lignes))
			return -1;
			
		// Si les deux conditions sont vérifiées, alors la ligne calculée précedemment est cohérente
		return ligne;
	}
	
	// Dire si une colonne est valide
	public boolean estColonneValide(int colonne){
		return (this.trouveLigne(colonne) != -1);
	}
	
	// Trouver les coups possibles sur la grille
	public Coup[] trouveCoupsPossibles() {
		int taille = 0;
		// Création d'un tableau de taille du nombre maximal de coups possibles que l'on puisse trouver
		Coup[] tmp = new Coup[this.m_colonnes];

		// Pour chaque colonne
		for(int i = 0 ; i < this.m_colonnes ; i++) {
			// Pour chaque ligne
			for(int j = 0 ; j < this.m_lignes ; j++) {
				// Si l'emplacement est disponible
				 if(this.m_tabPions[j][i].equals(Pion.Rien)) {
					 // On peut alors jouer sur cet emplacement
					 tmp[taille] = new Coup(j, i);
					 taille++;
					 // On sort de la boucle car les autres coups sont interdit (les pions tombent 1 à 1)
					 break;
				 }
			}
		}
			
		/* Si la taille trouvée est égale au nombre maximal de coups possibles que l'on puisse trouver,
		alors on renvoi le tableau */
		if (taille == this.m_colonnes)
			return tmp;
			
		/* Sinon, des éléments sont inutiles dans le tableau tmp, on lui retranche donc 
		ces éléments dans un nouveau tableau */
		Coup[] resultat = new Coup[taille];
		
		for (int i = 0 ; i < taille ; i++) {
			resultat[i] = tmp[i];
		}
			
		return resultat;
	}
	
	// Trouver les coups joués sur la grille
	public Coup[] trouveCoupsJoues() {
		int taille = 0;
		// Création d'un tableau de taille du nombre maximal de coups joués que l'on puisse trouver
		Coup[] tmp = new Coup[this.m_lignes * this.m_colonnes];

		// Pour chaque ligne
		for(int i = 0 ; i < this.m_lignes ; i++) {
			// Pour chaque colonne
			for(int j = 0 ; j < this.m_colonnes ; j++) {
				// Si l'emplacement n'est pas disponible
				 if(!(this.m_tabPions[i][j].equals(Pion.Rien))) {
					 // On a alors un coup joué à cet emplacement
					 tmp[taille] = new Coup(i, j);
					 taille++;
				 }
			}
		}
			
		/* Si la taille trouvée est égale au nombre maximal de coups joués que l'on puisse trouver,
		alors on renvoi le tableau */
		if (taille == this.m_lignes * this.m_colonnes)
			return tmp;
			
		/* Sinon, des éléments sont inutiles dans le tableau tmp, on lui retranche donc 
		ces éléments dans un nouveau tableau */
		Coup[] resultat = new Coup[taille];
		
		for (int i = 0 ; i < taille ; i++) {
			resultat[i] = tmp[i];
		}
			
		return resultat;
	}
	
	// Trouver le nombre de coups joué sur la grille
	public int trouveNombreCoupsJoue() {
		return this.trouveCoupsJoues().length;
	}
	
	// Dire si la grille est pleine
	public boolean estPleine(){
		// On parcoure le tableau à la recherche d'une case vide
		for (int i = this.m_lignes - 1 ; i >= 0 ; i--) { // Ici, on décroit pour limiter les calculs
			for (int j = 0 ; j < this.m_colonnes ; j++) {
				if (this.m_tabPions[i][j].equals(Pion.Rien))
						return false;
			}
		}
		
		// Si aucune case n'est vide, alors la grille est pleine
		return true;
	}
	
	// Trouver le nombre de pion alignés horizontalement à partir d'un coup sur la grille
	public int nbPionsAlignesHoriz(Pion pion, Coup coup) {
		return this.nbPionsAlignes(pion, coup.getLigne(), 0, 0, 1);
	}
	
	// Trouver le nombre de pion alignés verticalement à partir d'un coup sur la grille
	public int nbPionsAlignesVert(Pion pion, Coup coup) {
		return this.nbPionsAlignes(pion, 0, coup.getColonne(), 1, 0);
	}
	
	/* Trouver le nombre de pion alignés selon la diagonale de gauche à droite à partir 
	d'un coup sur la grille */
	public int nbPionsAlignesDiagGD(Pion pion, Coup coup) {
		// Si on est au dessus ou sur la droite L = C 
		if (coup.getLigne() - coup.getColonne() >= 0)
			return this.nbPionsAlignes(pion, (coup.getLigne() - coup.getColonne()), 0, 1, 1);
		// Si on est en dessous
		else
			return this.nbPionsAlignes(pion, 0, (coup.getColonne() - coup.getLigne()), 1, 1);
	}

	/* Trouver le nombre de pion alignés selon la diagonale de droite à gauche à partir 
	d'un coup sur la grille */
	public int nbPionsAlignesDiagDG(Pion pion, Coup coup) {
		// Si on est au dessus ou sur la droite L = -C + (nombre de colonnes - 1) 
		if ((coup.getLigne() + coup.getColonne()) - (this.m_colonnes - 1) >= 0)
			return this.nbPionsAlignes(pion, (coup.getLigne() + coup.getColonne()) - (this.m_colonnes - 1), 
					(this.m_colonnes - 1), 1, -1);
		// Si on est en dessous
		else
			return this.nbPionsAlignes(pion, 0, (coup.getLigne() + coup.getColonne()), 1, -1);
	}
	
	/* Donner le nombre maximum de pions alignés en suivant un déplacement dL 
	(déplacement suivant les lignes) et dC (déplacement suivant les colonnes) 
	à partir d'une position de référence */
	private int nbPionsAlignes(Pion pion, int lOrigine, int cOrigine, int dL, int dC) {
		int nbAlignes = 0, compteur = 0;
		boolean vertical = ((dL != 0) && (dC == 0));

		/* Si le pion testé est le pion vide, on retourne -1, ce cas ne nous interresse pas
		Et, on renvoyant un nombre négatif, on saura que le pion passé en paramètre est invalide */
		if (pion.equals(Pion.Rien))
			return -1;
		
		/* On parcoure la grille de la position d'origine en suivant ces déplacements 
		et en faisant attention à ne pas dépasser les limites de la grille */
		for(int lCourante = lOrigine, cCourante = cOrigine ; 
				((lCourante >= 0) && (lCourante < this.m_lignes)) 
				&& ((cCourante >= 0) && (cCourante < this.m_colonnes)) ; 
				lCourante += dL, cCourante += dC) {
			
			// Si le pion testé n'est pas égal au pion courant, le compteur retombe à 0
			if (!(this.m_tabPions[lCourante][cCourante].equals(pion))) {
				compteur = 0;
				
				/* Pour améliorer la complexité, étude du cas particulier où on se déplace
				de manière verticale positive : si on tombe sur une case vide lors du déplacement alors
				on peut arrêter la boucle (un pion ne peut pas être au dessus d'une case vide) */
				if (vertical && this.m_tabPions[lCourante][cCourante].equals(Pion.Rien))
					break;
			}
			// Sinon on incrémente le compteur
			else {
				compteur++;
			
				/* Pour renvoyer le maximum atteint par le compteur, on assigne la valeur du compteur
				à nAlignes uniquement lorsque celui ci est supérieur au nombre déjà atteint */
				if (compteur > nbAlignes)
					nbAlignes = compteur;
			}
		}
		
		return nbAlignes;
	}
	
	// Afficher la grille (Méthode polymorphe toString() de la classe Object)
	public String toString(){
		String resultat = "";
		
		// Ajout des numéros de colonnes
		for (int i = 1 ; i <= this.m_colonnes ; i++){
				resultat += " " + i;
		}
			
		// Ajout d'un retour à la ligne
		resultat += "\n";
			
		// Affigage ligne par ligne
		for (int i = this.m_lignes - 1 ; i >= 0 ; i--) { // On décroit de (nombre de lignes - 1) à 0		
			
			// Affichage colonne par colonne
			for (int j = 0 ; j < this.m_colonnes ; j++) // On croit de 0 à (nombre de colonnes - 1)
				
				// On affiche les pions par lignes décroissantes et colonnes croissantes
				resultat += "|" + this.m_tabPions[i][j].toString(); 
			
			// Ajout du séparateur extrême droit et d'un retour à la ligne à chaque fin de ligne
			resultat += "|\n"; 
		}
			
		// Ajout d'un tiret (par soucis d'esthétisme)
		resultat += "-";
			
		// Séparation de la grille par des tirets
		for (int j = 0 ; j < this.m_colonnes ; j++)
			resultat += "--";
			
		return resultat;
	}
}
