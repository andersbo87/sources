var express   		= require("express"), 
    bodyParser 	= require("body-parser"),
    app 	     		= express(),
    mongoose   	= require('mongoose'),
    campground 	= require('./models/campground'),
    comment    	= require("./models/comment"),
    passport	  	= require("passport"),
    localStrategy = require("passport-local"),
    user       	= require("./models/user"),
    seedDB	  		= require("./seed");

 // Importerer routes som er lagret i andre filer
 var commentRoutes = require("./routes/comments"),
 	 campgroundRoutes = require("./routes/campgrounds"),
 	 indexRoutes = require("./routes/index");


mongoose.connect("mongodb://localhost/yelp_camp_v6", { useNewUrlParser: true});
app.use(bodyParser.urlencoded({extended: true}));
app.set("view engine", "ejs");
app.use(express.static(__dirname + "/public"));
seedDB();

/*
Passport configuration
*/
app.use(require("express-session")({
    secret: "Camping is cool",
    resave: false,
    saveUninitialized: false
}));
app.use(passport.initialize());
app.use(passport.session());
passport.use(new localStrategy(user.authenticate()));
passport.serializeUser(user.serializeUser());
passport.deserializeUser(user.deserializeUser());

app.use(function(req, res, next){
    res.locals.currentUser = req.user;
    next();
});

app.use(indexRoutes);
app.use("/campgrounds/:id/comments", commentRoutes);
app.use("/campgrounds", campgroundRoutes);

// Linjen i koden under kan også skrives sliK:
// app.listen(process.env.PORT, function(){console.log("Serving on port 3000")});
// Dette gjelder først og fremst om du bruker en skytjeneste til å "hoste" siden.
// Kjører du Node lokalt, kan du bruke følgende ukommenterte kode:
app.listen(3000, process.env.IP, function(){
	console.log("YelpCamp-serveren har startet…");
}); 
