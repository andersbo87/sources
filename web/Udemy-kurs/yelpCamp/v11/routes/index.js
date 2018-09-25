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
	    req.flash("error", "Kan ikke registrere bruker: " + err.message);
	    return res.redirect("register");
	}
	passport.authenticate("local")(req, res, function () {
	    req.flash("success", "Velkommen ombord, " + req.body.username);
	    res.redirect("/campgrounds");
	});
    });
});

//Login
router.get("/login", function (req, res) {
    // Kode for å lese vedlagt streng.
    // Dersom redirfrom eksisterer, skal vi
    // redirigere til denne siden fremfor
    // det som er lagret i req.headers.referer.
    if(req.query.redirfrom)
        res.render("login", {referer:req.query.redirfrom});
    else    
        res.render("login", {referer:req.headers.referer});
});
// Kode som tar seg av selve innlogginga:
router.post("/login", passport.authenticate("local", {failureRedirect: "/login"}), (req, res) => {
    if (req.body.referer && (req.body.referer !== undefined && req.body.referer.slice(-6) !== "/login")) {
        //res.redirect(req.body.referer);
	req.flash("success", "Velkommen tilbake, " + req.body.username);
        res.redirect(req.body.referer);
    } else {
        res.redirect("/campgrounds");
    }
});

// Logout
router.get("/logout", function(req, res){
    req.logout();
    req.flash("success", "Du ble logget ut.");
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