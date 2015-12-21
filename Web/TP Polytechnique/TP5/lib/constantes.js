var discipline = [{
    title: "Camouflage", selected: false},
    {title: "Chasse",selected:false},
    {title: "Sixieme Sens",selected:false},
    {title: "Orientation",selected:false},
    {title: "Guerison",selected:false},
    {title: "Maitrise Armes",selected:false},
    {title: "Bouclier Psychique",selected:false},
    {title: "Puissance Psychique",selected:false},
    {title: "Communication Animale",selected:false},
    {title: "Maitrise Psy Matiere",selected:false
}];

var arme = [{
    title: "Epee", selected: false},
    {title: "Sabre", selected: false},
    {title: "Lance", selected: false},
    {title: "Masse", selected: false},
    {title: "Marteau de guerre", selected: false},
    {title: "Hache", selected: false},
    {title: "Baton", selected: false},
    {title: "Glaive", selected: false
}];

var objet = [{
    title: "Potion Lampsur", selected: false},
    {title: "Ration spéciales", selected: false},
    {title: "Repas", selected: false},
    {title: "Couverture en ", selected: false},
    {title: "Corde", selected: false
}];

var objetSpecial = [{
    title: "Gilet cuir martelet", selected: false},
    {title: "Huile de Bakanal", selected: false},
    {title: "Epee os", selected: false},
    {title: "Disque pierre bleu", selected: false
}];

var objetCreationJoueur = [{
    title: "Epee", selected: false, type: "arme"},
    {title: "Sabre", selected: false, type: "arme"},
    {title: "Lance", selected: false, type: "arme"},
    {title: "Masse", selected: false, type: "arme"},
    {title: "Marteau de guerre", selected: false, type: "arme"},
    {title: "Hache", selected: false, type: "arme"},
    {title: "Baton", selected: false, type: "arme"},
    {title: "Glaive", selected: false, type: "arme"},
    {title: "Potion Lampsur", selected: false, type: "objet"},
    {title: "Ration spéciales", selected: false, type: "objet"},
    {title: "Gilet cuir martelet", selected: false, type: "objetSpecial"
}];

module.exports = {
    discipline: discipline,
    arme: arme,
    objet: objet,
    objetSpecial: objetSpecial,
    objetCreationJoueur : objetCreationJoueur
}

