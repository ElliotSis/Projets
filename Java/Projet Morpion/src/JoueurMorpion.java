
public class JoueurMorpion extends Joueur {
	
	/*
	 * CONSTRUCTEURS
	 */
	
	// Instancier un joueur du morpion
	public JoueurMorpion(String nom, Pion pion) {
		super(nom, pion);
	}
	
	/*
	 * MÉTHODES D'INSTANCE
	 */
	
	// Jouer son tour
	public void jouer(Plateau p){
		int choix;
		int ligne = 0, colonne = 0;

		do {
			choix = IHMMorpion.demanderChoix(this);
			switch(choix) {
				case 1 : ligne = 0; colonne = 0; break;
				case 2 : ligne = 0; colonne = 1; break;
				case 3 : ligne = 0; colonne = 2; break;
				case 4 : ligne = 1; colonne = 0; break;
				case 5 : ligne = 1; colonne = 1; break;
				case 6 : ligne = 1; colonne = 2; break;
				case 7 : ligne = 2; colonne = 0; break;
				case 8 : ligne = 2; colonne = 1; break;
				case 9 : ligne = 2; colonne = 2; break;
			}
			
		} while(!(p.getTabPionPos(ligne,colonne).equals(Pion.Rien)));

		p.setTabPionPos(ligne, colonne, pion);
	}
}
