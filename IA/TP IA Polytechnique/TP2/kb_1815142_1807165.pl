% TP 2 - Base de connaissances - Adrien LOGUT Elliot SISTERON
%
%Enlève les warning pour prolog
:- discontiguous member/2.
:- discontiguous prop/3.

% Définition des classes
class(cours).
class(sujet).
class(etudiant).
class(programme).
class(langage).
class(institution).
class(orientation).

% Définition des sous classes
class(math).
class(physique).
class(programmation).
class(chimie).
class(stage).
class(projet).

subclass(math, sujet).
subclass(physique, sujet).
subclass(programmation, sujet).
subclass(chimie, sujet).
subclass(stage, sujet).
subclass(projet, sujet).

%Gestion des sous classes
%member(X,C2) :-
%	member(X,C1), 
%	subclass(C1,C2).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Question 1 : Liste des cours valides

valideChoixDeCours(Etudiant, ChoixDeCours):-
	valideChoixDeCoursAux(Etudiant, ChoixDeCours, ChoixDeCours).

valideChoixDeCoursAux(_, _, []).

valideChoixDeCoursAux(Etudiant, ChoixDeCours, [H|T]):-
	valideChoixDeCoursAux(Etudiant, ChoixDeCours, T),
	member(H,cours),
	valideCours(Etudiant, H, ChoixDeCours).

% Propriété qu'un cours soit valide
valideCours(Etudiant, Cours, ChoixDeCours):-
	prop(Etudiant, prealables_valides, Cours),
	corequisValide(Etudiant, ChoixDeCours, Cours).

% Propriété pour les prérequis
prop_liste(_, _, []).
% Vérifie qu'une liste d'objets satisfait une propriété
prop_liste(X, P, [H|T]):-
	prop(X, P, H),
	prop_liste(X, P, T).

% Vérifie qu'un cours valide bien les cours préables
prop(Etudiant, prealables_valides, Cours):-
	findall(CoursRequis, prop(Cours, requis, CoursRequis), ListeCoursPrealables),
	prop_liste(Etudiant, suivi, ListeCoursPrealables), 
	prop_liste(Etudiant, reussi, ListeCoursPrealables),
	verifCreditsAccumules(Etudiant, Cours).

%Crédits accumulés
genereCours(Etudiant, L):-
	findall(Cours, prop(Etudiant, reussi, Cours), L).

sommeCredit([], 0).
sommeCredit([H|T], C):-
	prop(H, credits, Valeur),
	sommeCredit(T, Reste),
	C is Valeur + Reste.

%Fonction utile pour mettre dans une liste
dansListe(X, [X|_]).
dansListe(X, [_|Y]):-
	dansListe(X,Y).

prop(Etudiant, credits_accumules, C):-
	genereCours(Etudiant, L),
	sommeCredit(L, C).

%Propriété pour la vérification si assez de crédits accumulés
verifCreditsAccumules(_, Cours):-
	\+ prop(Cours, besoin_credits, _).

verifCreditsAccumules(Etudiant, Cours):-
	prop(Cours, besoin_credits, C),
	prop(Etudiant, credits_accumules, C_accumul),
	X is C,
	Y is C_accumul,
	X =< Y.
%Propriété pour les corequis
corequisValide(Etudiant, ChoixDeCours, Cours):-
	findall(Corequis, prop(Cours, corequis, Corequis), L),
	corequisValide2(Etudiant, ChoixDeCours, L).

corequisValide2(_, _, []).

corequisValide2(Etudiant, ChoixDeCours, [H|T]):-
	dansListe(H, ChoixDeCours),
	corequisValide2(Etudiant, ChoixDeCours, T).

corequisValide2(Etudiant, ChoixDeCours, [H|T]):-
	prop(Etudiant, suivi, H),
	corequisValide2(Etudiant, ChoixDeCours, T).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Question 2 : Qualité
qualite(Etudiant, ListeDeCours):-
	valideChoixDeCours(Etudiant, ListeDeCours),
	sommeCredit(ListeDeCours, C),
	X is C,
	X >= 12.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Toute la base de donnée utile, Pour question 3 sauter à la ligne 388

% Liste des programmes
member(genieInfo, programme).
member(genieLog, programme).

%Liste orientation
member(securite, orientation).
member(multimedia, orientation).

