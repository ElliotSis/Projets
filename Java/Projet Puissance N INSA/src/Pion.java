
public enum Pion {
	
	/*
	 * ÉNUMÉRATION DES OBJETS
	 */
	
	Croix ("X"),
	Rond ("O"),
	Rien (" ");
	
	/*
	 * VARIABLES D'INSTANCE
	 */
	
	private String m_pion;
	
	/*
	 * CONSTRUCTEURS
	 */
	
	// Instancier les objets énumérés
	Pion(String pion) {
		this.m_pion = pion;
	}
	
	/*
	 * MÉTHODES D'INSTANCE
	 */
	
	// Dire si deux pions sont égaux (Méthode polymorphe equals() de la classe Object)
	public boolean equals(Pion pion){
		return this.m_pion.equals(pion.toString());
	}
	
	/* Afficher le pion (Méthode polymorphe toString() de la classe Object), 
	cette méthode fait aussi ici office d'accesseur */
	public String toString(){
		return this.m_pion;
	}
}
