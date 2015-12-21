// Init
var session = require("express-session");
var express = require("express");
var router = express.Router();
var app = express();
module.exports = router;

app.use(session({
  secret: 'secreetttt',
  resave: false,
  saveUninitialized: true
}));

// List of all game objects (by category).
// All relevant information regarding a game object (title, description, image…) can be found here.
var game_objects = {
  "disciplines": {
   "camouflage": {
      "title":"Camouflage",
      "desc":"This Discipline enables a Kai Lord to blend in with his surroundings. In the countryside, he can hide undetected among trees and rocks and pass close to an enemy without being seen. In a town or city, it enables him to look and sound like a native of that area, and can help him to find shelter or a safe hiding place.",
      "image":"/images/kai/Camouflage.png"
    },
    "hunting": {
      "title":"Hunting",
      "desc":"This skill ensures that a Kai Lord will never starve in the wild. He will always be able to hunt for food for himself except in areas of wasteland and desert. You are aware that most of Kalte is an icy desert and that opportunities for successful hunting will not arise. But this skill is still very useful for it also enables a Kai Lord to move with great speed and dexterity.",
      "image":"/images/kai/Hunting.png"
    },
    "sixth_sense": {
      "title":"Sixth Sense",
      "desc":"This skill may warn a Kai Lord of imminent danger. It may also reveal the true purpose of a stranger or strange object encountered in your adventure.",
      "image":"/images/kai/Sixth Sense.png"
    },
    "tracking": {
      "title":"Tracking",
      "desc":"This skill enables a Kai Lord to make the correct choice of a path in the wild, to discover the location of a person or object in a town or city and to read the secrets of footprints or tracks.",
      "image":"/images/kai/Tracking.png"
    },
    "healing": {
      "title":"Healing",
      "desc":"This Discipline can be used to restore ENDURANCE points lost in combat. If you possess this skill you may restore 1 ENDURANCE point to your total for every numbered section of the book you pass through in which you are not involved in combat. (This is only to be used after your ENDURANCE has fallen below its original level.) Remember that your ENDURANCE cannot rise above its original level",
      "image":"/images/kai/Healing.png"
    },
    "weaponskill": {
      "title":"Weaponskill",
      "desc":"Upon entering the Kai Monastery, each initiate is taught to master one type of weapon. A random weapon will be assigned to you as your master weapon. The fact that you are skilled with a weapon does not mean you set out on the adventure carrying that particular weapon. However, you will have opportunities to acquire weapons in the course of your adventures. You cannot carry more than 2 weapons.",
      "image":"/images/kai/Weaponskill.png"
    },
    "mindshield": {
      "title":"Mindshield",
      "desc":"Vonotar and many of the evil creatures under his command have the ability to attack you using their Mindforce. The Kai Discipline of Mindshield prevents you from losing any ENDURANCE points when subjected to this form of attack.",
      "image":"/images/kai/Mindshield.png"
    },
    "mindblast": {
      "title":"Mindblast",
      "desc":"This enables a Kai Lord to attack an enemy using the force of his mind. It can be used at the same time as normal combat weapons and adds two extra points to your COMBAT SKILL. Not all the creatures encountered on this adventure will be harmed by Mindblast. You will be told if a creature is immune.",
      "image":"/images/kai/Mindblast.png"
    },
    "mind_over_matter": {
      "title":"Mind Over Matter",
      "desc":"Mind Over Matter is a Kai Discipline that allows Lone Wolf to move objects telekinetically. This power is especially useful to avoid short range traps, or to silently move something without causing attention.",
      "image":"/images/kai/Mind Over Matter.png"
    },
    "animal_kinship": {
      "title":"Animal Kinship",
      "desc":"This skill enables a Kai Lord to communicate with some animals and to be able to guess the intentions of others.",
      "image":"/images/kai/Animal Kinship.png"
    }
  },
  "items":{
    "weapons":{
      "sword":{
        "title": "Sword",
        "desc" : "Weapon",
        "image":"/images/weapons/Sword.png"
      },
      "short_sword":{
        "title": "Short Sword",
        "desc" : "Weapon",
        "image":"/images/weapons/Short Sword.png"
      },
      "spear":{
        "title": "Spear",
        "desc" : "Weapon",
        "image":"/images/weapons/Spear.png"
      },
      "mace":{
        "title": "Mace",
        "desc" : "Weapon",
        "image":"/images/weapons/Mace.png"
      },
      "warhammer":{
        "title": "Warhammer",
        "desc" : "Weapon",
        "image":"/images/weapons/Warhammer.png"
      },
      "axe":{
        "title": "Axe",
        "desc" : "Weapon",
        "image":"/images/weapons/Axe.png"
      },
      "quarterstaff":{
        "title": "Quarterstaff",
        "desc" : "Weapon",
        "image":"/images/weapons/Quarterstaff.png"
      },
      "broadsword":{
        "title": "Broadsword",
        "desc" : "Weapon",
        "image":"/images/weapons/Broadsword.png"
      }
    },
    "backpack":{
      "PotionOfLampsur":{
        "title": "Potion of Laumspur",
        "desc" : "Backpack item - This restores 4 ENDURANCE points to your total when swallowed after combat. There is only enough for one dose.",
        "image":"/images/backpack/Potion of Laumspur.png"
      },
      "SpecialRations":{
        "title": "Special Rations",
        "desc" : "Meal - This counts as one meal.",
        "image":"/images/backpack/Special Rations.png"
      }
    },
    "special":{
      "padded_leather_waistcoat":{
        "title": "Padded Leather Waistcoat",
        "desc" : "Special item - This adds 2 ENDURANCE points to your total.",
        "image":"/images/special/Padded Leather Waistcoat.png"
      }
    }
  },
  "enemies":{
    "baknar":{
      "title":"Baknar",
      "desc":"",
      "stamina":19,
      "combat_skill":30,
      "image":"/images/enemies/Baknar.png"
    }
  }
};

