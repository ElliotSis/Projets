
public class JeuMorpion extends Jeu {
	
	/*
	 * CONSTRUCTEURS
	 */
	
	// Instancier un jeu du morpion
	public JeuMorpion(String j1, String j2, int difficulte) {
		if (difficulte == 0) {
			this.joueur1 = new JoueurMorpion(j1, Pion.Croix);
			this.joueur2 = new JoueurMorpion(j2, Pion.Rond);
			this.plateau = new PlateauMorpion();
		}
		else {
			this.joueur1 = new JoueurMorpion(j1, Pion.Croix);
			this.joueur2 = new IAMorpion(j2, Pion.Rond, difficulte);
			this.plateau = new PlateauMorpion();
		}
	}
	
	/*
	 * MÉTHODES D'INSTANCE
	 */
	
	// Jouer une partie
	public void jouerPartie() {
		int jCourant = 0;
		
		// Cast pour les méthodes d'instances des classes spécifiques au morpion
		PlateauMorpion p = (PlateauMorpion)plateau;
		
		do{	
			IHMMorpion.afficherPlateau(p);
			if (jCourant % 2 == 0)
				joueur1.jouer(p);
			else{
				joueur2.jouer(p);
			}
			jCourant++;
	
		}while (!(p.estGagnant()) && !(p.matchNul()));
		
		IHMMorpion.afficherPlateau(p);
		
		if (p.estGagnant()){
			if (jCourant % 2 == 0)
				IHMMorpion.afficherGagnant(joueur2);
			else
				IHMMorpion.afficherGagnant(joueur1);
		}
		else
			IHMMorpion.afficherMatchNul();
		
		IHMMorpion.fin();
    }

}
