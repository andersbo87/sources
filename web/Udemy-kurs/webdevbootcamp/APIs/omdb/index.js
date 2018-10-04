var express = require("express");
var ejs = require("ejs");
var request = require("request");
var app = express();
app.set("view engine", "ejs");


app.get("/", function(req, res){
	// Put some code here.
	res.render("search");
});

app.get("/results", function(req, res){
	// Put some code here.
	var results = req.query.search;
	var url = "http://omdbapi.com/?s=" + results + "&apikey=thewdb";
	request(url, function(error, response, body){
		if(!error && response.statusCode === 200){
			var data = JSON.parse(body);
			//res.send(data["Search"][0]["Title"]); // Henter første element.
			res.render("results", {data: data});
		}
	});
});

// Linjen i koden under kan også skrives sliK:
// app.listen(process.env.PORT, function(){console.log("Serving on port 3000")});
// Dette gjelder først og fremst om du bruker en skytjeneste til å "hoste" siden.
// Kjører du Node lokalt, kan du bruke følgende ukommenterte kode:
app.listen(3000, process.env.IP, function(){
	console.log("Starter node.js…");
}); 