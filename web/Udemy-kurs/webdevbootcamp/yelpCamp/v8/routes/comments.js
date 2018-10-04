var express = require("express");
var router = express.Router({mergeParams: true});
var campground = require("../models/campground");
var comment = require("../models/comment");

// Viser skjemaet som lar brukeren skrive en ny kommentar
router.get("/new", isLoggedIn, function(req, res){
    campground.findById(req.params.id, function(err, campground){
	if(err){
	    console.log(err);
	    res.status(400).send(err);
	}
	else
	{
	    res.render("comments/new.ejs", {campground: campground});
	}
    });
});

// Opprett ny kommentar
router.post("/", isLoggedIn, function(req, res){
    campground.findById(req.params.id, function(err, campground){
	if(err){
	    console.log(err);
	    res.status(400).send(err);
	}
	else
	{
	    
	    comment.create(req.body.comment, function(err, comment){
		if(err){
		    console.log(err);
		    res.status(400).send(err);
		}
		else
		{
			// Legg til brukernavn og -ID i kommentaren
			comment.author.id = req.user._id;
			comment.author.username = req.user.username;
			// Lagre innhold
			comment.save();
		    campground.comments.push(comment);
		    campground.save();
		    console.log(comment);
		    res.redirect("/campgrounds/" + campground._id);
		}
	    });
	}
    });
});

function isLoggedIn(req, res, next)
{
    if(req.isAuthenticated()){
	return next();
    }
    res.redirect("/login");
}

module.exports = router;