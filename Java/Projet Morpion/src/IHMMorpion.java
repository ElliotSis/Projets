import java.util.Scanner;

public class IHMMorpion {
	
	/*
	 * MÉTHODES DE CLASSE
	 */
	
	// Afficher le menu dans la console
	public static int menu() {
		int mode;
		Scanner sc = new Scanner(System.in);
		
		System.out.println(" ---------------------------------------");
		System.out.println("|		JEU DU MORPION		|");
		System.out.println(" ---------------------------------------");

			do {
				System.out.println("| Quel mode de jeu desirez-vous?");
		        	System.out.println("| 1. Mode 2 joueurs");
				System.out.println("| 2. Mode joueur VS ordinateur");
				System.out.println("| 3. Quitter le programme");
				System.out.print("| Votre choix : ");
				mode=sc.nextInt();
			}while (mode!=1 && mode!=2 && mode!=3);
                
		return mode;

	}

	// Demander le nom d'un joueur dans la console
	public static String demanderNomJoueur(int numeroDuJoueur) {
		Scanner sc = new Scanner(System.in);
		String nom;
		System.out.print("| Choisissez le nom du joueur n°" + numeroDuJoueur + " : ");
		nom = sc.nextLine();
		return nom;
	}
	
	// Demander la difficulté de l'IA dans la console
		public static int demanderDifficulteIA() {
			Scanner sc = new Scanner(System.in);
			int difficulte;
			do {
				System.out.print("| Choisissez la difficulte de l'IA (entre 1 et 3) : ");
				difficulte = sc.nextInt();
			} while (difficulte < 1 || difficulte > 3);
			return difficulte;
		}
	
	// Afficher le plateau dans la console
	public static void afficherPlateau(Plateau p) {
		System.out.println("|");
		int cpt = 0;
		
		for(int i = 0 ; i < p.getHauteur() ; i++) {
			if (i != 0)
				System.out.println("| ----------");
				System.out.print("| ");
			for(int j = 0 ; j < p.getLongueur() ; j++) {
				cpt++;
				if (p.getTabPionPos(i,j) != Pion.Rien)
					System.out.print(p.getTabPionPos(i,j).toString());
				else
					System.out.print(cpt);
				if (j != 2)
					System.out.print(" | ");
			}
			System.out.println();
		}
		System.out.println("|");
	}

	// Demander le choix du joueur dans la console
	public static int demanderChoix(Joueur j) {
		int choix;
		Scanner sc = new Scanner(System.in);
		do {
			System.out.print("| " + j.getNom() + " , choisissez la case à remplir : ");
			choix = sc.nextInt();
		} while(choix < 1 && choix > 9);
		return choix;
	}
	
	// Afficher le gagnant dans la console
	public static void afficherGagnant(Joueur j) {
		System.out.println("| " + j.getNom() + " gagne");	
	}
	
	// Afficher qu'il y a un match nul dans la console
	public static void afficherMatchNul() {
		System.out.println("| Match Nul !");	
	}
	
	// Afficher que c'est la fin dans la console
		public static void fin() {
			System.out.println("| ---------------- FIN ----------------");
		}

}
