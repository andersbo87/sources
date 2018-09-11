var express = require("express");
var bodyParser = require("body-parser");
var app = express();

app.use(bodyParser.urlencoded({extended: true}));
app.set("view engine", "ejs");
app.use(express.static("public"));

var campgrounds = [
	{name: "Salmon Creek", image: "https://farm6.staticflickr.com/5181/5641024448_04fefbb64d.jpg"},
	{name: "Granite Hill", image: "https://pixabay.com/get/ea36b7062bf6093ed1584d05fb1d4e97e07ee3d21cac104497f6c17aa1efb2bf_340.jpg"},
	{name: "Mountain Goat's Rest", image: "http://farm7.staticflickr.com/6057/6234565071_4d20668bbd.jpg"}
];

app.get("/",function(req, res){
	// Put in some code here...
	res.render("landing");
});

app.get("/campgrounds/new",function(req, res){
	// Put in some code here...
	res.render("new.ejs");
});

app.post("/campgrounds", function(req, res){
	// hente data fra skjemaet og legge til i tabellen
	var name = req.body.name; 
	var image = req.body.image;
	var newCampground = {name: name, image: image};
	campgrounds.push(newCampground);
	// gå tilbake til campgrounds-siden.
	res.redirect("/campgrounds");
});

app.get("/campgrounds", function(req, res){
	
	res.render("campgrounds", {campgrounds: campgrounds});
});

// Linjen i koden under kan også skrives sliK:
// app.listen(process.env.PORT, function(){console.log("Serving on port 3000")});
// Dette gjelder først og fremst om du bruker en skytjeneste til å "hoste" siden.
// Kjører du Node lokalt, kan du bruke følgende ukommenterte kode:
app.listen(3000, process.env.IP, function(){
	console.log("YelpCamp-serveren har startet…");
}); 