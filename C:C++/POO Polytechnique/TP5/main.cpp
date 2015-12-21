#include <iostream>

#include "Routeur.h"
#include "Meteo.h"
#include "Maison.h"
#include "Frigo.h"
#include "MemeAliment.h"
#include "RestrictionAlimentaire.h"

using namespace std;

int main()
{
	/*##################################*/
	/*     MISE EN PLACE DES OBJETS     */
	/*##################################*/

	// 1. Creer un routeur
	Routeur routeur;

	// 2. Creer une maison, avec l'ID 1, une adresse et la position 14.0.
	// Ajouter la maison aux connexions du routeur
	Maison maison(1, "23 rue des belges", 14.0, "Montreal");
	maison.seConnecter(&routeur);

	//3. Creer un objet Meteo et ajouter la maison a sa liste d'observateurs.
	// Ajouter ensuite les villes Montreal, Toronto et New York
	// Avec les températures respectivent 21, 15 et 22
	Meteo meteo;
	meteo.ajouterObservateur(&maison);
	meteo.ajouterVille("Montreal", 21.0);
	meteo.ajouterVille("Toronto", 15.0);
	meteo.ajouterVille("New York", 22.0);

	// 4. Creer 4 personnes: Philippe Lafrite, Mathilde Lafrite, Francois Lerigolo et Florence Lerigolo
	// Avec les preferences en gouts respectivement neutre, salé, sucré et salé
	// Ajouter une allergie alimentaire au "Arachides" pour Florence
	Personne philippe("Lafrite", "Philippe", 55, NEUTRE);
	Personne mathilde("Lafrite", "Mathilde", 59, SALE);
	Personne francois("Lerigolo", "Francois", 50, SUCRE);
	Personne florence("Lerigolo", "Florence", 44, SALE);
	

	
	// 5. Creer un cellulaire pour chaque occupant (IDs: 2, 3, 4 et 5)
	// Ajouter la maison dans la liste des observateurs de chaque cellulaire.
	Cellulaire c1(2, "#514-992-7307"); c1.ajouterObservateur(&maison); c1.setProprietaire(&philippe); philippe.attribuerCellulaire(c1.getNumero());
	Cellulaire c2(3, "#438-465-8756"); c2.ajouterObservateur(&maison); c2.setProprietaire(&mathilde); mathilde.attribuerCellulaire(c2.getNumero());
	Cellulaire c3(4, "#514-346-4467"); c3.ajouterObservateur(&maison); c3.setProprietaire(&francois); francois.attribuerCellulaire(c3.getNumero());
	Cellulaire c4(5, "#514-678-1234"); c4.ajouterObservateur(&maison); c4.setProprietaire(&florence); florence.attribuerCellulaire(c4.getNumero());
	
	// 6. Modifier la position des cellulaires de Philippe, Mathilde, Francois et Florence
	// a 7, 8, 6, 5 respectivement
	c1.setPosition(7);
	c2.setPosition(8);
	c3.setPosition(6);
	c4.setPosition(5);	

	// 7. Ajouter Philippe et Mathilde comme occupants de la maison
	// Lorsqu'on ajoute un occupant a la maison, son cellulaire doit egalement etre ajoute.
	maison.ajouterOccupant(&philippe);
	maison.ajouterOccupant(&mathilde);
	
	// 9. Créer 2 chauffages dont 1 automatiques et les connecter au routeur
	// Attention à ne pas leur attribuer des IDs similaires aux IDs déjà attribués(commencer à 5)
	Chauffage ch(6);
	Chauffage chAuto(7);
	ch.setAutomatique(false);
	chAuto.setAutomatique(true);
	ch.seConnecter(&routeur);
	chAuto.seConnecter(&routeur);

	// 10. Créer un frigo avec un ID de 10, puis connectez le au routeur.
	// Ajouter dans le frigo les aliments suivants :
	/*
	Pomme		Sucre
	Poule		Sale
	Yogourt		Sucre
	Dattes		Sucre
	Beurre		Neutre
	Arachides	Sale
	*/
	Aliment pomme("Pomme", SUCRE);
	Aliment poulet("Poulet roti", SALE);
	Aliment yogourt("Yogourt", SUCRE);
	Aliment dattes("Dattes", SUCRE);
	Aliment beurre("Beurre", NEUTRE);
	Aliment arachides("Arachides", SALE);
	Aliment amandes("Amandes", SALE);
	Frigo<Aliment> frigo(10);
	frigo.ajouterContenu(&pomme);
	frigo.ajouterContenu(&poulet);
	frigo.ajouterContenu(&yogourt);
	frigo.ajouterContenu(&dattes);
	frigo.ajouterContenu(&beurre);
	frigo.ajouterContenu(&arachides);

	florence.ajouterAllergie("Arachides");

	/*##################################*/
	/*           TEST GENERAL           */
	/*##################################*/

	
	// 1. Placer les cellulaires de Philippe et Mathilde aux positions 12.0 et 13.0 respectivement
	cout << "Philippe et Mathilde arrivent a la maison" << endl;
	c1.setPosition(12.0);
	c2.setPosition(13.0);
	

	// 2. Changer la temperature exterieure de Montreal a 24 degres (en utilisant l'objet Meteo)
	// ReChanger la temperature exterieure de Montreal a 18 degres
	// Changer la temperature exterieure de Toronto a 22 degres
	cout << endl << "Changement de temperature Montreal : 24" << endl;
	meteo.setTempVent("Montreal", 24);

	cout << endl << "Changement de temperature Montreal : 18" << endl;
	meteo.setTempVent("Montreal", 18);

	cout << endl << "Changement de temperature Toronto : 22" << endl;
	meteo.setTempVent("Toronto", 22);
	

	// 3. Placer le cellulaire de Francois à la position 15.0
	cout << endl << "Francois arrive" << endl;
	c3.setPosition(15);
	

	// 4. Placer le cellulaire de Florence à la position 15.0
	cout << endl << "Florence arrive" << endl;
	c4.setPosition(15);
	

	// 5. Sans envoyer de message, utilisez directement l'objet Frigo pour afficher le menu 
	//	que Mathilde et Florence peuvent manger en commun
	cout << endl << "Les aliments que Mathilde et Florence peuvent manger et apprecier ensemble sont:" << endl;
	frigo.suggererMenu2(RestrictionAlimentaire(&mathilde), RestrictionAlimentaire(&florence));
	
	
	// 6. Francois décide de manger une pomme et Florence des amandes.
	// Retirez les du frigo.
	cout << "\nFrancois et Florence decident de manger\n";
	frigo.retirerContenu(MemeAliment(&pomme));
	frigo.retirerContenu(MemeAliment(&amandes));
	
	// 7. Placer les cellulaires loin de la maison (position 20.0 par exemple)
	cout << endl << "Tout le monde quitte la maison" << endl;
	c1.setPosition(30);
	c2.setPosition(20);
	c3.setPosition(25);
	c4.setPosition(32);	
	
	// 8. Pour mieux vérifier les méthodes de tri, ajouter Francois et Florence
	//	  comme occupants à la maison,
	maison.ajouterOccupant(&francois);
	maison.ajouterOccupant(&florence);
	
	// 9. Trier les occupants selon leurs noms. Puis trier les occupants selon leurs ages
	maison.trierListeNomPrenom();
	cout << endl; 
	maison.trierListeAge();

	/*#############*/
	/*     FIN     */
	/*#############*/
	cout << endl;


	// 1. Desallocation de la memoire.
	// Pas besoin, on travaillé directement avec des objets.
	
	
	return 0;
}