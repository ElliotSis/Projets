program hillClimbing;

uses
	sysutils;

{$J-}
const
  PROBAREELLES: array['A'..'Z'] of Real = (8.59,1.02,3.08,3.70,17.11,1.10,1.07,1.00,7.36,0.42,0.02,5.92,2.79,6.91,5.33,2.70,1.18,6.57,7.90,7.32,6.36,1.60,0.01,0.43,0.36,0.17);
  PROBAREELLESBIG: array['A'..'Z','A'..'Z'] of Real = ((0.00001,0.32,0.42,0.21,0.01,0.09,0.34,0.10,1.07,0.03,0.00001,0.55,0.38,1.01,0.02,0.38,0.11,0.86,0.69,0.51,0.77,0.59,0.00001,0.01,0.13,0.01),(0.32,0.01,0.00001,0.00001,0.25,0.00001,0.00001,0.00001,0.28,0.02,0.00001,0.37,0.00001,0.00001,0.39,0.00001,0.00001,0.30,0.06,0.01,0.09,0.00001,0.00001,0.00001,0.01,0.00001),(0.44,0.00001,0.13,0.00001,0.81,0.00001,0.00001,0.71,0.37,0.00001,0.00001,0.21,0.00001,0.00001,0.81,0.00001,0.04,0.33,0.03,0.23,0.25,0.00001,0.00001,0.00001,0.01,0.00001),(0.58,0.00001,0.00001,0.00001,1.07,0.00001,0.01,0.00001,0.71,0.01,0.00001,0.00001,0.02,0.00001,0.45,0.00001,0.00001,0.30,0.11,0.00001,0.45,0.01,0.00001,0.00001,0.01,0.00001),(0.33,0.07,0.40,0.10,0.01,0.17,0.12,0.05,0.29,0.01,0.00001,0.71,0.70,1.18,0.03,0.27,0.03,0.96,1.09,0.90,0.90,0.32,0.01,0.20,0.01,0.24),(0.46,0.00001,0.00001,0.00001,0.27,0.25,0.00001,0.00001,0.40,0.00001,0.00001,0.14,0.00001,0.00001,0.41,0.00001,0.00001,0.21,0.02,0.00001,0.16,0.00001,0.00001,0.00001,0.00001,0.00001),(0.31,0.00001,0.00001,0.00001,0.47,0.00001,0.06,0.00001,0.14,0.00001,0.00001,0.12,0.01,0.25,0.17,0.00001,0.00001,0.34,0.02,0.06,0.21,0.00001,0.00001,0.00001,0.02,0.00001),(0.50,0.00001,0.00001,0.00001,0.53,0.00001,0.00001,0.00001,0.21,0.00001,0.00001,0.00001,0.00001,0.00001,0.33,0.00001,0.00001,0.02,0.00001,0.00001,0.10,0.00001,0.00001,0.00001,0.04,0.00001),(0.23,0.14,0.30,0.27,0.90,0.13,0.29,0.00001,0.02,0.00001,0.00001,0.91,0.28,0.87,0.40,0.07,0.20,0.70,0.93,1.09,0.01,0.28,0.00001,0.16,0.00001,0.03),(0.12,0.00001,0.00001,0.00001,0.34,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.25,0.00001,0.00001,0.00001,0.00001,0.00001,0.14,0.00001,0.00001,0.00001,0.00001,0.00001),(0.01,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.01,0.00001,0.00001,0.00001,0.00001,0.00001,0.01,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001),(0.93,0.01,0.03,0.03,1.19,0.00001,0.02,0.03,0.49,0.00001,0.00001,0.76,0.02,0.00001,0.46,0.03,0.13,0.00001,0.17,0.09,0.54,0.01,0.00001,0.02,0.03,0.02),(0.79,0.30,0.00001,0.00001,0.90,0.00001,0.00001,0.00001,0.45,0.00001,0.00001,0.00001,0.50,0.02,0.58,0.40,0.00001,0.03,0.01,0.00001,0.13,0.00001,0.00001,0.00001,0.02,0.00001),(0.45,0.00001,0.54,0.73,0.90,0.18,0.36,0.02,0.34,0.01,0.01,0.03,0.00001,0.43,0.47,0.00001,0.11,0.04,0.79,1.08,0.23,0.12,0.00001,0.00001,0.01,0.02),(0.01,0.13,0.20,0.10,0.10,0.07,0.13,0.04,0.80,0.00001,0.01,0.34,0.65,1.11,0.01,0.17,0.03,0.68,0.33,0.26,1.11,0.04,0.00001,0.00001,0.21,0.01),(0.83,0.00001,0.00001,0.00001,0.58,0.00001,0.00001,0.16,0.30,0.00001,0.00001,0.47,0.00001,0.00001,0.69,0.23,0.00001,0.61,0.14,0.11,0.25,0.00001,0.00001,0.00001,0.00001,0.00001),(0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,1.02,0.00001,0.00001,0.00001,0.00001,0.00001),(0.83,0.08,0.26,0.38,1.15,0.03,0.16,0.01,0.76,0.00001,0.00001,0.12,0.26,0.20,0.68,0.08,0.06,0.39,0.53,0.54,0.23,0.12,0.00001,0.00001,0.04,0.00001),(0.69,0.01,0.17,0.00001,0.90,0.01,0.00001,0.01,0.64,0.00001,0.00001,0.01,0.04,0.01,0.69,0.19,0.18,0.00001,0.66,0.66,0.50,0.00001,0.00001,0.00001,0.02,0.00001),(0.71,0.00001,0.01,0.00001,0.95,0.00001,0.00001,0.12,0.70,0.00001,0.00001,0.01,0.00001,0.00001,0.64,0.00001,0.00001,0.81,0.30,0.43,0.32,0.00001,0.00001,0.00001,0.02,0.02),(0.32,0.10,0.22,0.19,0.82,0.11,0.09,0.00001,0.79,0.08,0.00001,0.42,0.15,0.77,0.07,0.25,0.03,0.96,0.79,0.73,0.00001,0.38,0.00001,0.47,0.05,0.02),(0.58,0.00001,0.00001,0.00001,0.68,0.00001,0.00001,0.00001,0.46,0.00001,0.00001,0.00001,0.00001,0.00001,0.59,0.00001,0.00001,0.22,0.00001,0.00001,0.06,0.00001,0.00001,0.00001,0.00001,0.00001),(0.01,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001),(0.04,0.00001,0.03,0.00001,0.04,0.00001,0.00001,0.00001,0.05,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.07,0.00001,0.00001,0.00001,0.04,0.00001,0.00001,0.00001,0.01,0.00001,0.00001),(0.15,0.00001,0.00001,0.01,0.15,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.01,0.02,0.01,0.04,0.03,0.00001,0.02,0.09,0.02,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001),(0.03,0.00001,0.00001,0.00001,0.04,0.00001,0.00001,0.00001,0.01,0.00001,0.00001,0.00001,0.00001,0.00001,0.01,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001));
  ALPHABET = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
{$J+}

