
public class Coup {
	
	/*
	 * VARIABLES D'INSTANCE
	 */
	
	private int m_colonne;
	private int m_ligne;
	
	/*
	 * CONSTRUCTEURS
	 */
	
	// Instancier le coup
	public Coup(int ligne, int colonne) {
		this.m_ligne = ligne;
		this.m_colonne = colonne;
	}
	
	/*
	 * ACCESSEURS ET MUTATEURS
	 */
	
	// *** Accesseurs ***
	
	// Retourner la ligne
	public int getLigne(){
		return this.m_ligne;
	}
	
	// Retourner la colonne
	public int getColonne(){
		return this.m_colonne;
	}
	

	/*
	 * MÉTHODES D'INSTANCE
	 */
	
	// Simuler le coup d'un pion sur la grille
	public void simuler(Pion pion, Grille grille) {
		grille.setPionAt(pion, this);
	}
		
	// Annuler le coup d'un pion sur la grille
	public void annuler(Grille grille) {
		grille.setPionAt(Pion.Rien, this);
	}
	
	// Dire si le coup est gagnant
	public boolean estGagnant(Pion pion, Grille grille, int nAlignes) {
		// Étude de l'horizontale
		boolean resultat = (grille.nbPionsAlignesHoriz(pion, this) >= nAlignes);

		// Étude de la verticale, inutile de l'étudier quand la ligne est inférieure à nAlignes
		if (this.m_ligne >= (nAlignes - 1))
			resultat = (resultat || (grille.nbPionsAlignesVert(pion, this) >= nAlignes));
		
		/* Étude des cas particuliers pour améliorer la complexité de l'algorithme
		Ici, on s'intéresse aux coins du plateau : on a une diagonale en moins à vérifier 
		à chaque fois */
		
		/* Si on se trouve dans le coin inférieur gauche ou dans le coin supérieur droit, 
		 il est inutile de regarder les diagonales de droite à gauche */
		
		/* Inférieur gauche  : On est en dessous de la droite d'équation 
		L = -C + (nAlignes - 1) */
		if (((this.m_ligne + this.m_colonne) - (nAlignes - 1) < 0) 
				/* Supérieur droit  : On est au dessus de la droite d'équation 
				L = -C + (nombre de lignes - 1) + (nombre de colonnes - 1) - (nAlignes - 1) */
				|| ((this.m_ligne + this.m_colonne) - 
						(grille.getLignes() - 1) - (grille.getColonnes() - 1) + (nAlignes - 1) > 0))
			return (resultat || (grille.nbPionsAlignesDiagGD(pion, this) >= nAlignes));
		
		/* Si on se trouve dans le coin inférieur droit ou dans le coin supérieur gauche, 
		 il est inutile de regarder les diagonales de gauche à droite */
		
		/* Inférieur droit  : On est en dessous de la droite d'équation 
		L = C + (nAlignes - 1) - (nombre de colonnes - 1) */
		if (((this.m_ligne - this.m_colonne) - 
				(nAlignes - 1) + (grille.getColonnes() - 1) < 0)
				/* Supérieur gauche  : On est au dessus de la droite d'équation 
				L = C + (nombre de lignes - 1) - (nAlignes - 1) */
				|| ((this.m_ligne - this.m_colonne) - 
						(grille.getLignes() - 1)  + (nAlignes - 1) > 0))
			return (resultat || (grille.nbPionsAlignesDiagDG(pion, this) >= nAlignes));
		
		// Cas général
		return (resultat 
				|| (grille.nbPionsAlignesDiagGD(pion, this) >= nAlignes) 
				|| (grille.nbPionsAlignesDiagDG(pion, this) >= nAlignes));
	}
	
	// Afficher le coup joué par le joueur (Méthode polymorphe toString() de la classe Object)
	public String toString(){
		return String.valueOf(this.m_colonne + 1);
	}
}
