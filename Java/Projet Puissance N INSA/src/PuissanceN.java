import java.util.Scanner;

public class PuissanceN {
	
	/*
	 * VARIABLES DE CLASSE
	 */
	
	private static int nAlignes = 4;
	private static Grille grille = new Grille(6, 7);
	private static Joueur[] tabJoueurs = new Joueur[2];
	private static Scanner sc = new Scanner(System.in);
	
	/*
	 * CONSTRUCTEURS
	 */
	
	// Instancier une partie de Puissance N
	public PuissanceN() {
		// D�clarations
		int choixJeu = 0, choixMode = 0, lignes = 0, colonnes = 0, difficulte = 0;
		String joueur1 = "", joueur2 = "";
		
		// Initialisation de la grille
		grille = new Grille(6, 7);
		// Initialisation du nombre de pions � aligner
		nAlignes = 4;
		
		// Choix du jeu
		do {
			System.out.print("\n1 - Puissance 4 basique\n2 - Puissance N" +
					"\nChoisissez le jeu auquel vous souhaitez jouer : ");
			// Prise en charge de l'�ventuelle exception
			try {
				choixJeu = Integer.valueOf(sc.nextLine()).intValue();
			}
			catch (Exception e) {
			}
			finally {
				if (!(choixJeu == 1 || choixJeu == 2))
					System.out.println("Mauvaise saisie, merci de r�it�rer");
			}
		} while (!(choixJeu == 1 || choixJeu == 2));
		
		// Configuration du puissance N (grille et nombre de pions � aligner)
		if (choixJeu == 2){
			do {
				System.out.print("\nRentrez le nombre de lignes de la grille de jeu : ");
				// Prise en charge de l'�ventuelle exception
				try {	
					lignes = Integer.valueOf(sc.nextLine()).intValue();
				}
				catch (Exception e) {
				}
				finally {
					if (!(lignes > 2 && lignes < 10))
						System.out.print("Le nombre de lignes entr� est invalide " +
								"(il doit �tre compris entre 3 et 9), merci de r�it�rer");
				}
			} while (!(lignes > 2 && lignes < 10));
			
			do {
				System.out.print("\nRentrez le nombre de colonnes de la grille de jeu : ");
				// Prise en charge de l'�ventuelle exception
				try {	
					colonnes = Integer.valueOf(sc.nextLine()).intValue();
				}
				catch (Exception e) {
				}
				finally {
					if (!(colonnes > 2 && colonnes < 10))
						System.out.print("Le nombre de colonnes entr� est invalide " +
								"(il doit �tre compris entre 3 et 9), merci de r�it�rer");
				}	
			} while (!(colonnes > 2 && colonnes < 10));
			
			grille = new Grille(lignes, colonnes);
			
			do {
				System.out.print("\nRentrez le nombre de pions � aligner pour gagner : ");
				// Prise en charge de l'�ventuelle exception
				try {	
					nAlignes = Integer.valueOf(sc.nextLine()).intValue();
				}
				catch (Exception e) {
				}
				finally {
					if (!(nAlignes > 2 && (nAlignes <= lignes || nAlignes <= colonnes) && nAlignes < 8))
						System.out.print("Le nombre de pions � aligner entr� est invalide " +
								"(il doit �tre compris entre 3 et 7), merci de r�it�rer");
				}
			} while (!(nAlignes > 2 && (nAlignes <= lignes || nAlignes <= colonnes) && nAlignes < 8));
		}
		
		// Choix du mode de jeu
		do {
			System.out.print("\n1 - Mode un joueur\n2 - Mode deux joueurs" +
					"\nChoisissez votre mode de jeu : ");
			// Prise en charge de l'�ventuelle exception
			try {
				choixMode = Integer.valueOf(sc.nextLine()).intValue();
			}
			catch (Exception e) {
			}
			finally {
				if (!(choixMode == 1 || choixMode == 2))
					System.out.println("Mauvaise saisie, merci de r�it�rer");
			}			
		} while (!(choixMode == 1 || choixMode == 2));
		
		// Configuration du tableau de joueurs selon le mode choisi
		switch (choixMode) {
		case 1 :
			do {
				System.out.print("\nRentrez votre nom : ");
				joueur1 = sc.nextLine();
				if (joueur1.equals(""))
					System.out.println("Merci de rentrer un nom");
			} while (joueur1.equals(""));
			
			do {
				System.out.print("\n1 - Facile (Reese)\n2 - Moyenne (Dewey)\n3 - Difficile (Malcolm)" +
						"\nRentrez la difficult� de l'IA d�sir�e : ");
				// Prise en charge de l'�ventuelle exception
				try {
					difficulte = Integer.valueOf(sc.nextLine()).intValue();
				}
				catch (Exception e) {
				}
				finally {
					if (!(difficulte > 0 && difficulte < 4))
						System.out.println("La difficult� entr�e est invalide, merci de r�it�rer");
				}
			} while(!(difficulte > 0 && difficulte < 4));
			
			tabJoueurs[0] = new Joueur(joueur1);
			// On informe l'IA que le pion que l'humain jouera sera celui du joueur 1
			IA.setPionHumain(tabJoueurs[0].getPion());
			tabJoueurs[1] = new Joueur(difficulte);
			// On informe l'IA que le pion que l'IA jouera sera celui du joueur 2
			IA.setPionIA(tabJoueurs[1].getPion());
			break;
		case 2 :
			do {
				do {
					System.out.print("\nJoueur 1, rentrez votre nom : ");
					joueur1 = sc.nextLine();
					if (joueur1.equals(""))
						System.out.println("Merci de rentrer un nom");
				} while (joueur1.equals(""));
			
				do {
					System.out.print("\nJoueur 2, rentrez votre nom : ");
					joueur2 = sc.nextLine();
					if (joueur2.equals(""))
						System.out.println("Merci de rentrer un nom");
				} while (joueur2.equals(""));
				
				if (joueur1.equals(joueur2))
					System.out.println("Les deux joueurs ne peuvent pas avoir le m�me nom, " +
							"merci de r�it�rer");
			} while (joueur1.equals(joueur2));
			
			tabJoueurs[0] = new Joueur(joueur1);
			tabJoueurs[1] = new Joueur(joueur2);
			break;
		default :
		}
	}
	
