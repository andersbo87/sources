var campground = require("../models/campground");
var comment = require("../models/comment");
var middlewareObj = {};

middlewareObj.checkCampgroundOwnership = function(req, res, next){
    if(req.isAuthenticated()){
        campground.findById(req.params.id, function(err, foundCampground){
	    if(err){
		console.log("En feil har oppstått:\n" + err);
		res.redirect("back");
	    }
	    else {
		// Eier brukeren denne campingplassen?
		if(foundCampground.author.id.equals(req.user._id)){
		    next(); // Vis siden om det aktuelle camptingstedet.
		}
		else{
		    res.redirect("back");
		}
	    }
	});
    }
    // Hvis ikke, rediriger til et sted.
    else{
        console.log("Brukeren er ikke logget inn.");
        res.redirect("back");
    }
};

middlewareObj.checkCommentOwnership = function(req, res, next){
    if(req.isAuthenticated()){
        comment.findById(req.params.comment_id, function(err, foundComment){
	    if(err){
		console.log("En feil har oppstått:\n" + err);
		res.redirect("back");
	    }
	    else{
		// Eier brukeren denne kommentaren?
		if(foundComment.author.id.equals(req.user._id)){
		    next(); // Vis siden om den aktuelle kommentaren.
		}
		else{
		    res.redirect("back");
		}
	    }
	});
    }
    // Hvis ikke, går vi en side tilbake.
    else{
        console.log("Brukeren er ikke logget inn.");
        res.redirect("back");
    }
};

module.exports = middlewareObj;