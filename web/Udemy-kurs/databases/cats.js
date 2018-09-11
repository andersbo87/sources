var mongoose = require('mongoose');

// Koble til databasen.
console.log("Kobler til databasen \"cat\".");
// Dersom databasen ikke finnes fra før, blir den automatisk opprettet.
mongoose.connect("mongodb://localhost/cat");

var catSchema = new mongoose.Schema({
	name: String,
	age: Number,
	temperament: String
});

// Kompilerer objektet ovenfor i en modell og lagrer dette i en variabel:
var Cat = mongoose.model("Cat", catSchema);

// Legg til en ny katt i databasen
Cat.create({
	name: "Maia",
	age: 5,
	temperament: "Nice"
}, function(err, cat){
	if(err)
		console.log("Noe gikk galt." + err);
	else
		console.log("Katten ble lagret i databasen.\n" + cat);
});

// Hent alle registrerte katter fra databasen.
Cat.find({}, function(err, cats){
	if(err)
		console.log("En feil oppstod under henting: " + err);
	else
		console.log("Alle katter i databasen:\n" + cats);
});