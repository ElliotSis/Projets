var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var JoueurSchema = new Schema({
    pseudo: String,
    habileteBase: Number,
    habiletePlus: Number,
    enduranceBase: Number,
    endurancePlus: Number,
    pieceOr: Number,
    disciplines: [String],
    armes: [String],
    objets: [String],
    objetsSpeciaux: [String],
    page_av: Number,
    section_av: Number
});

module.exports = mongoose.model('Joueur', JoueurSchema);

