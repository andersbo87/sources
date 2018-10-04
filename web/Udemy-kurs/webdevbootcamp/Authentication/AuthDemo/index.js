var bodyParser 			  = require("body-parser"),
	 express 				  = require("express"),
	 localStrategy 		  = require("passport-local"),
	 mongoose 				  = require("mongoose"),
	 passport 				  = require("passport"),
	 passportLocalMongoose = require("passport-local-mongoose"),
	 user						  = require("./models/user");

// Oppsett av nøddvendige saker og ting
mongoose.connect("mongodb://localhost/auth_demo_app", { useNewUrlParser: true});

app = express();
app.set('view engine', 'ejs');
app.use(bodyParser.urlencoded({extended: true}));
app.use(require("express-session")({
	secret			  : "Dette er virkelig gøy",
	resave			  : false,
	saveUninitialized: false
}));
app.use(express.static(__dirname + "/public"));
app.use(passport.initialize());
app.use(passport.session());

passport.use(new localStrategy(user.authenticate()));
passport.serializeUser(user.serializeUser());
passport.deserializeUser(user.deserializeUser());

// "Ruter"
app.get("/", function(req, res){
	res.render("home");
});

app.get("/secret", isLoggedIn, function(req, res){
	res.render("secret");
});

// Autentiseringsruter
app.get("/register", function(req, res){
	res.render("register");
});

// Registrering:
app.post("/register", function(req, res){
	var newUsername     = req.body.username,
		 newPassword = req.body.password;
	user.register(new user({username: newUsername}), newPassword, function(err, newUser){
		if(err){
			console.log("Kan ikke legge til ny bruker: " +err);
			//res.status(400).send(err);
			return res.render("register");	
		}
		passport.authenticate("local")(req, res, function(){
			res.render("/secret");	
		});
	});
});
// Slutt registrering.

// Innlogging
app.get("/login", function (req, res) {
	res.render("login")
});
app.post("/login", passport.authenticate("local", {
	successRedirect: "/secret",
	failureRedirect: "/login"
}), function (req, res) {
	var userName = req.body.username,
		 userPass = req.body.password;
});
// Slutt innlogging

// "Utlogging"
app.get("/logout", function(req, res) {
	req.logout();
	res.redirect("/");
});
// Slutt på utloggingskode

function isLoggedIn(req, res, next){
	if(req.isAuthenticated()){
		return next();
	}
	else {
		res.redirect("/login");
	}
}

// Linjen i koden under kan også skrives sliK:
// app.listen(process.env.PORT, function(){console.log("Serving on port 3000")});
// Dette gjelder først og fremst om du bruker en skytjeneste til å "hoste" siden.
// Kjører du Node lokalt, kan du bruke følgende ukommenterte kode:
app.listen(3000, process.env.IP, function(){
	console.log("Autentiseringsserveren har startet…");
}); 