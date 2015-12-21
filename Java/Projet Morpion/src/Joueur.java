
public abstract class Joueur {
	
	/*
	 * VARIABLES D'INSTANCE
	 */
	
	protected String nom;
	protected Pion pion;
	
	/*
	 * CONSTRUCTEURS
	 */
	
	// Instancier un joueur avec des paramètres
	public Joueur(String p_nom, Pion p_pion) {
		nom = p_nom;
		pion = p_pion;
	}
	
	/*
	 * GETTERS & SETTERS
	 */
	
	// Getter nom
	public String getNom() {
		return nom;
	}
	
	// Setter nom
	public void setNom(String nom) {
		this.nom = nom;
	}
	
	// Getter pion
	public Pion getPion() {
		return pion;
	}
	
	// Setter pion
	public void setPion(Pion pion) {
		this.pion = pion;
	}
	
	public abstract void jouer(Plateau p);
	

}