% Liste des institutions
member(poly, institution).
member(mcgill, institution).
member(udem, institution).


% Liste des cours
member(inf1010, cours).
member(inf4215, cours).
member(inf8225, cours).
member(inf8703, cours).
member(log8430, cours).
member(log4420, cours).
member(log4715, cours).
member(inf3005, cours).
member(inf1005, cours).
member(inf1040, cours).
member(inf1500, cours).
member(inf1600, cours).
member(inf1995, cours).
member(inf2010, cours).
member(inf2610, cours).
member(inf2705, cours).
member(inf2990, cours).
member(inf3005, cours).
member(inf3405, cours).
member(inf3500, cours).
member(inf3610, cours).
member(inf3995, cours).
member(inf4410, cours).
member(inf4710, cours).
member(inf4420, cours).
member(log1000, cours).
member(log2410, cours).
member(log2810, cours).
member(mth1007, cours).
member(mth1101, cours).
member(mth1102, cours).
member(mth2302, cours).
member(phs1101, cours).
member(phs1102, cours).
member(ssh3201, cours).
member(ssh3501, cours).
member(phs4700, cours).
member(gbm1610, cours).
member(ele2305, cours).
member(inf4725, cours).

member(inf2565, cours).
member(inf4574, cours).
member(inf2222, cours).
member(mth2565, cours).
member(mth4574, cours).
member(mth2222, cours).

%Cours dispensés
prop(inf1010, dispensepar, poly).
prop(inf4215, dispensepar, poly).
prop(inf8225, dispensepar, poly).
prop(inf8703, dispensepar, poly).
prop(log8430, dispensepar, poly).
prop(log4420, dispensepar, poly).
prop(log4715, dispensepar, poly).
prop(inf3005, dispensepar, poly).
prop(inf1005, dispensepar, poly).
prop(inf1040, dispensepar, poly).
prop(inf1500, dispensepar, poly).
prop(inf1600, dispensepar, poly).
prop(inf1995, dispensepar, poly).
prop(inf2010, dispensepar, poly).
prop(inf2610, dispensepar, poly).
prop(inf2705, dispensepar, poly).
prop(inf2990, dispensepar, poly).
prop(inf3005, dispensepar, poly).
prop(inf3405, dispensepar, poly).
prop(inf3500, dispensepar, poly).
prop(inf3610, dispensepar, poly).
prop(inf3995, dispensepar, poly).
prop(inf4410, dispensepar, poly).
prop(inf4710, dispensepar, poly).
prop(inf4420, dispensepar, poly).
prop(log1000, dispensepar, poly).
prop(log2410, dispensepar, poly).
prop(log2810, dispensepar, poly).
prop(mth1007, dispensepar, poly).
prop(mth1101, dispensepar, poly).
prop(mth1102, dispensepar, poly).
prop(mth2302, dispensepar, poly).
prop(phs1101, dispensepar, poly).
prop(phs1102, dispensepar, poly).
prop(ssh3201, dispensepar, poly).
prop(ssh3501, dispensepar, poly).
prop(phs4700, dispensepar, poly).
prop(gbm1610, dispensepar, poly).
prop(ele2305, dispensepar, poly).
prop(inf4725, dispensepar, poly).

prop(inf2565, dispensepar, udem).
prop(inf4574, dispensepar, udem).
prop(inf2222, dispensepar, udem).

prop(mth2565, dispensepar, mcgill).
prop(mth4574, dispensepar, mcgill).
prop(mth2222, dispensepar, mcgill).




% Nombre de crédits offerts par cours
prop(inf1010, credits, 3).
prop(inf4215, credits, 3).
prop(inf8225, credits, 3).
prop(inf8703, credits, 3).
prop(log8430, credits, 3).
prop(log4420, credits, 3).
prop(log4715, credits, 3).
prop(inf3005, credits, 0).
prop(inf1005, credits, 3).
prop(inf1040, credits, 3).
prop(inf1500, credits, 3).
prop(inf1600, credits, 3).
prop(inf1995, credits, 4).
prop(inf2010, credits, 3).
prop(inf2610, credits, 3).
prop(inf2705, credits, 3).
prop(inf2990, credits, 3).
prop(inf3005, credits, 1).
prop(inf3405, credits, 3).
prop(inf3500, credits, 3).
prop(inf3610, credits, 3).
prop(inf3995, credits, 4).
prop(inf4410, credits, 3).
prop(inf4710, credits, 3).
prop(inf4420, credits, 3).
prop(log1000, credits, 3).
prop(log2410, credits, 3).
prop(log2810, credits, 3).
prop(mth1007, credits, 2).
prop(mth1101, credits, 2).
prop(mth1102, credits, 2).
prop(mth2302, credits, 3).
prop(phs1101, credits, 3).
prop(phs1102, credits, 3).
prop(phs4700, credits, 3).
prop(gbm1610, credits, 3).
prop(ele2305, credits, 3).
prop(inf4725, credits, 3).

