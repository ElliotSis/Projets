var express = require('express');
var u = require("underscore");
var fs = require('fs');


var constantes = require('../lib/constantes.js');
var pagesJeu = require('../lib/pagesJeu.js');
var Joueur = require("../modele/joueur.js");
var Avancement = require("../modele/avancement.js");

var router = express.Router();

/**
 * Ce service web envoie la représentation de tous les joueurs dans la base de données.
 */
router.get('/joueur/tous', function(req, res) {
    Joueur.find(function(err, joueurs) {
        if (err)
            res.send(err);

        res.json(joueurs);
    });
});

/**
 * Ce service web envoie la représentation d'un joueur de la base de données passé en paramètre.
 */
router.get('/joueur/:idJoueur', function(req, res) {
    var id = req.params.idJoueur;
    Joueur.findById(id, function(err, joueur) {
        if (err)
            res.send(err);

        res.json(joueur);
    });
});

/**
 * Ce service web envoie la représentation de tous les avancements dans la base de données.
 */
router.get('/avancement/tous', function(req, res) {
    Avancement.find(function(err, avancements) {
        if (err)
            res.send(err);

        res.json(avancements);
    });
});

/**
 * Ce service web envoie la représentation d'un avancement de la base de données passé en paramètre.
 */
router.get('/avancement/:idAvancement', function(req, res) {
    var id = req.params.idAvancement;
    Avancement.findById(id, function(err, avancement) {
        if (err)
            res.send(err);

        res.json(avancement);
    });
});

/**
 * Ce service web supprime le joueur de la base de donnée.
 */
router.delete('/joueur/:idJoueur', function(req, res) {
    var id = req.params.idJoueur;
    Joueur.remove({
        _id: id
    }, function(err, joueur) {
        if (err)
            res.send(err);
        res.json(joueur);
    });
});

/**
 * Ce service web supprime l'avancement de la base de donnée.
 */
router.delete('/avancement/:idAvancement', function(req, res) {
    var id = req.params.idAvancement;
    Avancement.remove({
        _id: id
    }, function(err, avancement) {
        if (err)
            res.send(err);
        res.json(avancement);
    });
});

/**
 * Ce service web modifie la représentation d'un joueur de la base de données passé en paramètre.
 */
router.put('/joueur/:idJoueur', function(req,res,next){
    var id = req.params.idJoueur;
    Joueur.findByIdAndUpdate(id, req.body, function(err){
        if(err)
            res.send(err);
        res.json("Succès");
    });
});

/**
 * Ce service web modifie la représentation d'un avancement de la base de données passé en paramètre.
 */
router.put('/avancement/:idAvancement', function(req,res,next){
    var id = req.params.idAvancement;
    Avancement.findByIdAndUpdate(id, req.body, function(err){
        if(err)
            res.send(err);
        res.json("Succès");
    });
});

/**
 * Ce service web envoie la représentation du joueur.
 */
router.get('/joueur', function(req, res) {
    res.json(req.session.joueur);
});

/**
 * Ce service web envoie la représentation d'une page de jeu.
 */
router.get('/page/:pageId', function(req, res, next) {
    var id = req.params.pageId;
    var pageJeu = "page/" + id;

    var sections = u.chain(fs.readdirSync('views/page'))
        // On récupère les sous-sections de la page demandée
        .filter(function(file) { return file.indexOf(id + '_') == 0; })
        // On convertit chaque sous-section vers une route valide de notre
        // site afin de récupérer la sous-section
        .map(function(file) {
            return '/page' + id + "/" +
                file.replace('.jade', '').replace(id + '_', '');
        })

    // On récupère les pages qu'on accéder à partir de la page actuelle.
    var pageDecision = u.find(pagesJeu.cheminJeu, function(page) {
        return page.id == id;
    });

    res.json({
        id: id,
        sections: sections,
        next: pageDecision.next
    });
});

/**
 * Ce service web envoie la représentation d'une sous-section d'une page
 * de jeu.
 */
router.get('/page/:pageId/:sectionId', function(req, res) {
    var id = req.params.pageId;
    var section = req.params.sectionId;
    var nextSectionNum = parseInt(section) + 1;

    var nextSectionPage = 'views/page/' + id + "_" + nextSectionNum + ".jade";
    var nextSection = fs.existsSync(nextSectionPage) ? "/page/" + id + "/" + nextSectionNum : "";

    res.render('page/' + id + "_" + section, function (err, html) {
        res.json({
            id: id,
            section: section,
            content: html,
            next: nextSection
        });
    });
});

/**
 * Service Web qui retourne l'information d'une page qui contient un choix
 * aléatoire.
 */
router.get('/choixAleatoire/:pageId', function(req, res) {
    var id = req.params.pageId;
    var choix = u.find(pagesJeu.pagesAleatoire, function(page) {
        return page.id == id;
    });

    // Si la page n'a pas de décision aléatoire, on retourne un JSON vide.
    if (choix == undefined) {
        res.json({});
    } else {
        var joueur = req.session.joueur;
        choix.value = choix.f(joueur);
        res.json(choix);
    }
});

/*
 * Ce service web envoie le JSON d'une ronde de combat entre un monstre et
 * le joueur. On envoie l'endurance et l'habilete de chacun.
 */
