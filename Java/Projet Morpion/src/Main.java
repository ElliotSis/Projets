
public class Main {

	public static void main(String[] args) {
		int choix = IHMMorpion.menu(), difficulte = 0;
		String j1 = "Joueur 1", j2 = "Joueur 2";
		boolean joue = true;
		switch (choix) {
			case 1 : j1 = IHMMorpion.demanderNomJoueur(1); j2 = IHMMorpion.demanderNomJoueur(2); break;
			case 2 : j1 = IHMMorpion.demanderNomJoueur(1); difficulte = IHMMorpion.demanderDifficulteIA(); break;
			case 3 : IHMMorpion.fin(); joue = false; break;
		}
		if (joue) {
			JeuMorpion game = new JeuMorpion(j1, j2, difficulte);
			game.jouerPartie();
		}
	}

}
