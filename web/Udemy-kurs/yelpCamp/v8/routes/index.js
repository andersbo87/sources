var express = require("express");
var router = express.Router();
var passport = require("passport");
var user = require("../models/user");

// Rotsiden
router.get("/",function(req, res){
    // Put in some code here...
    res.render("landing");
});

// Skjema for brukerregistrering:
router.get("/register", function(req, res){
    res.render("register")
});

// Kode som tar seg av registrering
router.post("/register", function(req, res){
    var newUser = new user({username: req.body.username}),
	passwd = req.body.password; 
    user.register(newUser, passwd, function(err, addedUser){
	if(err)
	{
	    console.log("Kan ikke registrere bruker: " + err);
	    //res.status(400).send(err);
	    return res.render("register");
	}
	passport.authenticate("local")(req, res, function () {
	    res.redirect("/campgrounds");
	});
    });
});

//Login
router.get("/login", function (req, res) {
    res.render("login");
});
// Kode som tar seg av selve innlogginga:
router.post("/login", passport.authenticate("local",{
    successRedirect: "/campgrounds",
    failureRedirect: "/login"
}), function (res, res) {
});

// Logout
router.get("/logout", function(req, res){
    req.logout();
    res.redirect("/campgrounds");
});

function isLoggedIn(req, res, next)
{
    if(req.isAuthenticated()){
	return next();
    }
    res.redirect("/login");
}

module.exports = router;