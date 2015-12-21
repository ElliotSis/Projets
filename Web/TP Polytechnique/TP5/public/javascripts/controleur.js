var app = angular.module("LoneWolf", ['ngSanitize']);


/*******************************************/
//Fonction permettant de compiler du html qui  comprends des directives angular 
app.directive('compileHtml', compileHtml);
function compileHtml($compile) {
  return {
    restrict: 'A',
    link: function(scope, element, attrs) {
      scope.$watch(function() {
        return scope.$eval(attrs.compileHtml);
      }, function(value) {
        element.html(value);
        $compile(element.contents())(scope);
      });
    }
  };
}
/*****************************************/


/***** Controleur de la page de création ***************/
app.controller("CreatePlayer", function($scope, $http) {

  
  $scope.objets = objets; //On recupere  tout les objets (armes + objets + objets speciaux)
  $scope.disciplines = disciplines; // On recupere toutes les disciplines
  $scope.disable = true; //Booleen desactivation bouton Creation Joueur
  $scope.selectedObj = 0; //Nombre d'objets selectionnées
  $scope.selectedItems = 0; //Nombre de disciplines selectionnes

  /** Fonction d'initialisation ***/
  $scope.initPlayers = function(joueurs) {
    $scope.joueurs = joueurs; //On recupere les joueurs deja enregistres
    if (joueurs) {
      joueurs.forEach(function(joueur) {
        var path = '/api/joueurs/avancement/' + joueur._id; //requete http pour recuperer l'avancement de chaque joueur
        $http.get(path).then(function(response) {
          joueur.page_av = response.data.pageId;
          joueur.section_av = response.data.sectionId;
        }, function(error) {
          console.log(error);
        });
      });
    }

  };

  //Si les conditions sont remplies on active ou non le bouton et on attribue du css en fonction des cas
  $scope.updateButton = function() {
    if ($scope.selectedItems == 5 && $scope.selectedObj == 2) {
      $scope.disable = false;
      document.getElementsByClassName("button")[0].setAttribute("id", "buttonSuccess");
    } else {
      $scope.disable = true;
      document.getElementsByClassName("button")[0].setAttribute("id", "buttonFail");
    }
  };

  //Detection checkbox disciplines
  $scope.updateDisc = function(disc) {
    if (disc.selected)
      $scope.selectedItems++;
    else
      $scope.selectedItems--;

  };
  //Detection checkbox objets
  $scope.updateObj = function(obj) {
    if (obj.selected)
      $scope.selectedObj++;
    else
      $scope.selectedObj--;
  };


  //Requete http pour supprimer un joueur
  $scope.deletePlayer = function(id) {
    var path = '/api/joueurs/' + id;
    if (confirm('Voulez vous vraiment supprimer ce joueur de la base de données?')) {
      $http.delete(path).then(function(response) {
        alert("Le joueur et son avancement ont bien été supprimés");
        location.reload();
      }, function(error) {
        alert("Erreur : " + error.message);
      });
    }
  };



});

