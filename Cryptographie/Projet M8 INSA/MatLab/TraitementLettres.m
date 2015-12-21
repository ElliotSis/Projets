% Script de traitement des données : Effectif des lettres
fichier = input('Rentrez le chemin fichier à étudier : ', 's');
tmp = importdata(fichier);
dt = tmp.data;

effectifs = [dt(1)+dt(2)+dt(3); dt(4); dt(5); dt(6); dt(7)+dt(8)+dt(9)+dt(10)+dt(11);
    dt(12); dt(13); dt(14); dt(15)+dt(16)+dt(17); dt(18); dt(19); dt(20);
    dt(21); dt(22); dt(23)+dt(24); dt(25); dt(26); dt(27); dt(28); dt(29); dt(30)+dt(31)+dt(32);
    dt(33); dt(34); dt(35); dt(36); dt(37)];
freq = 100*effectifs./sum(effectifs);
total = [sum(effectifs) sum(freq)];
numbers = [effectifs freq; total];
name = {'A'; 'B'; 'C'; 'D'; 'E'; 'F'; 'G'; 'H'; 'I'; 'J'; 'K'; 'L'; 'M'; 'N'; 'O'; 'P'; 'Q'; 'R'; 'S'; 'T'; 'U'; 'V'; 'W'; 'X'; 'Y'; 'Z'; 'Total'};
res = {name numbers};

h = figure;
bar(freq);
set(gca,'XTick', 1:26 ,'XTickLabel',['A':'Z']');
ylim([0 18]);
xlim([0 27]);
ylabel('Frequence (%)');
print(h, '-dpng', 'res.png');
close(h);

[nrows ncolumns] = size(res{2});

filename = 'resultatFrequences.txt';
fid = fopen(filename, 'w');

for row=1:nrows
    fprintf(fid, '\t\\textbf{%s} & % 7.0f & % 02.2f\\\\\n\t\\hline\n', res{1}{row}, res{2}(row,1), res{2}(row,2));
end

fclose(fid);

moyenne = [mean(effectifs) mean(freq)];
variance = [var(effectifs) var(freq)];
ecartType = [std(effectifs) std(freq)];
mediane = [median(effectifs) median(freq)];
name = {'Moyenne'; 'Variance'; 'Écart-type'; 'Médiane'};
numbers = [moyenne; variance; ecartType; mediane];
res = {name numbers};

filename = 'resultatDescription.txt';
fid = fopen(filename, 'w');

for row=1:4
    fprintf(fid, '\t\\textbf{%s} & % 7.2f & % 02.2f\\\\\n\t\\hline\n', res{1}{row}, res{2}(row,1), res{2}(row,2));
end

fclose(fid);

IC = sum((effectifs.*(effectifs - 1))./(sum(effectifs)*(sum(effectifs) - 1)))
