var mongoose     = require('mongoose');
var Schema       = mongoose.Schema;

var JoueurSchema   = new Schema({
    habilete: Number,
    endurance: Number,
    pieceOr: Number,
    disciplines: [{}],
    armes: [{}],
    objets: [{}],
    objetsSpeciaux: [{}]
});

module.exports = mongoose.model('Joueur', JoueurSchema);


