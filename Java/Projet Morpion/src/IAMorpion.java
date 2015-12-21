
public class IAMorpion extends JoueurMorpion {
	
	/*
	 * VARIABLES D'INSTANCE
	 */
	
	protected int difficulte;
	
	/*
	 * CONSTRUCTEURS
	 */
	
	// Instancier une IA du morpion
	public IAMorpion(String nom, Pion pion, int p_difficulte) {
		super(nom, pion);
		this.difficulte = p_difficulte;
	}
	
	/*
	 * MÉTHODES D'INSTANCE
	 */
	
	// Jouer le tour de l'IA
	public void jouer(Plateau p){
		PlateauMorpion p1 = (PlateauMorpion)p;
		switch(this.difficulte) {
			case 1 : minMax(p1, 2); break;
			case 2 : minMax(p1, 5); break;
			case 3 : minMax(p1, 9); break;
		}
	}
	
	// Algo MinMax
	private void minMax(PlateauMorpion p, int profondeur){
        int max = -10000;
        int tmp, maxi = 0, maxj = 0;
         
        for(int i=0 ; i<3 ; i++) {
             for(int j=0 ; j<3 ; j++){
                   if(p.getTabPionPos(i,j).equals(Pion.Rien)){
                         p.setTabPionPos(i, j, Pion.Rond);
                         tmp = min(p, profondeur-1);
                           
                         if(tmp > max){
                               max = tmp;
                               maxi = i;
                               maxj = j;
                         }
                         p.setTabPionPos(i, j, Pion.Rien);
                   }
             }
        }
        p.setTabPionPos(maxi, maxj, Pion.Rond);
   }
    
   private int max(PlateauMorpion p, int profondeur){
        int max = -10000;
        int tmp;
         
        if(profondeur == 0 || p.estGagnant() || p.matchNul()) {
             return eval(p);
        }
         
        for(int i=0 ; i<3 ; i++) {
             for(int j=0 ; j<3 ; j++){
                   if(p.getTabPionPos(i,j).equals(Pion.Rien)){
                         p.setTabPionPos(i, j, Pion.Croix);
                         tmp = min(p, profondeur-1);
                           
                         if(tmp > max){
                               max = tmp;
                         }
                         p.setTabPionPos(i, j, Pion.Rien);
                   }
             }
        }
        return max;
   }
    
   private int min(PlateauMorpion p, int profondeur){
        int min = 10000;
        int tmp;
         
        if(profondeur == 0 || p.estGagnant() || p.matchNul()) {
             return eval(p);
        }
         
        for(int i=0 ; i<3 ; i++) {
             for(int j=0 ; j<3 ; j++){
                   if(p.getTabPionPos(i,j).equals(Pion.Rien)){
                         p.setTabPionPos(i, j, Pion.Rond);
                         tmp = max(p, profondeur-1);
                           
                         if(tmp < min){
                               min = tmp;
                         }
                         p.setTabPionPos(i, j, Pion.Rien);
                   }
             }
        }
        return min;
   }
   
   private void nb_series(PlateauMorpion p,int series_j1, int series_j2, int n)
   { 
        int compteur1, compteur2, i, j;
         
        series_j1 = 0;
        series_j2 = 0;
    
        compteur1 = 0;
        compteur2 = 0;
    
         //Diagonale descendante
        for(i=0;i<3;i++)
        {
             if(p.getTabPionPos(i,i).equals(Pion.Rond))
             {
                  compteur1++;
                  compteur2 = 0;
    
                  if(compteur1 == n)
                  {
                       series_j1++;
                  }
             }
             else if(p.getTabPionPos(i,i).equals(Pion.Croix))
             {
                  compteur2++;
                  compteur1 = 0;
          
                  if(compteur2 == n)
                  {
                        series_j2++;
                  }
             }        
        }
    
        compteur1 = 0;
        compteur2 = 0;
    
        //Diagonale montante
        for(i=0;i<3;i++)
        {
             if(p.getTabPionPos(i,2-i).equals(Pion.Rond))
             {
                  compteur1++;
                  compteur2 = 0;
    
                  if(compteur1 == n)
                  {
                       series_j1++;
                  }
             }
             else if(p.getTabPionPos(i,2-i).equals(Pion.Croix))
             {
                  compteur2++;
                  compteur1 = 0;
          
                  if(compteur2 == n)
                  {
                        series_j2++;
                  }
             }        
        }
    
        //En ligne
        for(i=0;i<3;i++)
        {
             compteur1 = 0;
             compteur2 = 0;
            
             //Horizontalement
             for(j=0;j<3;j++)
             {
                  if(p.getTabPionPos(i,j).equals(Pion.Rond))
                  {
                       compteur1++;
                       compteur2 = 0;
    
                       if(compteur1 == n)
                       {
                            series_j1++;
                       }
                  }
                  else if(p.getTabPionPos(i,j).equals(Pion.Croix))
                  {
                       compteur2++;
                       compteur1 = 0;
    
                       if(compteur2 == n)
                       {
                            series_j2++;
                       }
                  }
             }
    
             compteur1 = 0;
             compteur2 = 0;
    
             //Verticalement
             for(j=0;j<3;j++)
             {
                  if(p.getTabPionPos(j,i).equals(Pion.Rond))
                  {
                       compteur1++;
                       compteur2 = 0;
    
                       if(compteur1 == n)
                       {
                            series_j1++;
                       }
                  }
                  else if(p.getTabPionPos(j,i).equals(Pion.Croix))
                  {
                       compteur2++;
                       compteur1 = 0;
    
                       if(compteur2 == n)
                       {
                            series_j2++;
                       }
                  }
             }
        }
   }
   
   private int eval(PlateauMorpion p) {
	   int res;
	   int nb_de_pions = 0;
	   
	   for(int i=0;i<3;i++)
	     {
	          for(int j=0;j<3;j++)
	          {
	               if(!(p.getTabPionPos(i,j).equals(Pion.Rien)))
	               {
	                    nb_de_pions++;
	               }
	          }
	     }
	   
	   int j1 = 0, j2 = 0;
	   nb_series(p,j1,j2,3);
	   if(p.estGagnant() || p.matchNul())
	     {
	          if(j1 == 1)
	          {
	               res = 1000 - nb_de_pions;
	          }
	          else if( j2 == 1 )
	          {
	               res = -1000 + nb_de_pions;
	          }
	          else
	          {
	               res = 0;
	          }
	     }
	   else {
		   nb_series(p,j1,j2,2);
		   res = j1 - j2;
	   }
	   return res;
   }
	

}
