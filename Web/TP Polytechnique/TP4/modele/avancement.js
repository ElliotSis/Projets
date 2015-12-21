var mongoose     = require('mongoose');
var Schema       = mongoose.Schema;

var AvancementSchema = new Schema({
    pageActive: Number
});

module.exports = mongoose.model('Avancement', AvancementSchema);