type
	Bigrammes = array['A'..'Z','A'..'Z'] of LongWord;
	Monogrammes = array['A'..'Z'] of LongWord;

function compterBigrammes(texte : Ansistring) : Bigrammes;
	var l, m : Char;
		i : LongWord;
		res : Bigrammes;
begin
	for l := 'A' to 'Z' do
	begin
		for m := 'A' to 'Z' do
			res[l,m] := 0;
	end;
	for i := 2 to length(texte) do
		res[texte[i-1],texte[i]] := res[texte[i-1],texte[i]] + 1;
	compterBigrammes := res;
end;

function compterMonogrammes(texte : Ansistring) : Monogrammes;
	var l : Char;
		i : LongWord;
		res : Monogrammes;
begin
	for l := 'A' to 'Z' do
		res[l] := 0;
	for i := 1 to length(texte) do
		res[texte[i]] := res[texte[i]] + 1;
	compterMonogrammes := res;
end;

function calculerKhi2(texte : Ansistring): Real;
	var l : Char;
		khi2 : Real;
		effectifs : Monogrammes;
begin
	khi2 := 0;
	effectifs := compterMonogrammes(texte);
	for l := 'A' to 'Z' do
		khi2 := khi2 + ((effectifs[l] - length(texte)*PROBAREELLES[l]/100)*(effectifs[l] - length(texte)*PROBAREELLES[l]/100))/(length(texte)*PROBAREELLES[l]/100);
	calculerKhi2:= khi2;
end;

function calculerFormeBigrammes(texte : Ansistring): Real;
	var	l, m : Char;
		forme : Real;
		effectifs : Bigrammes;
begin
	forme := 0;
	effectifs := compterBigrammes(texte);
	for l := 'A' to 'Z' do
	begin
		for m := 'A' to 'Z' do
			forme := forme + effectifs[l,m]*ln(PROBAREELLESBIG[l,m]/100);
	end;
	calculerFormeBigrammes:= forme