%% Sujets abordables
member(analyse, math).
member(algebre, math).
member(web, programmation).
member(jeuxvideo, programmation).
member(ia, programmation).
member(securite, programmation).
member(procedural, programmation).
member(objet, programmation).
member(ingenierie, programmation).
member(systeme, programmation).
member(algo, programmation).
member(graphisme, programmation).
member(kernel, programmation).
member(comm, programmation).
member(reseaux, programmation).
member(multimedia, programmation).
member(stage, stage).
member(conception, programmation).
member(probabilite, math).
member(mecaingenieur, physique).
member(electromag, physique).
member(physique, physique).
member(biochimie, chimie).
member(semiconduc, physique).
member(communication, programmation).
member(architecture, programmation).
member(projet, projet).
member(structures, programmation).

%Sont-ce des projets?
projet(inf2990).
projet(inf3995).

%Langages de programmation
member(c, langage).
member(cpp, langage).
member(csharp, langage).
member(java, langage).
member(javascript, langage).
member(matlab, langage).
member(assembleur, langage).
member(html, langage).
member(css, langage).
member(python, langage).
member(prolog, langage).

%Cours requis
prop(inf1010, requis, inf1005).
prop(inf1600, requis, inf1005).
prop(inf1600, requis, inf1500).
prop(inf1995, requis, inf1040).
prop(inf2010, requis, inf1010).
prop(inf2610, requis, inf1010).
prop(inf2610, requis, inf1600).
prop(inf2705, requis, inf2010).
prop(inf2705, requis, mth1007).
prop(inf2990, requis, inf1995).
prop(inf2990, requis, inf2010).
prop(inf2990, requis, log2410).
prop(inf3500, requis, inf1600).
prop(inf3610, requis, inf2610).
prop(inf3610, requis, inf3500).
prop(inf3710, requis, inf2010).
prop(inf3995, requis, inf3405).
prop(inf3995, requis, inf3610).
prop(inf4410, requis, inf3405).
prop(inf4420, requis, inf2610).
prop(inf4420, requis, inf3405).
prop(inf4710, requis, inf1010).
prop(inf8225, requis, log2810).
prop(inf8225, requis, mth2302).
prop(log1000, requis, inf1005).
prop(log2410, requis, log1000).
prop(log2410, requis, inf1010).
prop(mth1102, requis, mth1101).
prop(phs4700, requis, mth1210).
prop(phs4700, requis, mth1102).
prop(ele2305, requis, phs1102).
prop(inf4725, requis, inf1010).


%Cours corequis
prop(mth1102, corequis, mth1107).
prop(mth1102, corequis, phs1102).
prop(inf1995, corequis, inf1600).
prop(inf1995, corequis, log1000).

%Cours credits accumulés
prop(log4420, besoin_credits, 9).


%Etudiants
member(adrien, etudiant).
member(elliot, etudiant).

%Cours reussis
prop(adrien, reussi, inf1010).
prop(adrien, reussi, log4715).
prop(adrien, reussi, mth1101).
prop(adrien, reussi, log2810).
prop(adrien, reussi, mth2302).

