
public class Dewey implements ComportementJoueur {
	
	/*
	 * RED�FINITION DES M�THODES ABSTRAITES
	 */
	
	// Trouver le coup � jouer
	public Coup trouveCoup(Grille grille, int nAlignes) {
		return IA.trouveMeilleurCoup(grille, nAlignes, 4);
	}
}
