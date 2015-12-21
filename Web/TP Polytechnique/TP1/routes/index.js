var express = require('express');
var router = express.Router();

var disciplines = ['Camouflage','Hunting','Sixth Sense','Tracking','Healing','Weaponskill', 'Mindshield', 'Mindblast', 'Animal Kinship', 'Mind Over Matter'];
var backpack_items = ['Potion of Laumspur', 'Special Rations'];
var special_items = ['Padded Leather Waistcoat'];
var weapons = ['Sword','Short Sword','Spear','Mace','Warhammer','Axe','Quarterstaff','Broadsword'];
var items = ['Sword','Short Sword','Spear','Mace','Warhammer','Axe','Quarterstaff','Broadsword', 'Padded Leather Waistcoat', 'Potion of Laumspur', 'Special Rations'];
var combats = [];
var player_backpack = [];
var player_special_items = [];
var player_weapons = [];
var player_disciplines = [];
var combat_skill = 0;
var endurance = 0;
var gold = 0;
var name = 'unknown';
var discipline = 'unknown';
var item1 = 'unknown';
var item2 = 'unknown';

var enemies_endurance = {};
var enemies_combat_skill = {};
enemies_endurance['Baknar'] = 19;
enemies_combat_skill['Baknar'] = 30;


var descriptions = {};
var images = {};
descriptions['Camouflage'] = 'This Discipline enables a Kai Lord to blend in with his surroundings. In the countryside, he can hide undetected among trees and rocks and pass close to an enemy without being seen. In a town or city, it enables him to look and sound like a native of that area, and can help him to find shelter or a safe hiding place.';
descriptions['Hunting'] = 'This skill ensures that a Kai Lord will never starve in the wild. He will always be able to hunt for food for himself except in areas of wasteland and desert. You are aware that most of Kalte is an icy desert and that opportunities for successful hunting will not arise. But this skill is still very useful for it also enables a Kai Lord to move with great speed and dexterity.';
descriptions['Sixth Sense'] = 'This skill may warn a Kai Lord of imminent danger. It may also reveal the true purpose of a stranger or strange object encountered in your adventure.';
descriptions['Tracking'] = 'This skill enables a Kai Lord to make the correct choice of a path in the wild, to discover the location of a person or object in a town or city and to read the secrets of footprints or tracks.';
descriptions['Healing'] = 'This Discipline can be used to restore ENDURANCE points lost in combat. If you possess this skill you may restore 1 ENDURANCE point to your total for every numbered section of the book you pass through in which you are not involved in combat. (This is only to be used after your ENDURANCE has fallen below its original level.) Remember that your ENDURANCE cannot rise above its original level.';
descriptions['Weaponskill'] = 'Upon entering the Kai Monastery, each initiate is taught to master one type of weapon. A random weapon will be assigned to you as your master weapon. The fact that you are skilled with a weapon does not mean you set out on the adventure carrying that particular weapon. However, you will have opportunities to acquire weapons in the course of your adventures. You cannot carry more than 2 weapons.'
descriptions['Mindshield'] = 'Vonotar and many of the evil creatures under his command have the ability to attack you using their Mindforce. The Kai Discipline of Mindshield prevents you from losing any ENDURANCE points when subjected to this form of attack.';
descriptions['Mindblast'] = 'This enables a Kai Lord to attack an enemy using the force of his mind. It can be used at the same time as normal combat weapons and adds two extra points to your COMBAT SKILL. Not all the creatures encountered on this adventure will be harmed by Mindblast. You will be told if a creature is immune.';
descriptions['Animal Kinship'] = 'This skill enables a Kai Lord to communicate with some animals and to be able to guess the intentions of others.';
descriptions['Mind Over Matter'] = 'Mastery of this Discipline enables a Kai Lord to move small objects with his powers of concentration.';
descriptions['Sword'] = 'Weapon';
descriptions['Short Sword'] = 'Weapon';
descriptions['Spear'] = 'Weapon';
descriptions['Mace'] = 'Weapon';
descriptions['Warhammer'] = 'Weapon';
descriptions['Axe'] = 'Weapon';
descriptions['Quarterstaff'] = 'Weapon';
descriptions['Broadsword'] = 'Weapon';
descriptions['Padded Leather Waistcoat'] = 'Special item - This adds 2 ENDURANCE points to your total.';
descriptions['Potion of Laumspur'] = 'Backpack item - This restores 4 ENDURANCE points to your total when swallowed after combat. There is only enough for one dose.';
descriptions['Special Rations'] = 'Meal - This counts as one meal.';
images['Sword'] = 'sword.png';
images['Short Sword'] = 'ssword.png';
images['Spear'] = 'spear.png';
images['Mace'] = 'mace.png';
images['Axe'] = 'axe.png';
images['Warhammer'] = 'warhammr.png';
images['Quarterstaff'] = 'qstaff.png';
images['Broadsword'] = 'bsword.png';
images['Padded Leather Waistcoat'] = 'plw.png';
images['Potion of Laumspur'] = 'potion.png';
images['Special Rations'] = 'food.png';
images['Baknar'] = 'baknar.png';



