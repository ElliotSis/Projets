$(document).ready(function(){

	$('.trash').on('click', function(){ 
	  var id = this.id;
	  	if (confirm('Voulez vous vraiment supprimer ce joueur de la base de données?')) {
		    if(id){
			Joueur.remove({ _id: id }, function(err, joueur) {
				if (err) {
				    alert(err);
				} else {
				    Avancement.remove({ joueurId: id }, function(err, avancement) {
					if (err) {
					    alert(err);
					} else {
					    alert("Le joueur et son avancement ont été correctement supprimé.");
					}
				    });
				}
			    });
		    }
		}
	});
});
