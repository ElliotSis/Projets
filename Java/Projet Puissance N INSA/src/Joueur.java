
public class Joueur {
	
	/*
	 * VARIABLES D'INSTANCE
	 */
	
	private ComportementJoueur m_comportement;
	private String m_nom;
	private Pion m_pion;
	
	/*
	 * VARIABLES DE CLASSE
	 */
	
	// Sert à l'assignation automatique d'un pion au joueur
	private static int autoPion = 0;
	
	/*
	 * CONSTRUCTEURS
	 */
	
	// Instancier un joueur humain
	public Joueur(String nom){
		this.m_comportement = new Humain();
		this.m_nom = nom;
		
		// Assignation automatique du pion
		this.m_pion = (autoPion == 0) ? Pion.Croix : Pion.Rond;
		autoPion++;
		autoPion %= 2;
	}
	
	// Instancier une IA
	public Joueur(int difficulte) { 
		// Assignation de l'IA selon la difficulté
		switch (difficulte){
		case 1 : 
			this.m_comportement = new Reese();
			this.m_nom = "Reese";
			break;
		case 2 : 
			this.m_comportement = new Dewey();
			this.m_nom = "Dewey";
			break;
		case 3 : 
			this.m_comportement = new Malcolm();
			this.m_nom = "Malcolm";
			break;
		default :
		}
		
		// Assignation automatique du pion
		this.m_pion = (autoPion == 0) ? Pion.Croix : Pion.Rond;
		autoPion++;
		autoPion %= 2;
	}
	
	/*
	 * ACCESSEURS ET MUTATEURS
	 */
	
	// *** Accesseurs ***
	
	// Retourner le comportement
	public ComportementJoueur getComportement(){
		return this.m_comportement;
	}
	
	// Retourner le pion
	public Pion getPion(){
		return this.m_pion;
	}
	
	/*
	 * MÉTHODES D'INSTANCE
	 */
	
	// Jouer le coup
	public void joue(Grille grille, Coup coup) {
		grille.setPionAt(this.m_pion, coup);
	}
	
	/* Afficher le joueur (Méthode polymorphe toString() de la classe Object), 
	cette méthode fait aussi ici office d'accesseur sur la variable m_nom */
	public String toString(){
		return this.m_nom;
	}
}
