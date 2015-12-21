
public class Malcolm implements ComportementJoueur {
	
	/*
	 * REDÉFINITION DES MÉTHODES ABSTRAITES
	 */
	
	// Trouver le coup à jouer
	public Coup trouveCoup(Grille grille, int nAlignes) {
		return IA.trouveMeilleurCoup(grille, nAlignes, 6);
	}
}
