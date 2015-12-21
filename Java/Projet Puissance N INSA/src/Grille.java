
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
		
	// Retourner le pion � l'emplacement d'un coup (par surcharge de m�thode)
	public Pion getPionAt(Coup coup){
		return this.m_tabPions[coup.getLigne()][coup.getColonne()];
	}
	
	// *** Mutateurs ***
	
	// Ajouter un pion � l'emplacement d'un coup (par surcharge de m�thode)
	public void setPionAt(Pion pion, Coup coup){		
		this.m_tabPions[coup.getLigne()][coup.getColonne()] = pion;
	}
	
	/*
	 * M�THODES D'INSTANCE
	 */
	
	// Initialiser la grille
	public void initialise(){
		for (int i = 0 ; i < this.m_lignes ; i++) {
			for (int j = 0 ; j < this.m_colonnes ; j++)
				this.m_tabPions[i][j] = Pion.Rien;
		}
	}
	
	// Trouver la ligne associ�e � la colonne jou�e
	public int trouveLigne(int colonne){
		int ligne = 0;
		
		// On v�rifie que la colonne soit bien d�finie
		if ((colonne < 0) || (colonne >= this.m_colonnes))
			return -1;
			
		// On v�rifie que la colonne soit libre
		for (int i = 0 ; i < this.m_lignes ; i++) {
			if (!(this.m_tabPions[i][colonne].equals(Pion.Rien)))
				ligne++;
		}
			
		if ((ligne < 0) || (ligne >= this.m_lignes))
			return -1;
			
		// Si les deux conditions sont v�rifi�es, alors la ligne calcul�e pr�cedemment est coh�rente
		return ligne;
	}
	
	// Dire si une colonne est valide
	public boolean estColonneValide(int colonne){
		return (this.trouveLigne(colonne) != -1);
	}
	
	// Trouver les coups possibles sur la grille
	public Coup[] trouveCoupsPossibles() {
		int taille = 0;
		// Cr�ation d'un tableau de taille du nombre maximal de coups possibles que l'on puisse trouver
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
					 // On sort de la boucle car les autres coups sont interdit (les pions tombent 1 � 1)
					 break;
				 }
			}
		}
			
		/* Si la taille trouv�e est �gale au nombre maximal de coups possibles que l'on puisse trouver,
		alors on renvoi le tableau */
		if (taille == this.m_colonnes)
			return tmp;
			
		/* Sinon, des �l�ments sont inutiles dans le tableau tmp, on lui retranche donc 
		ces �l�ments dans un nouveau tableau */
		Coup[] resultat = new Coup[taille];
		
		for (int i = 0 ; i < taille ; i++) {
			resultat[i] = tmp[i];
		}
			
		return resultat;
	}
	
	// Trouver les coups jou�s sur la grille
	public Coup[] trouveCoupsJoues() {
		int taille = 0;
		// Cr�ation d'un tableau de taille du nombre maximal de coups jou�s que l'on puisse trouver
		Coup[] tmp = new Coup[this.m_lignes * this.m_colonnes];

		// Pour chaque ligne
		for(int i = 0 ; i < this.m_lignes ; i++) {
			// Pour chaque colonne
			for(int j = 0 ; j < this.m_colonnes ; j++) {
				// Si l'emplacement n'est pas disponible
				 if(!(this.m_tabPions[i][j].equals(Pion.Rien))) {
					 // On a alors un coup jou� � cet emplacement
					 tmp[taille] = new Coup(i, j);
					 taille++;
				 }
			}
		}
			
		/* Si la taille trouv�e est �gale au nombre maximal de coups jou�s que l'on puisse trouver,
		alors on renvoi le tableau */
		if (taille == this.m_lignes * this.m_colonnes)
			return tmp;
			
		/* Sinon, des �l�ments sont inutiles dans le tableau tmp, on lui retranche donc 
		ces �l�ments dans un nouveau tableau */
		Coup[] resultat = new Coup[taille];
		
		for (int i = 0 ; i < taille ; i++) {
			resultat[i] = tmp[i];
		}
			
		return resultat;
	}
	
	// Trouver le nombre de coups jou� sur la grille
	public int trouveNombreCoupsJoue() {
		return this.trouveCoupsJoues().length;
	}
	
	// Dire si la grille est pleine
	public boolean estPleine(){
		// On parcoure le tableau � la recherche d'une case vide
		for (int i = this.m_lignes - 1 ; i >= 0 ; i--) { // Ici, on d�croit pour limiter les calculs
			for (int j = 0 ; j < this.m_colonnes ; j++) {
				if (this.m_tabPions[i][j].equals(Pion.Rien))
						return false;
			}
		}
		
		// Si aucune case n'est vide, alors la grille est pleine
		return true;
	}
	
	// Trouver le nombre de pion align�s horizontalement � partir d'un coup sur la grille
	public int nbPionsAlignesHoriz(Pion pion, Coup coup) {
		return this.nbPionsAlignes(pion, coup.getLigne(), 0, 0, 1);
	}
	
	// Trouver le nombre de pion align�s verticalement � partir d'un coup sur la grille
	public int nbPionsAlignesVert(Pion pion, Coup coup) {
		return this.nbPionsAlignes(pion, 0, coup.getColonne(), 1, 0);
	}
	
	/* Trouver le nombre de pion align�s selon la diagonale de gauche � droite � partir 
	d'un coup sur la grille */
	public int nbPionsAlignesDiagGD(Pion pion, Coup coup) {
		// Si on est au dessus ou sur la droite L = C 
		if (coup.getLigne() - coup.getColonne() >= 0)
			return this.nbPionsAlignes(pion, (coup.getLigne() - coup.getColonne()), 0, 1, 1);
		// Si on est en dessous
		else
			return this.nbPionsAlignes(pion, 0, (coup.getColonne() - coup.getLigne()), 1, 1);
	}

	/* Trouver le nombre de pion align�s selon la diagonale de droite � gauche � partir 
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
	
	/* Donner le nombre maximum de pions align�s en suivant un d�placement dL 
	(d�placement suivant les lignes) et dC (d�placement suivant les colonnes) 
	� partir d'une position de r�f�rence */
	private int nbPionsAlignes(Pion pion, int lOrigine, int cOrigine, int dL, int dC) {
		int nbAlignes = 0, compteur = 0;
		boolean vertical = ((dL != 0) && (dC == 0));

		/* Si le pion test� est le pion vide, on retourne -1, ce cas ne nous interresse pas
		Et, on renvoyant un nombre n�gatif, on saura que le pion pass� en param�tre est invalide */
		if (pion.equals(Pion.Rien))
			return -1;
		
		/* On parcoure la grille de la position d'origine en suivant ces d�placements 
		et en faisant attention � ne pas d�passer les limites de la grille */
		for(int lCourante = lOrigine, cCourante = cOrigine ; 
				((lCourante >= 0) && (lCourante < this.m_lignes)) 
				&& ((cCourante >= 0) && (cCourante < this.m_colonnes)) ; 
				lCourante += dL, cCourante += dC) {
			
			// Si le pion test� n'est pas �gal au pion courant, le compteur retombe � 0
			if (!(this.m_tabPions[lCourante][cCourante].equals(pion))) {
				compteur = 0;
				
				/* Pour am�liorer la complexit�, �tude du cas particulier o� on se d�place
				de mani�re verticale positive : si on tombe sur une case vide lors du d�placement alors
				on peut arr�ter la boucle (un pion ne peut pas �tre au dessus d'une case vide) */
				if (vertical && this.m_tabPions[lCourante][cCourante].equals(Pion.Rien))
					break;
			}
			// Sinon on incr�mente le compteur
			else {
				compteur++;
			
				/* Pour renvoyer le maximum atteint par le compteur, on assigne la valeur du compteur
				� nAlignes uniquement lorsque celui ci est sup�rieur au nombre d�j� atteint */
				if (compteur > nbAlignes)
					nbAlignes = compteur;
			}
		}
		
		return nbAlignes;
	}
	
	// Afficher la grille (M�thode polymorphe toString() de la classe Object)
	public String toString(){
		String resultat = "";
		
		// Ajout des num�ros de colonnes
		for (int i = 1 ; i <= this.m_colonnes ; i++){
				resultat += " " + i;
		}
			
		// Ajout d'un retour � la ligne
		resultat += "\n";
			
		// Affigage ligne par ligne
		for (int i = this.m_lignes - 1 ; i >= 0 ; i--) { // On d�croit de (nombre de lignes - 1) � 0		
			
			// Affichage colonne par colonne
			for (int j = 0 ; j < this.m_colonnes ; j++) // On croit de 0 � (nombre de colonnes - 1)
				
				// On affiche les pions par lignes d�croissantes et colonnes croissantes
				resultat += "|" + this.m_tabPions[i][j].toString(); 
			
			// Ajout du s�parateur extr�me droit et d'un retour � la ligne � chaque fin de ligne
			resultat += "|\n"; 
		}
			
		// Ajout d'un tiret (par soucis d'esth�tisme)
		resultat += "-";
			
		// S�paration de la grille par des tirets
		for (int j = 0 ; j < this.m_colonnes ; j++)
			resultat += "--";
			
		return resultat;
	}
}