/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Lone Wolf : The Caverns of Kalte' });
});

router.get('/help', function(req, res, next) {
  res.render('help', { title: 'Help', disciplines:disciplines, items:items, descriptions:descriptions, images:images });
});

router.get('/create', function(req, res, next) {
  res.render('create', { title: 'Create your player' , disciplines:disciplines, items:items });
});

router.get('/combat:valeur', function(req, res, next) {
  var enemy_name = req.params.valeur;
  
  // TODO: update of the fight values (for fight logic)

  res.render('combat', { title: 'Combat' , combat_skill:combat_skill, endurance:endurance, gold:gold, name:name,
    player_disciplines:player_disciplines, player_weapons:player_weapons, player_backpack:player_backpack, player_special_items:player_special_items,
    combats:combats, enemy_name:enemy_name, enemies_combat_skill:enemies_combat_skill, enemies_endurance:enemies_endurance, images:images });
});

router.get('/jeu/:valeur', function(req, res, next) {
  var page = req.params.valeur;
  res.render('page' + page, { title: 'Page ' + page, combat_skill:combat_skill, endurance:endurance, gold:gold, name:name,
    player_disciplines:player_disciplines, player_weapons:player_weapons, player_backpack:player_backpack, player_special_items:player_special_items,
    combats:combats });
});

router.post('/create', function (req, res) {
    combats = [];
    player_backpack = [];
    player_special_items = [];
    player_weapons = [];
    player_disciplines = [];

    combat_skill = Math.floor((Math.random() * 10) + 10);
    endurance = Math.floor((Math.random() * 10) + 20);
    gold = Math.floor((Math.random() * 10) + 10);

    name = req.body.name;
    discipline = req.body.discipline;

    if(weapons.indexOf(req.body.item1) >= 0)
      player_weapons.push(req.body.item1);
    else if(special_items.indexOf(req.body.item1) >= 0)
      player_special_items.push(req.body.item1)
    else if(backpack_items.indexOf(req.body.item1) >= 0)
      player_backpack.push(req.body.item1)
    if(weapons.indexOf(req.body.item2) >= 0)
      player_weapons.push(req.body.item2);
    else if(special_items.indexOf(req.body.item2) >= 0)
      player_special_items.push(req.body.item2)
    else if(backpack_items.indexOf(req.body.item2) >= 0)
      player_backpack.push(req.body.item2)

    player_disciplines.push(req.body.discipline1);
    player_disciplines.push(req.body.discipline2);
    player_disciplines.push(req.body.discipline3);
    player_disciplines.push(req.body.discipline4);
    player_disciplines.push(req.body.discipline5);

    res.redirect('/jeu/1');
});

module.exports = router;
