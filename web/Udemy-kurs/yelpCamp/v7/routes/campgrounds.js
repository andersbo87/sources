var express = require("express");
var router = express.Router({mergeParams: true});
var campground = require("../models/campground");

// Skjema som lar brukeren lage et nytt campingsted:
router.get("/new",function(req, res){
    // Put in some code here...
    res.render("campgrounds/new.ejs");
});

// Oppretter et nytt campingsted
router.post("/", function(req, res){
    // hente data fra skjemaet og legge til i tabellen
    var name = req.body.name; 
    var image = req.body.image;
    var description = req.body.description;
    var newCampground = {name: name, image: image, description: description};
    // Opprett et nytt campingsted og lagre dette i databasen:
    campground.create(newCampground,function(err, newCampground){
	if(err)
	    console.log("Kunne ikke lagre det nye campingstedet i databasen:\n" + err);
	else
	{
	    // gå tilbake til campgrounds-siden.
	    res.redirect("/campgrounds");
	}		
    });
});

// Vis alle campingsteder:
router.get("/", function(req, res){
    // Get all campgrounds from the database
    campground.find({}, function(err, allCampgrounds){
	if(err)
	    console.log("Noe har gått galt:\n" + err);
	else
	{
	    res.render("campgrounds/index", {campgrounds: allCampgrounds, currentUser: req.user});		
	}
    });
    //res.render("campgrounds", {campgrounds: campgrounds});
});


// SHOW - viser info om gitt campingsted.
router.get("/:id", function(req, res){
    // Finn campingsted med angitt ID.
    campground.findById(req.params.id).populate("comments").exec(function(err, foundCampground){
	if(err)
	    console.log("En feil har oppstått:\n" + err);
	else {
	    // Vis siden om det aktuelle camptingstedet.
	    console.log(foundCampground);
	    res.render("campgrounds/show", {campground: foundCampground});		
	}
    });
});

module.exports = router;