prop(elliot, reussi, inf1010).
prop(elliot, reussi, log4420).
prop(elliot, reussi, inf2990).
prop(elliot, reussi, inf2565).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Question 3 : Sujets abordés
prop(inf1010, aborde, objet).
prop(inf4215, aborde, ia).
prop(inf8225, aborde, ia).
prop(inf8225, aborde, probabilite).
prop(inf8703, aborde, multimedia).
prop(log8430, aborde, conception).
prop(log4420, aborde, web).
prop(log4715, aborde, jeuxvideo).
prop(inf3005, aborde, communication).
prop(inf1005, aborde, procedural).
prop(inf1040, aborde, ingenierie).
prop(inf1500, aborde, systeme).
prop(inf1600, aborde, architecture).
prop(inf1995, aborde, projet).
prop(inf2010, aborde, algo).
prop(inf2610, aborde, kernel).
prop(inf2705, aborde, graphisme).
prop(inf2990, aborde, projet).
prop(inf3005, aborde, communication).
prop(inf3405, aborde, reseaux).
prop(inf3500, aborde, conception).
prop(inf3610, aborde, systeme).
prop(inf3995, aborde, projet).
prop(inf3995, aborde, conception).
prop(inf4410, aborde, systeme).
prop(inf4710, aborde, multimedia).
prop(inf4420, aborde, securite).
prop(log1000, aborde, ingenierie).
prop(log2410, aborde, conception).
prop(log2810, aborde, structures).
prop(mth1007, aborde, algebre).
prop(mth1101, aborde, analyse).
prop(mth1102, aborde, analyse).
prop(mth2302, aborde, probabilite).
prop(phs1101, aborde, mecaingenieur).
prop(phs1102, aborde, electromag).
prop(phs4700, aborde, physique).
prop(gbm1610, aborde, biochimie).
prop(ele2305, aborde, semiconduc).
prop(inf4725, aborde, multimedia).

prop(inf2565, aborde, ia).
prop(inf4574, aborde, multimedia).
prop(inf2222, aborde, securite).

prop(mth2565, aborde, algebre).
prop(mth4574, aborde, analyse).
prop(mth2222, aborde, probabilite).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Question 4 : Utilisation des Langages

prop(inf1010, utilise, c).
prop(inf4215, utilise, python).
prop(inf4215, utilise, prolog).
prop(inf8225, utilise, python).
prop(inf8225, utilise, matlab).
prop(inf8703, utilise, cpp).
prop(log8430, utilise, java).
prop(log4420, utilise, javascript).
prop(log4420, utilise, html).
prop(log4420, utilise, css).
prop(log4715, utilise, csharp).
prop(inf1005, utilise, c).
prop(inf1040, utilise, cpp).
prop(inf1500, utilise, c).
prop(inf1600, utilise, c).
prop(inf1995, utilise, c).
prop(inf2010, utilise, c).
prop(inf2610, utilise, c).
prop(inf2610, utilise, assembleur).
prop(inf2705, utilise, cpp).
prop(inf2990, utilise, cpp).
prop(inf3405, utilise, c).
prop(inf3500, utilise, cpp).
prop(inf3610, utilise, c).
prop(inf3995, utilise, cpp).
prop(inf4410, utilise, c).
prop(inf4710, utilise, cpp).
prop(inf4420, utilise, cpp).
prop(log1000, utilise, cpp).
prop(log2410, utilise, cpp).
prop(log2810, utilise, cpp).
prop(mth1007, utilise, matlab).
prop(mth1101, utilise, matlab).
prop(mth1102, utilise, matlab).
prop(mth2302, utilise, matlab).
prop(phs1101, utilise, matlab).
prop(phs1102, utilise, matlab).
prop(phs4700, utilise, cpp).
prop(inf4725, utilise, matlab).

prop(inf2565, utilise, cpp).
prop(inf4574, utilise, cpp).
prop(inf2222, utilise, cpp).