	/*
	 * M�THODES DE CLASSE
	 */
	
	// Jouer au jeu
	public static int jeu() {
		// D�clarations
		int jCourant = (int)((Math.random() * 2)); // Le premier � jouer est d�finit au hasard
		int recommencer = 0;
		Coup coupActuel = null, coupPrecedent = null;
		boolean humain, coupGagnant, grillePleine;
		
		
		do {	
			// On regarde si le joueur actuel est humain
			humain = (tabJoueurs[jCourant].getComportement().getClass().getName().equals("Humain"));
			
			// Si le joueur actuel est humain
			if (humain) {
				/* On affiche la grille (on peut �crire directement cette expression 
				gr�ce � la m�thode toString()) */
				System.out.println("\n" + grille);
			
				// On affiche le coup jou� pr�cedemment
				if (coupPrecedent != null)
					System.out.println(tabJoueurs[((jCourant + 1) % 2)] + " a jou� sur la colonne n�" + 
							coupPrecedent);
				
				// On affiche que c'est � lui de jouer
				System.out.println(tabJoueurs[jCourant] + ", � vous de jouer ! (vous avez les " +
						tabJoueurs[jCourant].getPion() + ")");
			}
			// Si c'est une IA
			else
				System.out.println("\n" + tabJoueurs[jCourant] + " r�fl�chit...");
			
			// On va chercher le coup � jouer
			coupActuel = tabJoueurs[jCourant].getComportement().trouveCoup(grille, nAlignes);
			// On joue le coup � jouer sur la grille
			tabJoueurs[jCourant].joue(grille, coupActuel);
			
			// On regarde si le coup est gagnant
			coupGagnant = coupActuel.estGagnant(tabJoueurs[jCourant].getPion(), grille, nAlignes);
			// On regarde si la grille est pleine
			grillePleine = grille.estPleine();
						
			// Si le coup est gagnant, on affiche que le joueur a gagn�
			if (coupGagnant) {
				// On affiche d'abord la grille
				System.out.println("\n" + grille);
				// Si le joueur est humain, il a son message personalis�
				if (humain)
					System.out.println("Bravo " + tabJoueurs[jCourant] + ", vous gagnez la partie !");
				// Sinon, c'est l'IA qui gagne, on sugg�re au joueur humain de pratiquer
				else
					System.out.println(tabJoueurs[jCourant] + " gagne la partie, " +
						"entrainez vous pour le battre !");
			}
			// Si la grille est pleine alors que le coup n'est pas gagnant, il y a match nul
			else if (grillePleine) {
				System.out.println("\n" + grille);
				System.out.println("Match Nul !");
			}	
			
			// Le coup pr�c�dent devient le coup actuel
			coupPrecedent = coupActuel;
			
			// On change de joueur
			jCourant++;
			jCourant %= 2;
		} while (!(coupGagnant || grillePleine));
		
		// Proposer de recommencer
		do {
			System.out.println("\n1 - Recommencer la partie courante\n" +
					"2 - Commencer une nouvelle partie\n" +
					"3 - Arr�ter le programme");
			System.out.print("Que voulez-vous faire ? ");
		// Prise en charge de l'�ventuelle exception
			try {
				recommencer = Integer.valueOf(sc.nextLine()).intValue();
			}
			catch (Exception e) {
			}
			finally {				
				if ((recommencer != 1) && (recommencer != 2) && (recommencer != 3))
					System.out.println("Mauvaise saisie, merci de r�it�rer");
			}
		} while ((recommencer != 1) && (recommencer != 2) && (recommencer != 3));
		
		return recommencer;
	}
	
	// M�thode main
	public static void main(String[] args) {
		// D�clarations
		int recommencer = 2;
		
		// Affichage du titre du jeu
		System.out.println(" -------------------------------------------------------");
		System.out.println("|\t\t\tPUISSANCE N\t\t\t|");
		System.out.println(" -------------------------------------------------------");
		
		while ((recommencer == 1) || (recommencer == 2)) {
			// Si on d�cide de recommencer la partie courante il faut r�initialiser la grille
			if ((recommencer == 1))
				grille.initialise();
			
			/* Si on d�cide de recommencer une partie avec de nouveaux param�tres, 
			on redefinit les variables de classes avec le constructeur par d�faut */
			else if ((recommencer == 2))
				new PuissanceN();
			
			// On lance le jeu, on r�cup�re le choix de l'utilisateur
			recommencer = jeu();
		}
	}
}
