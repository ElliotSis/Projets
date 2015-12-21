
public abstract class IA {
	
	/*
	 * VARIABLES DE CLASSE
	 */
	
	private static Pion pionHumain;
	private static Pion pionIA;
	private static Coup[] coupsPossibles;
	private static Coup coupJoue;
	
	/*
	 * CONSTANTES
	 */
	
	private static final int INFINI = 100000;
	private static final int BORNE_SUP = 1000;
	private static final int BORNE_INF = -BORNE_SUP;
	
	/*
	 * ACCESSEURS ET MUTATEURS
	 */
	
	// *** Accesseurs ***
	
	// Retourner le pion humain
	public static Pion getPionHumain() {
		return pionHumain;
	}
	
	// Retourner le pion de l'IA
	public static Pion getPionIA() {
		return pionIA;
	}
	
	// *** Mutateurs ***
	
	// Modifier le pion humain
	public static void setPionHumain(Pion pPionHumain) {
		pionHumain = pPionHumain;
	}
	
	// Modifier le pion de l'IA
	public static void setPionIA(Pion pPionIA) {
		pionIA = pPionIA;
	}
	
	/*
	 * MÉTHODES DE CLASSE
	 */
	
	/* Trouver le meilleur coup possible jouable par l'IA sur la grille 
	avec une certaine profondeur */
	public static Coup trouveMeilleurCoup(Grille grille, int nAlignes, int profondeur) {
		/* On prend un maximum très faible, qui sort des bornes définies par la fonction
		d'évaluation */
		int max = -INFINI, valCoup = 0;
		Coup meilleurCoup = null;
		coupsPossibles = grille.trouveCoupsPossibles();
		
		// Pour chaque coup dans le tableau des coups possibles
		for (Coup coup : coupsPossibles) {
			// On simule le coup
			coup.simuler(pionIA, grille);
			
			// On assigne le coup joué actuellement
			coupJoue = coup;
			
			// La valeur associée au coup courant est le minimum de la valeur associée aux coup fils
			valCoup = Min(grille, nAlignes, profondeur);
			
			/* Le meilleur coup est celui dont la valeur est maximale (c'est l'IA qui joue)
			On ajoute une dimension aléatoire à l'algo, en choississant au hasard le meilleur coup
			si le max est égal à valCoup */
			if (valCoup > max || ((valCoup == max) && ((int)((Math.random() * 2)) == 0))) {
				max = valCoup;
				meilleurCoup = coup;
			}
			
			// On annule le coup
			coup.annuler(grille);
		}
		
		return meilleurCoup;
	}
	
	// Rechercher la valeur minimale de tout les coups possibles
	private static int Min(Grille grille, int nAlignes, int profondeur) {
		/* On prend un minimum très fort, qui sort des bornes définies par la fonction
		d'évaluation */
		int min = INFINI, valCoup = 0;
		coupsPossibles = grille.trouveCoupsPossibles();
		
		/* Si la profondeur est nulle ou bien si la partie est finie, on évalue la grille
		sachant que c'est l'IA qui a joué précedemment */
		// Si l'IA à gagné
		if (coupJoue.estGagnant(pionIA, grille, nAlignes))
			// On cherche à gagner le plus vite possible, donc évalue par la borne sup - les coups
			return BORNE_SUP - grille.trouveNombreCoupsJoue();
		// Sinon si la grille est pleine, il y a match nul, donc on évalue cela à 0
		else if (grille.estPleine())
			return 0;
		// Sinon si la profondeur est nulle, on arrête le parcours de l'arbre et on évalue la grille
		else if (profondeur == 0)
			return evaluation(grille, nAlignes);
		
		// Pour chaque coup dans le tableau des coups possibles
		for (Coup coup : coupsPossibles) {
			// On simule le coup
			coup.simuler(pionHumain, grille);
			
			// On assigne le coup joué actuellement
			coupJoue = coup;
			
			// La valeur associée au coup courant est le maximum de la valeur associée aux coup fils
			valCoup = Max(grille, nAlignes, profondeur - 1);
			
			// On cherche le minimum en comparant à chaque itération les deux valeurs
			if (valCoup < min || ((valCoup == min) && ((int)((Math.random() * 2)) == 0)))
				min = valCoup;
			
			// On annule le coup
			coup.annuler(grille);
		}
		
		return min;
	}
	
	// Rechercher la valeur maximale de tout les coups possibles
	private static int Max(Grille grille, int nAlignes, int profondeur) {
		/* On prend un maximum très faible, qui sort des bornes définies par la fonction
		d'évaluation */
		int max = -INFINI, valCoup = 0;
		coupsPossibles = grille.trouveCoupsPossibles();
		
		/* Si la profondeur est nulle ou bien si la partie est finie, on évalue la grille
		sachant que c'est l'Humain qui a joué précedemment */
		// Si l'humain à gagné
		if (coupJoue.estGagnant(pionHumain, grille, nAlignes))
			// On cherche à survivre le plus longtemps possible, donc évalue par la borne inf + les coups
			return BORNE_INF + grille.trouveNombreCoupsJoue();
		// Sinon si la grille est pleine, il y a match nul, donc on évalue cela à 0
		else if (grille.estPleine())
			return 0;
		// Sinon si la profondeur est nulle, on arrête le parcours de l'arbre et on évalue la grille
		else if (profondeur == 0)
			return evaluation(grille, nAlignes);
		
		// Pour chaque coup dans le tableau des coups possibles
		for (Coup coup : coupsPossibles) {
			// On simule le coup
			coup.simuler(pionIA, grille);
			
			// On assigne le coup joué actuellement
			coupJoue = coup;
			
			// La valeur associée au coup courant est le minimum de la valeur associée aux coup fils
			valCoup = Min(grille, nAlignes, profondeur - 1);
				
			// On cherche le minimum en comparant à chaque itération les deux valeurs
			if (valCoup > max || ((valCoup == max) && ((int)((Math.random() * 2)) == 0)))
				max = valCoup;
				
			// On annule le coup
			coup.annuler(grille);
		}
			
		return max;
	}
	
