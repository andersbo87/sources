var express = require("express");
var router = express.Router({mergeParams: true});
var campground = require("../models/campground");
var middleware = require("../middleware/");

// Skjema som lar brukeren lage et nytt campingplass:
router.get("/new", isLoggedIn,function(req, res){
    // Put in some code here...
    res.render("campgrounds/new.ejs");
});

// Oppretter et nytt campingplass
router.post("/", isLoggedIn, function(req, res){
    // hente data fra skjemaet og legge til i tabellen
    var name = req.body.name;
    var price = req.body.price;
    var image = req.body.image;
    var description = req.body.description;
    var author = {
    	id: req.user._id,
    	username: req.user.username
    }
    var newCampground = {name: name, price: price, image: image, description: description, author: author};
    // Opprett et nytt campingplass og lagre dette i databasen:
    campground.create(newCampground,function(err, newCampground){
	if(err){
	    console.log("Kunne ikke lagre den nye campingplassen i databasen:\n" + err);
	    req.flash("error", "Kunne ikke lagre den nye campinglpassen i databasen: " + err.message);
	}
	else
	    {
		// gå tilbake til campgrounds-siden.
		    req.flash("success", "Campingplassen ble registrert uten problemer.");
		res.redirect("/campgrounds");
	    }		
    });
});

// Vis alle campingplasser:
router.get("/", function(req, res){
    // Get all campgrounds from the database
    campground.find({}, function(err, allCampgrounds){
	if(err){
	    console.log("Noe har gått galt:\n" + err);
	    req.flash("error", "Noe har gått galt: " + err.message);
	}
	else
	    {
		res.render("campgrounds/index", {campgrounds: allCampgrounds, currentUser: req.user});		
	    }
    });
    //res.render("campgrounds", {campgrounds: campgrounds});
});


// SHOW - viser info om gitt campingplass.
router.get("/:id", function(req, res){
    // Finn campingplass med angitt ID.
    campground.findById(req.params.id).populate("comments").exec(function(err, foundCampground){
	if(err){
	    console.log("En feil har oppstått:\n" + err);
	    req.flash("error", "En feil har oppstått: " + err.message);
            res.redirect("/campgrounds");
	}
	else if(!foundCampground){
	    req.flash("error", "Campingplassen finnes ikke.");
	    res.redirect("/campgrounds");
	}
	else {
	    // Vis siden om det aktuelle camptingstedet.
	    res.render("campgrounds/show", {campground: foundCampground});
	}
    });
});

// Route som gjør at man redigere en campingplass:
router.get("/:id/edit", middleware.checkCampgroundOwnership, function(req, res){
    campground.findById(req.params.id, function(err, foundCampground)
	{
            res.render("campgrounds/edit", {campground: foundCampground});
	});
});

// Route som gjør at man kan oppdatere et campingplass:
router.put("/:id", middleware.checkCampgroundOwnership, function(req, res){
    console.log("Oppdaterer campingplass...\n");
    campground.findOneAndUpdate(req.params.id, req.body.campground, function(err, updatedCampground){
        if(err){
            console.log("Kan ikke oppdatere campingplass");
	    req.flash("error", "Kan ikke oppdatere campingplass: " + err.message);
	    res.redirect("/campgrounds/:id");
        }
        else{
	    req.flash("success", "Campingplassen ble oppdatert uten problemer");
            res.redirect("/campgrounds/" + req.params.id);
        }
    });
});

// Slett campingplass
router.delete("/:id", middleware.checkCampgroundOwnership, function(req,res){
    campground.findOneAndDelete(req.params.id, function(err){
        if(err){
            console.log("Kan ikke slette campingplass: " + err);
	    req.flash("error", "Kan ikke slette campingplass: " + err.message);
            res.redirect("/campgrounds/");
        }
        else{
	    req.flash("success", "Campingplassen ble slettet fra databasen.");
            res.redirect("/campgrounds/");
        }
    })
});

// Middleware
function isLoggedIn(req, res, next)
{
    if(req.isAuthenticated()){
	return next();
    }
    req.flash("error", "Du må logge inn for å kunne legge inn en ny campingplass.");
    res.redirect("/login?redirfrom="+req.headers.referer + req.path);
}

module.exports = router;