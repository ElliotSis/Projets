import java.util.Scanner;

public class Humain implements ComportementJoueur {
	
	/*
	 * VARIABLES DE CLASSE
	 */
	
	private static Scanner sc = new Scanner(System.in);

	/*
	 * RED�FINITION DES M�THODES ABSTRAITES
	 */
	
	// Trouver le coup � jouer
	public Coup trouveCoup(Grille grille, int nAlignes) {
		int ligne = -1, colonne = -1;
		
		do {
			// On demande au joueur la colonne sur laquelle il souhaite jouer
			System.out.print("\nRentrez la colonne sur laquelle vous souhaitez jouer : ");
			// Prise en charge de l'�ventuelle exception
			try {
				colonne = Integer.valueOf(sc.nextLine()).intValue();
				colonne--;
				ligne = grille.trouveLigne(colonne);
			}
			catch (Exception e) {
				colonne = -1;
			}
			finally {
				if (!(grille.estColonneValide(colonne)))
					System.out.print("La colonne entr�e est invalide... Merci de r�it�rer");
			}
			
		} while (!(grille.estColonneValide(colonne)));
		
		return new Coup(ligne, colonne);
	}
	
}
