
public class Reese implements ComportementJoueur {
	
	/*
	 * REDÉFINITION DES MÉTHODES ABSTRAITES
	 */
	
	// Trouver le coup à jouer
	public Coup trouveCoup(Grille grille, int nAlignes) {
		// Une fois sur deux on joue avec une IA relativement simple à battre
		if (((int)((Math.random()*2) % 2)) == 0)
			return IA.trouveMeilleurCoup(grille, nAlignes, 2);
		// Une fois sur deux on joue au hasard
		else {
			int ligne = -1, colonne = 0;
		
			do {
				// On pioche une colonne au hasard dans l'intervalle [0, (nombre de colonnes)]
				colonne = (int)((Math.random() * 100) % (grille.getColonnes() + 1));
				ligne = grille.trouveLigne(colonne);
				// On s'assure qu'on puisse la poser
			} while (!(grille.estColonneValide(colonne)));
		
			return new Coup(ligne, colonne);
		}
	}
}
