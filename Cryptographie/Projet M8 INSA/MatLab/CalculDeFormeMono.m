% Script de calcul de la forme d'un texte avec les monogrammes - CalculDeFormeMono.m

% Chargement des frequences du fichier source
TraitementLettres;

% Sauvegarde des frequences reelles dans une variable
frqReelle = freq/100;

% Chargement des effectifs du fichier etudie
TraitementLettres;

% Calcul de la forme
forme = 0;
for i = 1:26
forme = forme + effectifs(i)*log(frqReelle(i));
end;

% Affichage de la forme
forme