var express = require("express");
var app = express();

app.get("/", function(req, res){
	res.send("Hi there welcome to my assignment");
});

app.get("/speak/:animal", function(req, res){
	var animal = req.params.animal;
	var sound = "";
	if(animal === "pig")
		sound = "oink";
	else if(animal === "cow")
		sound = "moo";
	else if(animal === "dog")
		sound = "Woof Woof";
	// Lar min egen løsning over bli stående
	/*
	En enda bedre måte å løse oppgaven på, er slik:
	var sounds = {
	   pig: "Oink",
	   cow: "Moo",
	   dog: "Woof Woof"
	}
	sound = sounds[animal].toLowerCase();
	*/
	res.send("The " + animal + " says '" + sound + "'");
});

app.get("/repeat/:phrase/:times", function(req, res){
	var phrase = req.params.phrase;
	var max = Number(req.params.times);
	var newPhrase = "";
	for(var i = 0; i < max; i++){
		newPhrase += phrase + " ";
	}
	res.send(newPhrase);
});

app.get("*", function(res, res){
	res.send("Sorry, page not found…What are you doing with your life?");
});

// Linjen i koden under kan også skrives sliK:
// app.listen(process.env.PORT, function(){console.log("Serving on port 3000")});
// Dette gjelder først og fremst om du bruker en skytjeneste til å "hoste" siden.
// Kjører du Node lokalt, kan du bruke følgende ukommenterte kode:
app.listen(3000, process.env.IP, function(){
	console.log("Starter node.js…");
}); 
