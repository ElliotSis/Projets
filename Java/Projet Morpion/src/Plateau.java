
public class Plateau {
	
	/*
	 * VARIABLES D'INSTANCE
	 */
	
	protected int hauteur;
	protected int longueur;
	protected Pion[][] tabPion;
	
	
	/*
	 * CONSTRUCTEURS
	 */
	
	// Instancier un plateau avec des paramètres
	public Plateau(int p_hauteur, int p_longueur) {
		this.hauteur = p_hauteur;
		this.longueur = p_longueur;
		this.tabPion = new Pion[p_hauteur][p_longueur];
		this.initialiserPlateau();
	}
	
	/*
	 * GETTERS & SETTERS
	 */
	
	// Getter hauteur
	public int getHauteur() {
		return hauteur;
	}

	// Setter hauteur
	public void setHauteur(int hauteur) {
		this.hauteur = hauteur;
	}

	// Getter longueur
	public int getLongueur() {
		return longueur;
	}

	// Setter longueur
	public void setLongueur(int longueur) {
		this.longueur = longueur;
	}

	// Getter pion à la position
	public Pion getTabPionPos(int i, int j) {
		return tabPion[i][j];
	}

	// Setter pion à la position
	public void setTabPionPos(int i, int j, Pion pion) {
		this.tabPion[i][j] = pion;
	}
	
	
	/*
	 * MÉTHODES D'INSTANCE
	 */
	
	// Initialiser le plateau
	public void initialiserPlateau(){
		for(int i = 0 ; i < this.hauteur ; i++) {
			for(int j = 0 ; j < this.longueur ; j++) {
				this.tabPion[i][j] = Pion.Rien;
			}
		}
	}
	
}
