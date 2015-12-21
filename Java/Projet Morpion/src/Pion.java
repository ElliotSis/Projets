
public enum Pion {
	
	/*
	 * �NUM�RATION DES OBJETS
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
	
	// Instancier les objets �num�r�s
	Pion(char p_pion) {
		this.pion = p_pion;
	}
	
	/*
	 * M�THODES D'INSTANCE
	 */
	
	// Dire si deux pions sont �gaux (M�thode polymorphe equals() de la classe Object)
	public boolean equals(Pion p_pion){
		return (this.pion == p_pion.pion);
	}
	
	/* Afficher le pion (M�thode polymorphe toString() de la classe Object), 
	cette m�thode fait aussi ici office d'accesseur */
	public String toString(){
		return Character.toString(this.pion);
	}
}
