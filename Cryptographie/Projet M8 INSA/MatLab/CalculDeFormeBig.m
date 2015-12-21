% Script de calcul de la forme d'un texte avec les bigrammes - CalculDeFormeBig.m

% Chargement des frequences du fichier source
TraitementBigrammes;

% Sauvegarde des frequences reelles dans une variable
frqReelle = freq/100;
for i = 1:676
    if frqReelle(i) == 0 
        frqReelle(i) = 0.0000001;
    end;
end;

% Chargement des effectifs du fichier etudie
TraitementBigrammes;

% Calcul de la forme
forme = 0;
forme = 0;
for i = 1:676
    if frqReelle(i) ~= 0 
        forme = forme + effectifs(i)*log(frqReelle(i));
    end;
end;

% Affichage de la forme
forme
