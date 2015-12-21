
public class Dewey implements ComportementJoueur {
	
	/*
	 * REDÉFINITION DES MÉTHODES ABSTRAITES
	 */
	
	// Trouver le coup à jouer
	public Coup trouveCoup(Grille grille, int nAlignes) {
		return IA.trouveMeilleurCoup(grille, nAlignes, 4);
	}
}