prop(mth2565, utilise, matlab).
prop(mth4574, utilise, matlab).
prop(mth2222, utilise, matlab).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Question 5 : Programme offre cours
member(genieInfo, offre, inf4215).
member(genieInfo, offre, inf8225).
member(genieInfo, offre, inf8703).
member(genieInfo, offre, log8430).
member(genieInfo, offre, log4420).
member(genieInfo, offre, log4715).
member(genieInfo, offre, inf3005).
member(genieInfo, offre, inf1005).
member(genieInfo, offre, inf1040).
member(genieInfo, offre, inf1500).
member(genieInfo, offre, inf1600).
member(genieInfo, offre, inf1995).
member(genieInfo, offre, inf2010).
member(genieInfo, offre, inf2610).
member(genieInfo, offre, inf2705).
member(genieInfo, offre, inf2990).
member(genieInfo, offre, inf3005).
member(genieInfo, offre, inf3405).
member(genieInfo, offre, inf3500).
member(genieInfo, offre, inf3610).
member(genieInfo, offre, inf3995).
member(genieInfo, offre, inf4410).
member(genieInfo, offre, inf4710).
member(genieInfo, offre, inf4420).
member(genieInfo, offre, log1000).
member(genieInfo, offre, log2410).
member(genieInfo, offre, log2810).
member(genieInfo, offre, mth1007).
member(genieInfo, offre, mth1101).
member(genieInfo, offre, mth1102).
member(genieInfo, offre, mth2302).
member(genieInfo, offre, phs1101).
member(genieInfo, offre, phs1102).
member(genieInfo, offre, ssh3201).
member(genieInfo, offre, ssh3501).
member(genieInfo, offre, phs4700).
member(genieInfo, offre, gbm1610).
member(genieInfo, offre, ele2305).
member(genieInfo, offre, inf4725).
member(genieLog, offre, log8430).
member(genieLog, offre, log4420).
member(genieLog, offre, log4715).
member(genieLog, offre, log1000).
member(genieLog, offre, log2410).
member(genieLog, offre, log2810).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Question 6 : Propriété classes inversées
classe_inversee(inf4215).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Question 7 et 8 : Cours suivis et orientation et obligatoire etc...
prop(adrien, suivi, mth1107).
prop(adrien, suivi, inf4725).
prop(adrien, suivi, log4420).
prop(adrien, suivi, mth1101).
prop(adrien, obligatoire, inf1010).
prop(adrien, obligatoire, log4715).
prop(adrien, obligatoire, mth1101).
prop(adrien, obligatoire, mth1102).
prop(adrien, obligatoire, mth1107).
prop(adrien, obligatoire, inf4725).
prop(adrien, obligatoire, log4420).
prop(adrien, optionnel, mth1101).

prop(adrien, est_inscrit_orientation, multimedia).


prop(elliot, suivi, log4715).
prop(elliot, suivi, gbm1610).
prop(elliot, suivi, ele2305).
prop(elliot, suivi, inf4410).
prop(elliot, obligatoire, log4715).
prop(elliot, obligatoire, gbm1610).
prop(elliot, obligatoire, ele2305).
prop(elliot, obligatoire, inf1010).
prop(elliot, obligatoire, log4420).
prop(elliot, obligatoire, inf2990).
prop(elliot, optionnel, inf4410).

prop(Etudiant, suivi, Cours):-
	prop(Etudiant, reussi, Cours).

prop(Etudiant, suivi_obligatoire, Cours):-
	prop(Etudiant, suivi, Cours),
	prop(Etudiant, obligatoire, Cours).

prop(Etudiant, suivi_optionnel, Cours):-
	prop(Etudiant, suivi, Cours),
	prop(Etudiant, optionnel, Cours).

prop(Etudiant, suivi_projet, Cours):-
	prop(Etudiant, suivi, Cours),
	projet(Cours).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Question 9 : Equivalence
prop(Etudiant, equivalence, Cours):-
	prop(Cours, aborde, Sujet),
	prop(Cours2, aborde, Sujet),
	Cours \= Cours2,
	prop(Cours, dispensepar, Ecole1),
	prop(Cours2, dispensepar, Ecole2),
	Ecole1 \= Ecole2,
	prop(Etudiant, reussi, Cours2).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%question 10 : En echange ?
en_echange(adrien).

%Liste des cours en echange
accepte_echange(inf1010).
accepte_echange(inf4215).
accepte_echange(inf8225).
accepte_echange(inf8703).
accepte_echange(log8430).
accepte_echange(log4420).
accepte_echange(log4715).
accepte_echange(inf3005).
accepte_echange(inf1005).
accepte_echange(inf1040).
accepte_echange(inf1500).
accepte_echange(inf1600).
accepte_echange(inf1995).
accepte_echange(inf2010).
accepte_echange(inf2610).
accepte_echange(inf2705).
accepte_echange(inf2990).
accepte_echange(inf3005).
accepte_echange(inf3405).
accepte_echange(inf3500).
accepte_echange(inf3610).
accepte_echange(inf3995).
accepte_echange(inf4410).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
