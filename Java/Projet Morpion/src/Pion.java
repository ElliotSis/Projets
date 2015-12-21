
public enum Pion {
	
	/*
	 * ÉNUMÉRATION DES OBJETS
	 */
	
	Croix ('X'),
	Rond ('O'),
	Rien (' ');
	
	/*
	 * VARIABLES D'INSTANCE
	 */
	
	private char pion;
	
	/*
	 * CONSTRUCTEURS
	 */
	
	// Instancier les objets énumérés
	Pion(char p_pion) {
		this.pion = p_pion;
	}
	
	/*
	 * MÉTHODES D'INSTANCE
	 */
	
	// Dire si deux pions sont égaux (Méthode polymorphe equals() de la classe Object)
	public boolean equals(Pion p_pion){
		return (this.pion == p_pion.pion);
	}
	
	/* Afficher le pion (Méthode polymorphe toString() de la classe Object), 
	cette méthode fait aussi ici office d'accesseur */
	public String toString(){
		return Character.toString(this.pion);
	}
}
