% Script de calcul de k, le nombre de lettres du mot-clé

% Chargement des effectifs, des fréquences et de l'IC du fichier
TraitementLettres;

% Affectation des constantes
Il = 0.0779;
Iu = 1/26;
n = sum(effectifs);

% Calcul et affichage de k
k = (n*(Il - Iu))/((Il - IC)+n*(IC - Iu))
