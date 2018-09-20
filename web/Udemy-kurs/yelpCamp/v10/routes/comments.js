var express = require("express");
var router = express.Router({mergeParams: true});
var campground = require("../models/campground");
var comment = require("../models/comment");
var middleware = require("../middleware/");

// Viser skjemaet som lar brukeren skrive en ny kommentar
router.get("/new", isLoggedIn, function(req, res){
    campground.findById(req.params.id, function(err, campground){
	if(err){
	    console.log(err);
	    res.status(400).send(err);
	}
	else{
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
	else{
	    comment.create(req.body.comment, function(err, comment){
		if(err){
		    console.log(err);
		    res.status(400).send(err);
		}
		else{
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

// Kode for å redigere en kommentar
router.get("/:comment_id/edit", middleware.checkCommentOwnership, function(req, res){
    comment.findById(req.params.comment_id, function(err, foundComment){
	if(err){
	    console.log("En feil har oppstått: " + err);
	    res.redirect("back");
	}
	else{
	    res.render("comments/edit", {campground_id: req.params.id, comment: foundComment});
	}
    });
});

// Gjennomføre oppdateringa:
router.put("/:comment_id", middleware.checkCommentOwnership, function(req, res){
    comment.findOneAndUpdate({"_id": req.params.comment_id}, req.body.comment, function(err, updatedComment){
	if(err){
	    console.log("Kan ikke oppdatere kommentar: " + err);
	    //res.status(400).send(err);
	    res.redirect("back");
	}
	else{
	    res.redirect("/campgrounds/" + req.params.id);
	}
    });
});

// Comments destroy -- slett en kommentar
router.delete("/:comment_id", middleware.checkCommentOwnership, function(req, res){
    comment.findOneAndDelete({"_id" :req.params.comment_id}, function(err){
	if(err) {
	    console.log("Kan ikke slette kommentaren: " + err);
	    res.redirect("back");
	}
	else {
	    res.redirect("/campgrounds/" + req.params.id);
	}
    });
});

// Middleware
function isLoggedIn(req, res, next)
{
    if(req.isAuthenticated()){
	return next();
    }
    res.redirect("/login?redirfrom="+req.headers.referer + "/comments" + req.path);
}

module.exports = router;