//Controleur des pages de jeu
app.controller("pageManager", function($scope, $http, $sce) {

  var choicePages = [91,57,331,12,129,209,155,134,167,331,180,78,12]; //Toutes les pages comportant des actions à faire
  var randomPages = [134,167,331]; //Toutes les pages comportant la table de choix aléatoire
  //$scope.totalEndurance = current.enduranceBase + (current.endurancePlus - current.enduranceBase); //On calcul l'endurance total
  var initEndurancePlus = current.endurancePlus; //On enregistre l'endurance bonus
  var initEnduranceBase = current.enduranceBase; //On enregistre l'endurance de base
  $scope.bourse = current.pieceOr; //On enregistre la bourse du joueur

  


    /***** Fonctions surveillant les changements de valeur de l'endurance et de l'habilete *******/
    /****************** Permets un affichage correcte dans la section Stats du joueur ************/
	$scope.$watch('[currentPlayer.enduranceBase,currentPlayer.endurancePlus]', function () {
                    $scope.differenceEndurance = Math.abs($scope.currentPlayer.endurancePlus - $scope.currentPlayer.enduranceBase);
                    $scope.totalEndurance = $scope.currentPlayer.enduranceBase + $scope.differenceEndurance;
	}, true);

	$scope.$watch('[currentPlayer.habileteBase,currentPlayer.habiletePlus]', function () {
		  if($scope.currentPlayer.habiletePlus - $scope.currentPlayer.habileteBase < 0){
		    $scope.lessHabilete = true;
                    $scope.differenceHabilete = Math.abs($scope.currentPlayer.habiletePlus - $scope.currentPlayer.habileteBase);
                  }
		  else{
		    $scope.lessHabilete = false;
		    $scope.differenceHabilete = $scope.currentPlayer.habiletePlus - $scope.currentPlayer.habileteBase;
                  }
	}, true);

  /************************************************************************************************/

  getVolumePack = function(){ //On recupere la valeur du volume occupé par les objets dans le sac du joueur
   var volume = 0;
   $scope.currentPlayer.objets.forEach(function(obj) {
      if (obj.name.indexOf("Couverture Fourrure") >= 0)
         volume += 2;
      else
         volume++;
    });
   $scope.volumeObjetsBackPack = volume;
  }

  /** On reucpere le html pour le premier chargement de page ****/
  $scope.initHtml = function(html, pageId) {

    $scope.choices = []; //Tableau comportant les differents choix disponibles
    $scope.currentPlayer = current; //On récupere le joueur actuel
    $scope.currentHtml = html;
    $scope.currentPage = pageId;
    $scope.disableConfirmOil = true;//Booelen confirmant ou non si le joueur possede l'huile de bakanal
    $scope.drainEndurance = false;//Boolen pour confirmer le retrait d'endurance
    $scope.showChoices = true; //Booleen pour montrer la section de choix de la prochaine page (avec choix aléatoire)
    $scope.showOptions = true;
    getVolumePack();

    choicePages.forEach(function(id) {
      if (pageId == id)
        $scope.showOptions = false;
    });

  }

  $scope.deliberatelyTrustDangerousSnippet = function() {
    return $sce.trustAsHtml($scope.currentHtml);
  };

  /**** Lorsque le joueur clique sur son choix on recupere le html de la page demandé pour l'afficher sans chargement ***/
  $scope.chargeNextPage = function(num) {

    $scope.disableConfirmOil = true;//Booelen confirmant ou non si le joueur possede l'huile de bakanal
    $scope.drainEndurance = false;//Boolen pour confirmer le retrait d'endurance
    $scope.showChoices = true;
    $scope.showOptions = true;
    //Si c'est une page avec action on affiche pas les choix de pages suivantes
    choicePages.forEach(function(id) {
      if (num == id)
        $scope.showOptions = false;
    });
    var path = '/api/pages/' + num;
    $scope.currentPage = num;
    $http.get(path).then(function(response) { //On récupere l'html de la page demandée
      $scope.currentHtml = response.data;
      $http.put('/api/joueurs/avancement/' + $scope.currentPlayer._id, { //On mets à jour l'avancement du joueur
        "pageId": num
      }).then(function(response) {
        $http.put('/api/joueurs/' + $scope.currentPlayer._id, { //On mets à jour les stats du joueur
          "endurance": $scope.currentPlayer.endurancePlus,
          "pieceOr": $scope.currentPlayer.pieceOr,
          "objets": $scope.currentPlayer.objets,
          "objetsSpeciaux": $scope.currentPlayer.objetsSpeciaux,
          "armes": $scope.currentPlayer.armes
        }).then(function(response) {
          if ($scope.currentPlayer.disciplines.indexOf("Guerison") && $scope.currentPage != 1) { 
            $scope.currentPlayer.endurancePlus += 1; //Si le joueur possède Guerison +1 à chaque chargement
            alert("Votre compétence Guerison vous permets de regagner un point d'endurance");
          }
        }, function(error) {
          alert("Erreur : " + error.message);
        });
      }, function(error) {
        alert("Erreur : " + error.message);
      });

    }, function(error) {
      alert("Erreur : " + error.message);
    });
  };

  /*** Fonction d'initialisation d'un combat ***/
  $scope.initFight = function() {
    $scope.playerLife = $scope.currentPlayer.endurancePlus + $scope.currentPlayer.enduranceBase;
    $scope.fightBegin = false; //Début du combat ?
    $scope.showOptions = false; //On affiche pas la suite (in case)
    $scope.loose = false; //Booleen de défaite
    $scope.win = false; //Booleen de victoire
    $scope.flee = false;//Boolen de fuite
    $scope.rounds = []; //Objet javascript qui comportera tout les rounds
    $scope.countRound = 0; //Numero du round
    $scope.disableFightButtons = false; //Booleen d'activation des boutons de combat

    $scope.currentPlayer.disciplines.forEach(function(disc) {
      $scope.psyField = disc.indexOf("Bouclier Psychique") >= 0 ? true : false; //On verifie si le joueur possède Bouclier Psychique
    });

    var path = '/api/pages/' + $scope.currentPage + '/1';
    $http.get(path).then(function(response) { //On récupere les données concernant le combat et le monstre
      console.log(response);
      $scope.fight = response.data.combat;
      $scope.ennemiLife = $scope.fight.endurance;
    }, function(error) {
      alert("Erreur : " + error.message);
    });

  };

  //Fonction appellée pour chaque round
  $scope.roundFight = function(languabarb) {
    $scope.fightBegin = true;//Le combat commence
    $scope.disableFightButtons = true;
    var path = '/api/combat/' + $scope.currentPlayer.endurancePlus + "/" + $scope.currentPlayer.habiletePlus + "/" + $scope.fight.endurance + "/" + $scope.fight.habilete;
    $http.get(path).then(function(response) { //On récupere les donnes du combat en fonction des stats du joueur et du monstre
      $scope.fightFigures = response.data;
      $scope.fightFigures.degatEnnemi = languabarb ? $scope.fightFigures.degatEnnemi + 3 : $scope.fightFigures.degatEnnemi;
      $scope.countRound += 1;
      $scope.disableFightButtons = false;
      $scope.ennemiLife -= $scope.fightFigures.degatJoueur >= $scope.ennemiLife ? $scope.ennemiLife : $scope.fightFigures.degatJoueur;
      $scope.playerLife -= $scope.fightFigures.degatEnnemi >= $scope.playerLife ? $scope.playerLife : $scope.fightFigures.degatEnnemi;

      $scope.rounds.push({
        "countRound": $scope.countRound,
        "ratio": response.data.quotientAttaque,
        "random": response.data.chiffreAleatoire,
        "degatEnnemi": $scope.fightFigures.degatEnnemi,
        "degatJoueur": response.data.degatJoueur,
        "playerLife": $scope.playerLife,
        "ennemiLife": $scope.ennemiLife
      });

      if ($scope.playerLife == 0) { //Si le joueur perd
        $scope.loose = true; //Defaite
        $scope.disableFightButtons = true;
      } else if ($scope.ennemiLife == 0) { //Si le joueur gagne
        $scope.win = true; //Victoire
        $scope.showOptions = true;
        $scope.disableFightButtons = true;
        if(psyField) //On desactive le bouclier psychique
         $scope.currentPlayer.habiletePlus -= 2;
      }


    }, function(error) {
      alert("Erreur : " + error.message);
    });


  };
  //Fonction si le joueur fuit, identique à la derniere mis a part qu'il y a qu'un round
  $scope.fleeFight = function(languabarb) {
    $scope.fightBegin = true;
    $scope.disableFightButtons = true;
    var path = '/api/combat/' + $scope.currentPlayer.endurancePlus + "/" + $scope.currentPlayer.habiletePlus + "/" + $scope.fight.endurance + "/" + $scope.fight.habilete;
    $http.get(path).then(function(response) {
      $scope.fightFigures = response.data;
      $scope.fightFigures.degatEnnemi = languabarb ? $scope.fightFigures.degatEnnemi + 3 : $scope.fightFigures.degatEnnemi;
      $scope.countRound += 1;
      $scope.disableFightButtons = false;
      $scope.currentPlayer.enduranceBase -= $scope.fightFigures.degatJoueur >= $scope.currentPlayer.enduranceBase ? $scope.currentPlayer.enduranceBase : $scope.fightFigures.degatEnnemi;


      $scope.rounds.push({
        "countRound": $scope.countRound,
        "ratio": response.data.quotientAttaque,
        "random": response.data.chiffreAleatoire,
        "degatEnnemi": $scope.fightFigures.degatEnnemi,
        "degatJoueur": response.data.degatJoueur,
        "playerLife": $scope.currentPlayer.endurancePlus + $scope.currentPlayer.enduranceBase,
        "ennemiLife": $scope.ennemiLife
      });
      $scope.flee = true;
      $scope.showOptions = true;
      $scope.disableFightButtons = true;

    }, function(error) {
      alert("Erreur : " + error.message);
    });

  };

  //Si le joueur perd à un combat il recommence dès le debut
  $scope.restartGame = function() {
    var path = "/api/joueurs/avancement/" + $scope.currentPlayer._id;
    $http.put(path, { //On re initialise son avncement à la premiere page
      "pageId": 1,
      "sectionId": 1
    }).then(function(response) {
        $http.put('/api/joueurs/' + $scope.currentPlayer._id, { //On remet son endurance à ses valeurs initiales
          "endurance": initEndurancePlus,
          "enduranceb": initEnduranceBase
        }).then(function(response) {
             console.log(response);
             document.location.href = "http://localhost:3000/creationJoueur"; //On redirige vers la page de création
        }, function(error) {
          alert("Erreur : " + error.message);
        });
    }, function(error) {
      alert("Erreur : " + error.message);
    });

  };

  //Fonction appelle lorsque le joueur arrive sur une page où il meurt
  $scope.dieAndDeletePlayer = function() {
    var path = "/api/joueurs/" + $scope.currentPlayer._id;
    $http.delete(path).then(function(response) { //On supprime son profil
      document.location.href = "http://localhost:3000";
    }, function(error) {
      alert("Erreur : " + error.message);
    });

  };

  //Activation du bouclier psychique
  $scope.enablePsyField = function() {
    $scope.currentPlayer.habiletePlus += 2;
    $scope.psyField = false;
  };

  //On ajoute l'huile de Bakanal dans l'inventaire
  $scope.addOil = function() {
    if ($scope.currentPlayer.objetsSpeciaux.indexOf("Huile de Bakanal") != 0) { //On check si il le possède pas deja
      $scope.currentPlayer.objetsSpeciaux.push("Huile de Bakanal");
      $scope.disableConfirmOil = false;
    }
  };

  //Si le joueur possède bien l'huile dans son inventaire, il peut continuer
  $scope.enableToContinue = function() {
    if (!$scope.disableConfirmOil)
      $scope.showOptions = true;
  };

  //Verification de certaines disciplines en fonction de certaines pages (voir instructions dans le TP)
  $scope.controlDisciplines = function(numPage) {
    var discPages = [204, 318, 209, 339];
    $scope.info = "";
    if (discPages.indexOf(numPage) >= 0) {
      if (numPage == 204 && $scope.currentPlayer.disciplines.indexOf("Chasse") < 0) {
        $scope.info = "Désolé mais vous n'avez pas la discipline Chasse";
        return true;
      } else if (numPage == 318 && $scope.currentPlayer.disciplines.indexOf("Communication Animale") < 0) {
        $scope.info = "Désolé mais vous n'avez pas la discipline Communication Animale";
        return true;
      } else if (numPage == 209 && $scope.currentPlayer.objetsSpeciaux.indexOf("Huile de Bakanal") < 0) {
        $scope.info = "Désolé mais vous ne vous êtes pas enduit d'huile de Bakanal sur tout le corps ... Dommage !";
        return true;
      } else if (numPage == 339 && $scope.currentPlayer.objetsSpeciaux.indexOf("Huile de Bakanal") >= 0) {
        $scope.info = "Tu possèdes l'huile ... J'aime que tu t'enduis d'huile ..";
        return true;
      } else
        return false;
    } else
      return false;
  };

  //Verification de certaines disciplines en fonction de certaines pages (voir instructions dans le TP)
  $scope.checkDisciplines = function() {
    if ($scope.currentPage == 331 && $scope.currentPlayer.disciplines.indexOf("Guerison") >= 0) {
      $scope.info = "Vous êtes exempter de perdre ces 4 points d'endurance grâce à votre compétence de Guérison ! Celle-ci fait apparaitre un sèche cheveux qui vous permets de vous décongeler ! It's super effectve ! "
      return true;
    } else
      return false;
  };
   //Verification de la possession d'Huile de Bakanal 
  $scope.checkBakanalOil = function() {
    if ($scope.currentPlayer.objetsSpeciaux.indexOf("Huile de Bakanal") >= 0) {
      $scope.info = "Vous êtes exempter de perdre ces 3 points d'endurance grâce à votre corps enduit d'huile de Bakanal ... So sex .. "
      return true;
    } else
      return false;
  };

  //Fonction de retrait de points d'endruance
  $scope.alertDrainEndurance = function(value) {
    $scope.currentPlayer.enduranceBase -= value;
    $scope.drainEndurance = true;
    alert("Vous perdez " + value + " points d'endurance");
    if ($scope.currentPage == 209 || $scope.currentPage == 129)
      $scope.showOptions = true;
  };
  //Fonction identique à la dernier excepté que c'est pour une page précise où il faut checker si le joueur possède des repas
  $scope.alertDrainEnduranceCheckMeal = function(value) {
    var haveMeal; //boolen qui indique si le joueur possède des repas dans son inventaire
    $scope.currentPlayer.objets.forEach(function(obj) {
      if (obj.name == "Repas") { //Si oui
        haveMeal = true;
        obj.count--; //On en enlève un
        $scope.drainEndurance = true;
        alert("1 Repas a été supprimé dans votre inventaire -- ");
      } else
        haveMeal = false;
    });

    if (!haveMeal) { //Sinon le joueur perd de l'endurance
      $scope.currentPlayer.enduranceBase -= value;
      $scope.drainEndurance = true;
      alert("Vous perdez " + value + " points d'endurance");
    }
  };

  $scope.checkPreviewRandom = function() {
    $scope.showChoices = true;
    $scope.disableRandomButton = false;
  };

  //Fonction recuperant les donnes necessaires dans les pagesavec table de hasard
  $scope.getRandomValue = function() {
    var path = "/api/pages/choixAleatoire/" + $scope.currentPage;
    $http.get(path).then(function(response) {
      $scope.showChoices = false;
      $scope.choices = response.data;
      if ($scope.currentPage == 155) {
        if ($scope.currentPlayer.endurancePlus <= 10)
          $scope.randomNumber = response.data[0].valeurAleatoire - 2;
        else if ($scope.currentPlayer.endurancePlus >= 20)
          $scope.randomNumber = response.data[0].valeurAleatoire + 1;
        else
          $scope.randomNumber = response.data[0].valeurAleatoire;
      } else
        $scope.randomNumber = response.data[0].valeurAleatoire;

      $scope.disableRandomButton = true;
    }, function(error) {
      alert("Erreur : " + error.message);
    });

  };
  /** Fonctions d'initialisation pour les pages avec des choix d'objets à ajouter dans son inventaire ***/
  $scope.initSpecialObjects = function(speObj) {
    $scope.specialObjs = speObj;
  };

  $scope.initObjects = function(obj) {
    $scope.normalObjects = obj;
    $scope.deleteMeal = true;
  };
 /************************************************************************************************/

  //Après le choix des objets , à l'appui du bouton, on rajoute les objets speciaux dans l'inventaire
  $scope.addToBackpack = function() {
    $scope.specialObjs.forEach(function(obj) {
      if (obj.select && $scope.currentPlayer.objetsSpeciaux.indexOf(obj.name) < 0) {
        $scope.currentPlayer.objetsSpeciaux.push(obj.name);
      }
    });
    $scope.showOptions = true;
  };
  //Identique à la derniere fonction sauf que pour les objets normaux on check le volume pris par les objets 
  $scope.addObjToBackpack = function() {
    var volumeObj = $scope.volumeObjetsBackPack;
    $scope.normalObjects.forEach(function(obj) {
      if (obj.select && volumeObj < 3) {
        if($scope.currentPlayer.objets.indexOf(obj.name) >= 0)
           obj.count++;
        else{
	 $scope.currentPlayer.objets.push({
	  "name": obj.name,
	  "count": obj.count
	 });
        }
        volumeObj += obj.name.indexOf("Couverture Fourrure") < 0 ? 1 : 2; //La couverture prend le volume pour deux objets
        $scope.volumeObjetsBackPack = volumeObj;
      }
    });
  };

  //Suppression d'un repas dans l'inventaire
  $scope.deleteOneMeal = function() {
    $scope.currentPlayer.objets.forEach(function(obj) {
      if (obj.name == "Repas") {
        obj.count--;
         if(obj.count == 0)
           $scope.volumeObjetsBackPack -= 1; //Si il ne reste plus de repas on libère un volume 

        $scope.deleteMeal = false;
        $scope.showOptions = true;
        alert("1 Repas a été supprimé dans votre inventaire");
      }
    });
  };

  //Suppresion des derniers choix faits pour les objets speciaux
  $scope.cancelChoiceSpecialObject = function() {
    $scope.specialObjs.forEach(function(obj) {
      if (obj.select)
        $scope.currentPlayer.objetsSpeciaux.pop();
    });

  };

   //Suppresion des derniers choix faits pour les objets 
  $scope.cancelChoiceObject = function() {
    $scope.normalObjects.forEach(function(obj) {
      if (obj.select)
        $scope.currentPlayer.objets.pop();
    });
  };

});

