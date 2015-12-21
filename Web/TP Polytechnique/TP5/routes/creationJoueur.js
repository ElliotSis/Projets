var express = require('express');
var rest = require('restler');
var u = require("underscore");
var constantes = require('../lib/constantes.js')
var router = express.Router();

var Joueur = require('../models/joueur');
var Avancement = require('../models/avancement');
var apiPlayer = require('./api/joueurs.js');

// GET page de création du joueur.
router.get('/creationJoueur', function (req, res, next) {
  var send = false;
    Joueur.find({}, function (err, joueurs) {
        if (joueurs) {
            res.render('creationJoueur', {
                c: constantes,
                erreursMsg: [],
                joueurs: joueurs
            });
        }
        else if(err){
          res.send(err);
        }
    });
});

// POST page de création du joueur
router.post('/jeu/1', function(req, res) {
    var erreursMsg = [];

    // Récupération des données du formulaire
    var name = (req.body.pseudo);
    var disciplines = (req.body.discipline) ? [].concat(req.body.discipline) : [];
    var armes = (req.body.arme) ? [].concat(req.body.arme) : [];
    var objets = (req.body.objet) ? [].concat(req.body.objet) : [];
    var objetsSpeciaux = (req.body.objetSpecial) ? [].concat(req.body.objetSpecial) : [];
   
    // Traitement des disciplines choisies
    var NB_DISCIPLINE = 5;
    if (disciplines.length < NB_DISCIPLINE || disciplines.length > NB_DISCIPLINE) {
        erreursMsg.push("Vous devez choisir EXACTEMENT " + NB_DISCIPLINE + " disciplines Kai.");
    }

    // Traitement des armes choisies
    if (!u.contains(disciplines, "Maitrise Armes") && armes.length > 1) {
        erreursMsg.push("Vous ne pouvez pas choisir une arme si vous ne maîtriser pas la discipline de Maîtrise des Armes.");
    }

    // Traitement des objets choisis
    var NB_OBJET = 2;
    var nbObjetsChoisis = armes.length + objets.length + objetsSpeciaux.length;
    if (nbObjetsChoisis < 2 || nbObjetsChoisis > 2) {
        erreursMsg.push("Vous devez choisir EXACTEMENT " + NB_OBJET + " objets.");
    }

    // S'il y au moins une erreur, on revient à la page de création avec la
    // liste d'erreurs. Sinon, on se dirige vers la 1ere page de l'histoire.
    if (u.isEmpty(erreursMsg)) {
        var joueur = new Joueur;
        joueur.pseudo = name;
        joueur.habileteBase = u.random(10, 19);
        joueur.enduranceBase = u.random(20, 29);
        joueur.pieceOr = u.random(10, 19);
        joueur.disciplines = disciplines;
        joueur.armes = armes;
        joueur.objets = objets;
        joueur.objetsSpeciaux = objetsSpeciaux;
        joueur.habiletePlus = habiletePlus(joueur);
        joueur.endurancePlus = endurancePlus(joueur);
        joueur.page_av = 1;
        joueur.section_av = 1;

        // On ajoute le joueur dans la session
        joueur.save(function(err, joueur) {
            if (err) {
                res.send(err);
            } else {
                rest.post('http://localhost:3000/api/joueurs/avancement/' + joueur.id)
                .on('complete', function(data, response) {
                    console.log(response);
                });
                req.session.joueur = joueur;
                req.session.follow = false;
                res.redirect('/jeu/1');
            }
        });
    } else {
        res.render('creationJoueur', {
            c: constantes,
            erreursMsg: erreursMsg
        });
    }
});

//POST continuer histoire du pseudo donné
router.post('/jeu/continue',function(req,res){

    var id_player = req.body.playerSelect;
    req.session.currentId = id_player;
    if (id_player) {
	    Avancement.findOne({joueurId: id_player}, function(err, avancement) {
		if (err) {
		    res.send(err);
		} else if (avancement) {
                    req.session.pageId = avancement.pageId;
                    req.session.follow = true;
                    var path = '/jeu/' + avancement.pageId;
		    res.redirect(path);
		} else {
		    res.json({});
		}
	    });
    }

 
});


/**
 * On calcul les points d'habiletes du joueur en fonction de ses disciplines
 * et de ses objets.
 *
 * @param joueur Joueur du jeu
 * @return Habilete calculer en fonction du joueur
 */
function habiletePlus(joueur) {
    var habilete = joueur.habileteBase;
    if (u.contains(joueur.disciplines, constantes.discipline.MAITRISE_ARMES) && !u.isEmpty(joueur.armes)) {
        habilete = joueur.habileteBase + 2;
    } else {
        habilete = joueur.habileteBase - 4;
    }
    return habilete;
}

/**
 * On calcul les points d'endurance du joueur en fonction de ses disciplines
 * et de ses objets.
 *
 * @param joueur Joueur du jeu
 * @return Endurance calculée en fonction du joueur
 */
function endurancePlus(joueur) {
    var endurance = joueur.enduranceBase;
    if (u.contains(joueur.objetsSpeciaux, constantes.objetSpecial.GILET_CUIR_MARTELE)) {
        endurance = joueur.enduranceBase + 2;
    }
    return endurance;
}

module.exports = router;

