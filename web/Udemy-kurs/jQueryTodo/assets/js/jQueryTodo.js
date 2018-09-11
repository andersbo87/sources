// Huke av gitte elementer ved å klikke på dem.
$("ul").on("click", "li", function(){
	$(this).toggleClass("completed");
});

// Klikker brukeren på X, slettes denne
// ene saken fra lista.
$("ul").on("click", "span", function(event){
	$(this).parent().fadeOut(1000, function(){
		$(this).remove();
	});
	event.stopPropagation();
});

$("input[type='text']").on("keypress", function(event){
	console.log("Du trykket en knapp på tastaturet!");
	if(event.which === 13) {
		console.log("Du trykket Enter-knappen!");
		// Lagrer det brukeren skrev i en variabel.
		var todoItem = $(this).val();
		$(this).val("");
		// Oppretter en ny LI med det nye innholdet
		$("ul").append("<li><span><i class='fa fa-trash-alt'></i></span> " + todoItem + "</li");
		
	}
});


$(".fa-plus").click(function(){
	$("input[type='text']").fadeToggle();
});