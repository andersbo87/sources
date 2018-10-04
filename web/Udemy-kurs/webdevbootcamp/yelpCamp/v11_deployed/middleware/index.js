var campground = require("../models/campground");
var comment = require("../models/comment");
var middlewareObj = {};

middlewareObj.checkCampgroundOwnership = function(req, res, next){
    if(req.isAuthenticated()){
        campground.findById(req.params.id, function(err, foundCampground){
	    if(err){
		req.flash("error", "En feil har oppstått:\n" + err);
		res.redirect("back");
	    }
	    else if(!foundCampground){
		req.flash("error", "Campingplassen finnes ikke.");
		res.redirect("back");
	    }
	    else {
		// Eier brukeren denne campingplassen?
		if(foundCampground.author.id.equals(req.user._id)){
		    next(); // Vis siden om det aktuelle camptingstedet.
		}
		else{
		    req.flash("error", "Du har ikke tillatelse til å gjøre dette.");
		    res.redirect("back");
		}
	    }
	});
    }
    // Hvis ikke, rediriger til et sted.
    else{
	req.flash("error","Du må logge deg inn for å gjøre dette.");
        res.redirect("back");
    }
};

middlewareObj.checkCommentOwnership = function(req, res, next){
    if(req.isAuthenticated()){
        comment.findById(req.params.comment_id, function(err, foundComment){
	    if(err){
		req.flash("error", "En feil har oppstått:\n" + err);
		res.redirect("back");
	    }
	    else if(!foundComment){
		req.flash("error", "Kommentaren finnes ikke.");
		res.redirect("back");
	    }
	    else{
		// Eier brukeren denne kommentaren?
		if(foundComment.author.id.equals(req.user._id)){
		    next(); // Vis siden om den aktuelle kommentaren.
		}
		else{
		    req.flash("error", "Du har ikke tillatelse til å gjøre dette.");
		    res.redirect("back");
		}
	    }
	});
    }
    // Hvis ikke, går vi en side tilbake.
    else{
	req.flash("error", "Du må logge deg inn for å kunne gjøre dette.");
        res.redirect("back");
    }
};

module.exports = middlewareObj;