// The pages info.
var pages = {
  1:{
    id:1,
    next_pages:[160, 273],
    is_random:false,
    interval:[0,0]
  }
  // TODO : other pages
}

// The player object constructor.
Player = function (name, disciplines, weapons, backpack, special_items, stats) {
  this.name = name;
  this.disciplines = disciplines;
  this.weapons = weapons;
  this.backpack = backpack;
  this.special_items = special_items;
  this.stats = stats;
}

// Utility : checks for duplicates in an array.
function check_for_duplicates(array) {
    var counts = [];
    for(var i = 0; i <= array.length; i++) {
        if(counts[array[i]] === undefined) {
            counts[array[i]] = 1;
        } else {
            return true;
        }
    }
    return false;
}

// Web service.
router.get("/api/player",function(req,res){
   res.json(req.session.player);
});

router.get("/combat/:valeur1/:valeur2", function (req,res) {
  combat_skill_player = req.params.valeur1;
  combat_skill_enemy = req.params.valeur2;

  random_number = Math.floor(Math.random()*10);
  attack_ratio = combat_skill_player - combat_skill_enemy;

  //usage combatRatioPos/Neg[randomNumber][abs(combatRatio)][0 = ennemi, 1 = joueur]
  if (attack_ratio >= 0) {
    combatRatio = 
    [
    [[12,0],[11,0],[11,0],[10,0],[10,0],[9,0],[9,0],[8,0],[8,0],[7,0],[7,0],[6,0]],
    [[3,5],[2,5],[2,5],[1,6],[1,6],[0,6],[0,6],[0,8],[0,8],[0,999],[0,999],[0,999]],
    [[4,4],[3,5],[3,5],[2,5],[2,5],[1,6],[1,6],[0,7],[0,7],[0,8],[0,8], [0,999]],
    [[5,4],[4,4],[4,4],[3,5],[3,5],[2,5],[2,5],[1,6],[1,6],[0,7],[0,7],[0,8]],
    [[6,3],[5,4],[5,4],[4,4],[4,4],[3,5],[3,5],[2,6],[2,6],[1,7],[1,7],[0,8]],
    [[7,2],[6,3],[6,3],[5,4],[5,4],[4,4],[4,4],[3,5],[3,5],[2,6],[2,6],[1,7]],
    [[8,2],[7,2],[7,2],[6,3],[6,3],[5,4],[5,4],[4,5],[4,5],[3,6],[3,6],[2,6]],
    [[9,1],[8,2],[8,2],[7,2],[7,2],[6,3],[6,3],[5,4],[5,4],[4,5],[4,5],[3,5]],
    [[10,0],[9,1],[9,1],[8,1],[8,1],[7,2],[7,2],[6,3],[6,3],[5,4],[5,4],[4,4]],
    [[11,0],[10,0],[10,0],[9,0],[9,0],[8,0],[8,0],[7,2],[7,2],[6,3],[6,3],[5,3]]
    ];
  }
  else {
    combatRatio = 
    [
    [[12,0],[14,0],[14,0],[15,0],[15,0],[18,0],[18,0],[999,0],[999,0],[999,0],[999,0],[999,0]],
    [[3,5], [4,5], [4,5], [5,4] ,[5,4] ,[6,4] ,[6,4] ,[7,4] ,[7,4] ,[8,3] ,[8,3] ,[9,3] ],
    [[4,4], [5,4], [5,4], [6,3] ,[6,3] ,[7,3] ,[7,3] ,[8,3] ,[8,3] ,[9,3] ,[9,3] ,[10,2]],
    [[5,4], [6,3], [6,3], [7,3] ,[7,3] ,[8,3] ,[8,3] ,[9,2] ,[9,2] ,[10,2] ,[10,2] ,[11,2]],
    [[6,3], [7,3], [7,3], [8,2] ,[8,2] ,[9,2] ,[9,2] ,[10,2],[10,2],[11,2] ,[11,2] ,[12,2]],
    [[7,2], [8,2], [8,2], [9,2] ,[9,2] ,[10,2],[10,2],[11,2],[11,2],[12,2] ,[12,2] ,[14,1]],
    [[8,2], [9,2], [9,2], [10,2],[10,2],[11,1],[11,1],[12,1],[12,1],[14,1] ,[14,1] ,[16,1]],
    [[9,1], [10,1],[10,1],[11,1],[11,1],[12,0],[12,0],[12,0],[12,0],[16,0] ,[16,0] ,[18,0]],
    [[10,0],[11,0],[11,0],[12,0],[12,0],[14,0],[14,0],[14,0],[14,0],[18,0] ,[18,0] ,[999,0]],
    [[11,0],[12,0],[12,0],[14,0],[14,0],[16,0],[16,0],[16,0],[16,0],[999,0],[999,0],[999,0]]
    ];
  }

  res.json({attack_ratio:attack_ratio, random:random_number, stamina_lost_player:combatRatio[random_number][Math.abs(attack_ratio)][0], stamina_lost_enemy:combatRatio[random_number][Math.abs(attack_ratio)][1] });

});

