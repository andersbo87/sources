var express   	   = require("express"), 
    bodyParser 	   = require("body-parser"),
    app 	   = express(),
    mongoose   	   = require('mongoose'),
    flash          = require('connect-flash'),
    methodOverride = require('method-override'),
    campground 	   = require('./models/campground'),
    comment    	   = require("./models/comment"),
    passport	   = require("passport"),
    localStrategy  = require("passport-local"),
    user       	   = require("./models/user");

 // Importerer routes som er lagret i andre filer
 var commentRoutes = require("./routes/comments"),
     campgroundRoutes = require("./routes/campgrounds"),
     indexRoutes = require("./routes/index");
var url = process.env.DATABASEURL || "mongodb://localhost/yelp_camp_v11";
mongoose.connect(url, { useNewUrlParser: true });
app.use(bodyParser.urlencoded({extended: true}));
app.set("view engine", "ejs");
app.use(express.static(__dirname + "/public"));
app.use(methodOverride("_method"));
app.use(flash());
//seedDB(); // Legger inn testdata i databasen.

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
    res.locals.error       = req.flash("error");
    res.locals.success     = req.flash("success");
    next();
});

app.use(indexRoutes);
app.use("/campgrounds/:id/comments", commentRoutes);
app.use("/campgrounds", campgroundRoutes);

// Linjen i koden under kan også skrives sliK:
// app.listen(process.env.PORT, function(){console.log("Serving on port 3000")});
// Dette gjelder først og fremst om du bruker en skytjeneste til å "hoste" siden.
// Kjører du Node lokalt, kan du bruke følgende ukommenterte kode:
var port = process.env.PORT || 3000;
app.listen(port, process.env.IP, function(){
	console.log("YelpCamp-server has started on port " + port + " …");
}); 
