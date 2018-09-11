var express = require('express');
var bodyParser = require('body-parser');
var app = express();

var friends = ["Tony", "Miranda", "Joakim", "Anette"];

app.use(bodyParser.urlencoded({extended: true}));
app.set("view engine", "ejs");

app.get("/", function(req, res){
	res.render("home");
});

app.get("/friends", function(req,res){
	
	res.render("friends", {friends: friends});
});

app.post("/addfriend", function(req, res) {
	var newFriend = req.body.newfriend;
	friends.push(newFriend);
	res.redirect("/friends");
	//res.render("friends", {friends: friends});
})

// Linjen i koden under kan også skrives sliK:
// app.listen(process.env.PORT, function(){console.log("Serving on port 3000")});
// Dette gjelder først og fremst om du bruker en skytjeneste til å "hoste" siden.
// Kjører du Node lokalt, kan du bruke følgende ukommenterte kode:
app.listen(3000, process.env.IP, function(){
	console.log("Starter node.js…");
}); 