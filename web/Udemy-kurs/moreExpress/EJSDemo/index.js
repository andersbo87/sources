var express = require('express');
var app = express();

app.use(express.static("public"));
app.set("view engine", "ejs");

app.get("/", function(req, res){
	//res.send("<h1>Velkommen hjem!</h1><strong>Dette er en hjemmeside.</strong>");
	res.render("home");
});

app.get("/fallinlovewith/:thing", function(req, res){
	var thing = req.params.thing;
	//res.send("Du forelsket deg i " + thing + ".")
	res.render("love", {thingVar: thing});
});

app.get("/posts", function(req, res){
	var posts = [
		{title: "Post 1", author: "Susanne"},
		{title: "Nok en post", author: "Hans Petter"},
		{title: "En siste post", author: "Anne"}
	];
	res.render("posts", {posts: posts});
});

// Linjen i koden under kan også skrives sliK:
// app.listen(process.env.PORT, function(){console.log("Serving on port 3000")});
// Dette gjelder først og fremst om du bruker en skytjeneste til å "hoste" siden.
// Kjører du Node lokalt, kan du bruke følgende ukommenterte kode:
app.listen(3000, process.env.IP, function(){
	console.log("Starter node.js…");
}); 