% Script de traitement des donnees : Effectif des mots

% Importation des donnees
fichier = input('Rentrez le chemin fichier à étudier : ', 's');
tmp = importdata(fichier);
effectifs = tmp.data;
name = tmp.textdata;

% Calcul des frequences
freq = 100*effectifs./sum(effectifs);

% Tri des donnees dans l'ordre decroissant
tmp = {upper(name) effectifs freq};
[unused order] = sort(effectifs, 'descend');
res = cellfun(@(x)x(order),tmp,'un',0);

% Suppression des mots de moins de trois lettres
i = 1;
m = size(res{1});
n = m(1);
while i <= n
    str = res{1}{i};
    if length(str) < 4
        res{1}(i,:) = [];
        res{2}(i,:) = [];
        res{3}(i,:) = [];
    else
        i = i + 1;
    end
    m = size(res{1});
    n = m(1);
end

% Exportation des mots au format tableau latex dans le fichier 'resultatMots.txt'
filename = 'resultatMots.txt';
fid = fopen(filename, 'w');

for row=1:20
    fprintf(fid, '%s\n', res{1}{row});
end

fclose(fid);