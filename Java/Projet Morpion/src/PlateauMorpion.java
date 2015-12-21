
public class PlateauMorpion extends Plateau {
	
	/*
	 * CONSTRUCTEURS
	 */
	
	// Instancier un plateau du morpion
	public PlateauMorpion() {
		super(3,3);
	}
	
	/*
	 * MÉTHODES D'INSTANCE
	 */
	
	// Dire si il y a match nul sur le plateau
	public boolean matchNul(){
		boolean resultat = true;
		
		for(int i = 0 ; i < this.hauteur ; i++) {
			for(int j = 0 ; j < this.longueur ; j++) {
				resultat = ((resultat) && (this.tabPion[i][j] != Pion.Rien));
			}
		}
		
		return resultat;
	}
	
	// Dire si il y a un gagnant sur le plateau
	public boolean estGagnant() {
		return ((this.estGagnantSurLesLignes()) || (this.estGagnantSurLesColonnes()) || (this.estGagnantSurLesDiagonales()));
	}

	// Dire si il y a un gagnant sur les lignes
	private boolean estGagnantSurLesLignes() {
		return ((this.tabPion[0][0].equals(this.tabPion[0][1])) && (this.tabPion[0][1].equals(this.tabPion[0][2])) && (!(this.tabPion[0][1].equals(Pion.Rien)))
				|| (this.tabPion[1][0].equals(this.tabPion[1][1])) && (this.tabPion[1][1].equals(this.tabPion[1][2])) && (!(this.tabPion[1][1].equals(Pion.Rien)))
				|| (this.tabPion[2][0].equals(this.tabPion[2][1])) && (this.tabPion[2][1].equals(this.tabPion[2][2])) && (!(this.tabPion[2][1].equals(Pion.Rien))));
	}
	
	// Dire si il y a un gagnant sur les colonnes
	private boolean estGagnantSurLesColonnes() {
		return ((this.tabPion[0][0].equals(this.tabPion[1][0])) && (this.tabPion[1][0].equals(this.tabPion[2][0])) && (!(this.tabPion[1][0].equals(Pion.Rien)))
				|| (this.tabPion[0][1].equals(this.tabPion[1][1])) && (this.tabPion[1][1].equals(this.tabPion[2][1])) && (!(this.tabPion[1][1].equals(Pion.Rien)))
				|| (this.tabPion[0][2].equals(this.tabPion[1][2])) && (this.tabPion[1][2].equals(this.tabPion[2][2])) && (!(this.tabPion[1][2].equals(Pion.Rien))));
	}
	
	// Dire si il y a un gagnant sur les diagonales
	private boolean estGagnantSurLesDiagonales() {
		return (!(this.tabPion[1][1].equals(Pion.Rien))
				&& ((((this.tabPion[0][0].equals(this.tabPion[1][1])) && (this.tabPion[1][1].equals(this.tabPion[2][2]))))
				|| ((this.tabPion[0][2].equals(this.tabPion[1][1])) && (this.tabPion[1][1].equals(this.tabPion[2][0])))));
	}
	
}