end;

function formeBigrammesBasique(n : LongWord): Real;
	var	l, m : Char;
		forme : Real;
begin
	forme := 0;
	for l := 'A' to 'Z' do
	begin
		for m := 'A' to 'Z' do
		begin
			forme := forme + n*(PROBAREELLESBIG[l,m]/100)*ln(PROBAREELLESBIG[l,m]/100);
		end;
	end;
	formeBigrammesBasique:= forme
end;

procedure echanger(var a : Char; var b : Char);
	var tmp : Char;
begin
	tmp := a;
	a := b;
	b := tmp
end;

procedure permuterDeuxLettres(var str : Ansistring);
	var i, j : LongWord;
begin
	repeat
		i := random(length(str) + 1);
		j := random(length(str) + 1);
	until ((i <> j) and (i <> 0) and (j <> 0));
	echanger(str[i], str[j])
end;

function cleAleatoire() : Ansistring;
	var i, j, n : Integer;
		c : Char;
		dejaLa : Boolean;
		res : Ansistring;
begin
	res := ALPHABET;
	for i := 1 to 26 do
	begin
		repeat
			dejaLa := false;
			n := random(26);
			c := Chr(ord('A') + n);
			for j := 1 to i - 1 do
			begin
				if c = res[j] then
					dejaLa := true; 
			end;
		until not(dejaLa);
		res[i] := c;
	end;	
	cleAleatoire:= res;
end;

function dechiffrerLettre(lettre : Char; cle : Ansistring) : Char;
	var pos, i : LongWord;
begin
	for i := 1 to 26 do
	begin
		if cle[i] = lettre then
			pos := i;
	end;
	dechiffrerLettre:= ALPHABET[pos]
end;

function dechiffrerTexte(texte : Ansistring; cle : Ansistring) : Ansistring;
	var i : LongWord;
		res : Ansistring;
begin
	res := '';
	for i := 1 to length(texte) do
	begin
		res := res + dechiffrerLettre(texte[i], cle);
	end;
	dechiffrerTexte:= res;
end;

procedure hillClimbing(texte : Ansistring; var cle : Ansistring; var formeMax : Real);
	var
		cletmp : Ansistring;
		forme : Real;
		cpt : LongWord;
begin
	cletmp := cle;
	formeMax := calculerFormeBigrammes(dechiffrerTexte(texte, cletmp));
	cpt := 0;
	while (cpt < 1000) do
	begin
		permuterDeuxLettres(cletmp);
		forme := calculerFormeBigrammes(dechiffrerTexte(texte, cletmp));
		if (forme > formeMax) then
		begin
			cpt := 0;
			formeMax := forme;
			cle := cletmp;
		end;
		cpt := cpt + 1;
	end;
end;

function importer(chemin : Ansistring) : Ansistring;
	var fichier : Text;
		res : Ansistring;
begin
	assign(fichier, chemin);
	reset(fichier);
	readln(fichier, res);
	close(fichier);
	importer := res
end;

procedure exporter(chemin : Ansistring; texte : Ansistring);
	var fichier : Text;
begin
	assign(fichier, chemin);
	rewrite(fichier);
	write(fichier, texte);
	close(fichier)
end;

	var res, texte : Ansistring;
		cle : Ansistring;
		forme, formeMax : Real;
		i : Integer;
begin
	randomize;
	texte := importer('cryptogramme.txt');
	writeln(calculerKhi2(dechiffrerTexte(texte, 'BERNOULIACDFGHJKMPQSTVWXYZ')));
	cle := cleAleatoire();
	writeln('Forme attendue : ', calculerFormeBigrammes(dechiffrerTexte(texte, 'BERNOULIACDFGHJKMPQSTVWXYZ')), #13#10);
	formeMax := calculerFormeBigrammes(dechiffrerTexte(texte, cle));
	i := 0;
	repeat
		i := i+1;
		hillClimbing(texte,cle,forme);
		if (forme > formeMax) then
		begin
			writeln('Itération ', i);
			formeMax := forme;
			res := dechiffrerTexte(texte, cle);
			writeln('Clé : ', cle);
			writeln('Cryptogramme « déchiffré » : ', res);
			writeln('Forme : ', forme, #13#10);
		end;
		if (i mod 100 = 0) then
			writeln('Itération ', i, #13#10);
		if (i mod 5000 = 0) then
			cle := cleAleatoire();
	until (formeMax >= (formeBigrammesBasique(length(texte))));
	exporter('resultat.txt', cle + #13#10 + res);
end.