// Get home page.
router.get("/", function(req, res, next) {
  res.render("index", { title: "Lone Wolf : The Caverns of Kalte" });
});

// Get help page.
router.get("/help", function(req, res, next) {
  res.render("help", { title: "Help", game_objects:game_objects });
});

// Get the player's creation page.
router.get("/create", function(req, res, next) {
  res.render("create", { title: "Create your player" , game_objects:game_objects, error:req.session.creation_error });
});

// Get a fight page.
router.get("/combat/:valeur", function(req, res, next) {
  var enemy_name = req.params.valeur;
  
  // TODO: update of the fight values (for fight logic).

  res.render("combat", { title: "Combat" , enemy_name:enemy_name, game_objects:game_objects, player:req.session.player });
});

// Get a page of the book.
router.get("/page/:valeur1/:valeur2", function(req, res, next) {
  var page = req.params.valeur1;
  var page_content = req.params.valeur2;
  res.render((page_content == 1) ? ("p" + page) : ("p" + page + "decision"), { title: "Page " + page , game_objects:game_objects, player:req.session.player });
});

// Get a page of the book.
router.get("/page/:valeur", function(req, res, next) {
  var page = req.params.valeur;
  res.render('p' + page, { title: "Page " + page , game_objects:game_objects, player:req.session.player }, function (err, html) {
    res.json({ id:page, html:html/*, next_pages:pages[page].next_pages */}); // TODO: next_pages
  });
});

// Random choic..
router.get("/random/:valeur",function(req,res){
  var valeur = req.params.valeur;
  var a = pages[valeur].interval[0];
  var b = pages[valeur].interval[1];
  var random_choice = Math.floor(Math.random()*(b-a+1) + a);
  res.json({random_choice:random_choice});
});

// Create player.
router.post("/create", function (req, res) {
    // Initializing values.
    disciplines = [];
    weapons = [];
    backpack = [];
    special_items = [];

    // Getting the stats.
    combat_skill = Math.floor((Math.random() * 10) + 10);
    stamina = Math.floor((Math.random() * 10) + 20);
    gold = Math.floor((Math.random() * 10) + 10);

    stats = {
      "combat_skill":combat_skill,
      "stamina":stamina,
      "gold":gold
    };

    // Getting the name.
    name = req.body.name;

    // Getting the items.
    if(Object.keys(game_objects.items.weapons).indexOf(req.body.item1) >= 0)
      weapons.push(req.body.item1);
    else if(Object.keys(game_objects.items.special).indexOf(req.body.item1) >= 0)
      special_items.push(req.body.item1)
    else if(Object.keys(game_objects.items.backpack).indexOf(req.body.item1) >= 0)
      backpack.push(req.body.item1)

    if(Object.keys(game_objects.items.weapons).indexOf(req.body.item2) >= 0)
      weapons.push(req.body.item2);
    else if(Object.keys(game_objects.items.special).indexOf(req.body.item2) >= 0)
      special_items.push(req.body.item2)
    else if(Object.keys(game_objects.items.backpack).indexOf(req.body.item2) >= 0)
      backpack.push(req.body.item2)

    // Getting the disciplines.
    disciplines.push(req.body.discipline1);
    disciplines.push(req.body.discipline2);
    disciplines.push(req.body.discipline3);
    disciplines.push(req.body.discipline4);
    disciplines.push(req.body.discipline5);

    // Adding bonuses if available.
    if (disciplines.indexOf("weaponskill") >= 0) {
      bonus_weapon = Math.floor((Math.random() * 10));
      if(weapons.indexOf(Object.keys(game_objects.items.weapons)[bonus_weapon]) >= 0) {
        stats.combat_skill += 2;
      }
    }

    if (disciplines.indexOf("mindblast") >= 0) {
      stats.combat_skill += 2;
    }

    if (special_items.indexOf("padded_leather_waistcoat") >= 0) {
      stats.stamina += 2;
    }

    // Check for error.
    error = check_for_duplicates(disciplines) || check_for_duplicates(weapons) || check_for_duplicates(backpack) || check_for_duplicates(special_items);
    req.session.creation_error = error;

    // Redirecting.
    if(!error) {
      player = new Player(name, disciplines, weapons, backpack, special_items, stats);
      req.session.player = player;
      res.redirect("/page/1/1");
    }
    else{
      res.redirect("/create");
    }    
});

