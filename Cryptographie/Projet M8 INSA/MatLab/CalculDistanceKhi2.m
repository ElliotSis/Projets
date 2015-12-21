% Script de calcul de la distance du chi2 et de la p-valeur avec les monogrammes - CalculDistanceKhi2.m

% Chargement des frequences du fichier source
TraitementLettres;

% Sauvegarde des frequences reelles dans une variable
frqReelle = freq/100;

% Chargement des effectifs du fichier etudie
TraitementLettres;

% Calcul de n
n = sum(effectifs)

% Affichage des frequences
effectifs
n*frqReelle - effectifs

% Calcul de la distance
khi2 = 0;
for i = 1:26
    khi2 = khi2 + ((effectifs(i) - n*frqReelle(i))^2)/(n*frqReelle(i));
end;

% Affichage de la distance et de la p-valeur
khi2
pval = (1 - cdf('chi2', khi2, 25))*100