	// Évaluer la grille
	private static int evaluation(Grille grille, int nAlignes) {
		int resultat = 0;
		Coup[] coupsJoues = grille.trouveCoupsJoues();
		
		// Pour chaque coup joué
		for (Coup coup : coupsJoues) {
				
			if (grille.getPionAt(coup).equals(pionIA))
				resultat += evaluationAlignement(grille.nbPionsAlignesHoriz(pionIA, coup), nAlignes)
				+ evaluationAlignement(grille.nbPionsAlignesVert(pionIA, coup), nAlignes)
				+ evaluationAlignement(grille.nbPionsAlignesDiagGD(pionIA, coup), nAlignes)
				+ evaluationAlignement(grille.nbPionsAlignesDiagDG(pionIA, coup), nAlignes);
			
			else if (grille.getPionAt(coup).equals(pionHumain))
				resultat -=  (evaluationAlignement(grille.nbPionsAlignesHoriz(pionIA, coup), nAlignes) 
				+ evaluationAlignement(grille.nbPionsAlignesVert(pionIA, coup), nAlignes)
				+ evaluationAlignement(grille.nbPionsAlignesDiagGD(pionIA, coup), nAlignes)
				+ evaluationAlignement(grille.nbPionsAlignesDiagDG(pionIA, coup), nAlignes));
		}
	
		return resultat;
	}
	
	// Évaluer l'alignement
	private static int evaluationAlignement(int nbPionsAlignes, int nAlignes) {
		int resultat = 0;
		
		switch (nAlignes) {
		case 3 :
			switch (nbPionsAlignes) {
			case 1 :
				resultat = 1;
				break;
			case 2 :
				resultat = (int)(BORNE_SUP / 20);
				break;
			case 3 :
				resultat = BORNE_SUP;
				break;
			case 4 :
				resultat = BORNE_SUP;
				break;
			case 5 :
				resultat = BORNE_SUP;
				break;
			case 6 :
				resultat = BORNE_SUP;
				break;
			case 7 :
				resultat = BORNE_SUP;
				break;
			case 8 :
				resultat = BORNE_SUP;
				break;
			case 9 :
				resultat = BORNE_SUP;
				break;
			default :
			}
			break;
		case 4 :
			switch (nbPionsAlignes) {
			case 1 :
				resultat = 1;
				break;
			case 2 :
				resultat = (int)(BORNE_SUP / 100);
				break;
			case 3 :
				resultat = (int)(BORNE_SUP / 20);
				break;
			case 4 :
				resultat = BORNE_SUP;
				break;
			case 5 :
				resultat = BORNE_SUP;
				break;
			case 6 :
				resultat = BORNE_SUP;
				break;
			case 7 :
				resultat = BORNE_SUP;
				break;
			case 8 :
				resultat = BORNE_SUP;
				break;
			case 9 :
				resultat = BORNE_SUP;
				break;
			default :
			}
			break;
		case 5 :
			switch (nbPionsAlignes) {
			case 1 :
				resultat = 1;
				break;
			case 2 :
				resultat = (int)(BORNE_SUP / 200);
				break;
			case 3 :
				resultat = (int)(BORNE_SUP / 100);
				break;
			case 4 : 
				resultat = (int)(BORNE_SUP / 20);
				break;
			case 5 :
				resultat = BORNE_SUP;
				break;
			case 6 :
				resultat = BORNE_SUP;
				break;
			case 7 :
				resultat = BORNE_SUP;
				break;
			case 8 :
				resultat = BORNE_SUP;
				break;
			case 9 :
				resultat = BORNE_SUP;
				break;
			default :
			}
			break;
		case 6 :
			switch (nbPionsAlignes) {
			case 1 :
				resultat = 1;
				break;
			case 2 :
				resultat = (int)(BORNE_SUP / 300);
				break;
			case 3 :
				resultat = (int)(BORNE_SUP / 200);
				break;
			case 4 : 
				resultat = (int)(BORNE_SUP / 100);
				break;
			case 5 :
				resultat = (int)(BORNE_SUP / 20);
				break;
			case 6 :
				resultat = BORNE_SUP;
				break;
			case 7 :
				resultat = BORNE_SUP;
				break;
			case 8 :
				resultat = BORNE_SUP;
				break;
			case 9 :
				resultat = BORNE_SUP;
				break;
			default :
			}
			break;
		case 7 :
			switch (nbPionsAlignes) {
			case 1 :
				resultat = 1;
				break;
			case 2 :
				resultat = (int)(BORNE_SUP / 500);
				break;
			case 3 :
				resultat = (int)(BORNE_SUP / 300);
				break;
			case 4 : 
				resultat = (int)(BORNE_SUP / 200);
				break;
			case 5 :
				resultat = (int)(BORNE_SUP / 100);
				break;
			case 6 :
				resultat = (int)(BORNE_SUP / 20);
				break;
			case 7 :
				resultat = BORNE_SUP;
				break;
			case 8 :
				resultat = BORNE_SUP;
				break;
			case 9 :
				resultat = BORNE_SUP;
				break;
			default :
			}
			break;
		default :
		}
		
		return resultat;
	}
}

