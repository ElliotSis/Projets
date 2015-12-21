% Script de traitement des donnees : Effectif des bigrammes

% Importation des donnees
fichier = input('Rentrez le chemin fichier à étudier : ', 's');
tmp = importdata(fichier);
effectifs = tmp.data;
name = tmp.textdata;

% Calcul des frequences
freq = 100*effectifs./sum(sum(effectifs));

% Tri des donnees dans l'ordre decroissant
tmp = {upper(name) effectifs freq};
[unused order] = sort(effectifs, 'descend');
res = cellfun(@(x)x(order),tmp,'un',0);

% Exportation des bigrammes au format tableau latex dans le fichier 'resultatBig.txt'
filename = 'resultatBig.txt';
fid = fopen(filename, 'w');

for row=1:26
    fprintf(fid, '\t\\textbf{%s} & % 7.0f & % 02.2f\\\\\n\t\\hline\n', res{1}{row}, res{2}(row), res{3}(row));
end

fclose(fid);

% Recherche des paires de lettres
for i = 1:26 
    namePaires{i} = name{26*(i-1) + i};
    effectifsPaires(i) = effectifs(26*(i-1) + i);
    freqPaires(i) = freq(26*(i-1) + i);
end
res = {upper(namePaires) effectifsPaires freqPaires}; 

% Exportation des paires de lettres au format tableau latex dans le fichier 'resultatPaires.txt'
filename = 'resultatPaires.txt';
fid = fopen(filename, 'w');

for row=1:26
    fprintf(fid, '\t\\textbf{%s} & % 7.0f & % 02.2f\\\\\n\t\\hline\n', res{1}{row}, res{2}(row), res{3}(row));
end

fclose(fid);

% Calcul de moyenne & cie
moyenne = [mean(effectifs) mean(freq)];
variance = [var(effectifs) var(freq)];
ecartType = [std(effectifs) std(freq)];
mediane = [median(effectifs) median(freq)];
name = {'Moyenne'; 'Variance'; 'Écart-type'; 'Médiane'};
numbers = [moyenne; variance; ecartType; mediane];
res = {name numbers};

% Exportation des résultats de la description au format tableau latex dans le fichier 'resultatDescriptionBig.txt'
filename = 'resultatDescriptionBig.txt';
fid = fopen(filename, 'w');

for row=1:4
    fprintf(fid, '\t\\textbf{%s} & % 7.2f & % 02.2f\\\\\n\t\\hline\n', res{1}{row}, res{2}(row,1), res{2}(row,2));
end

fclose(fid);