router.get('/:enduranceJoueur/:habileteJoueur/:enduranceMonstre/:habileteMonstre', function(req, res) {
    var ej = req.params.enduranceJoueur;
    var hj = req.params.habileteJoueur;
    var em = req.params.enduranceMonstre;
    var hm = req.params.habileteMonstre;

    // Calcul du quotient d'attaque
    var qa = hj - hm;
    if (qa < -11) {
        qa = -11;
    } else if (qa > 11) {
        qa = 11;
    }
    // Relation entre l'index du tableau et le quotient d'attaque.
    var indexQa = (qa >= 0) ? Math.ceil(qa / 2) + 7 : Math.floor(qa / 2) + 6;

    var chiffreAleatoire = u.random(0, 9);

    // On obtient la bonne case du tableau de combat
    var combat = TableCombat(ej,em)[indexQa][chiffreAleatoire];

    // On retourne les informations sur la ronde de combat
    res.json({
        quotientAttaque: qa,
        chiffreAleatoire: chiffreAleatoire,
        degatJoueur: combat.degatJoueur,
        degatEnnemi: combat.degatEnnemi
    })
});

// Table de combat qui retourne les dégâts causés sur le joueur et le monstre.
// @param ej Endurance joueur
// @param em Endurance monstre
var TableCombat = function(ej, em) { return [
[lrc(6,0), lrcmj(ej), lrcmj(ej), lrc(0,8), lrc(0,8), lrc(1,7), lrc(2,6), lrc(3,5), lrc(4,4), lrc(5,3)], // index 0, QA -11 et -
[lrc(7,0), lrcmj(ej), lrc(0,8), lrc(0,7), lrc(1,7), lrc(2,6), lrc(3,6), lrc(4,5), lrc(5,4), lrc(6,3)], // index 1, QA -10 et -9
[lrc(8,0), lrc(0,8), lrc(0,7), lrc(1,6), lrc(2,6), lrc(3,5), lrc(4,5), lrc(5,4), lrc(6,3), lrc(7,2)], // index 2, QA -8 et -7
[lrc(9,0), lrc(0,6), lrc(1,6), lrc(2,5), lrc(3,5), lrc(4,4), lrc(5,4), lrc(6,3), lrc(7,2), lrc(8,0)], // index 3, QA -6 et -5
[lrc(10,0), lrc(1,6), lrc(2,5), lrc(3,5), lrc(4,4), lrc(5,4), lrc(6,3), lrc(7,2), lrc(8,1), lrc(9,0)], // index 4, QA -4 et -3
[lrc(11,0), lrc(2,5), lrc(3,5), lrc(4,4), lrc(5,4), lrc(6,3), lrc(7,2), lrc(8,2), lrc(9,1), lrc(10,0)], // index 5, QA -2 et -1
[lrc(12,0), lrc(3,4), lrc(4,4), lrc(5,4), lrc(6,3), lrc(7,2), lrc(8,2), lrc(9,1), lrc(10,0), lrc(11,0)], // index 6, QA 0
[lrc(12,0), lrc(3,5), lrc(4,4), lrc(5,4), lrc(6,3), lrc(7,2), lrc(8,2), lrc(9,1), lrc(10,0), lrc(11,0)], // index 7, QA 1 et 2
[lrc(14,0), lrc(4,5), lrc(5,4), lrc(6,3), lrc(7,3), lrc(8,2), lrc(9,2), lrc(10,1), lrc(11,0), lrc(12,0)], // index 8, QA 3 et 4
[lrc(16,0), lrc(5,4), lrc(6,3), lrc(7,3), lrc(8,2), lrc(9,2), lrc(10,2), lrc(11,1), lrc(12,0), lrc(14,0)], // index 9 QA 5 et 6
[lrc(18,0), lrc(6,4), lrc(7,3), lrc(8,3), lrc(9,2), lrc(10,2), lrc(11,1), lrc(12,0), lrc(14,0), lrc(16,0)], // index 10 QA 7 et 8
[lrcmm(em), lrc(7,4), lrc(8,3), lrc(9,2), lrc(10,2), lrc(11,2), lrc(12,1), lrc(14,0), lrc(16,0), lrc(18,0)], // index 11 QA 9 et 10
[lrcmm(em), lrc(8,3), lrc(9,3), lrc(10,2), lrc(11,2), lrc(12,2), lrc(14,1), lrc(16,0), lrc(18,0), lrcmm(em)], // index 12 QA 11 et +
[lrcmm(em), lrc(9,3), lrc(10,2), lrc(11,2), lrc(12,2), lrc(14,1), lrc(16,1), lrc(18,0), lrcmm(em), lrcmm(em)]
];
}

// Lancer résultat combat.
// @param e Dégât ennemi
// @param j Dégât joueur
function lrc(e, j) { return { degatEnnemi: e, degatJoueur: j }; }
// Mort instantanné du joueur
function lrcmj(enduranceJoueur) {
    return { degatEnnemi: 0, degatJoueur: enduranceJoueur };
}
// Mort instantanné du monstre
function lrcmm(enduranceMonstre) {
    return { degatEnnemi: enduranceMonstre, degatJoueur: 0 };
}

module.exports = router;
