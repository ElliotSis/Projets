
public enum Pion {
	
	/*
	 * �NUM�RATION DES OBJETS
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
	
	// Instancier les objets �num�r�s
	Pion(String pion) {
		this.m_pion = pion;
	}
	
	/*
	 * M�THODES D'INSTANCE
	 */
	
	// Dire si deux pions sont �gaux (M�thode polymorphe equals() de la classe Object)
	public boolean equals(Pion pion){
		return this.m_pion.equals(pion.toString());
	}
	
	/* Afficher le pion (M�thode polymorphe toString() de la classe Object), 
	cette m�thode fait aussi ici office d'accesseur */
	public String toString(){
		return this.m_pion;
	}
}
