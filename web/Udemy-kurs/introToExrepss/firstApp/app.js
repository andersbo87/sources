var express = require('express');
var app = express();

/*
	ROUTES:
	/ => "Hei sann"
	/bye => "Farvel"
	/dog => "VOFF!"
*/

app.get("/", function(req, res){
	res.send("Hei sann!");
});

app.get("/dog", function(req, res){
	res.send("VOFF!");
});

app.get("/bye", function(req, res){
	res.send("Farvel!");
});

app.get("/r/:subredditName", function(req, res){
	console.log(req);
	console.log(req.params);
	res.send("Velkommen til \"Subreddit\" om " + req.params.subredditName);
});

app.get("/r/:subredditName/comments/:id/:title", function(req, res){
	console.log(req.params);
	var title = req.params.title;
	res.send("Velkommen til " + title + " kommentarside på \"Subreddit\"!");
});

app.get("*", function(req, res){
	res.send("Finner ikke den aktuelle siden.");
});

// Linjen i koden under kan også skrives sliK:
// app.listen(process.env.PORT, function(){console.log("Serving on port 3000")});
// Dette gjelder først og fremst om du bruker en skytjeneste til å "hoste" siden.
// Kjører du Node lokalt, kan du bruke følgende ukommenterte kode:
app.listen(3000, process.env.IP, function(){
	console.log("Starter node.js…");
}); 
