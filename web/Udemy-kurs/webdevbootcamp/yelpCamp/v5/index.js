var express   = require("express"), 
	bodyParser = require("body-parser"),
	app 	     = express(),
	mongoose   = require('mongoose'),
	campground = require('./models/campground'),
	comment    = require("./models/comment"),
	user       = require("./models/user"),
	seedDB	  = require("./seed")

seedDB();
mongoose.connect("mongodb://localhost/yelp_camp_v3");

app.use(bodyParser.urlencoded({extended: true}));
app.set("view engine", "ejs");
app.use(express.static(__dirname + "/public"));
console.log("wd: " + __dirname);
/*campground.create(
	{
		name: "Granite Hill", 
		image: "https://pixabay.com/get/ea36b7062bf6093ed1584d05fb1d4e97e07ee3d21cac104497f6c17aa1efb2bf_340.jpg",
		description: "Dette er et campingsted som ligger på et område med mye granitt. Her er det ikke innlagt vann. Mye vakker granitt!"
	}, function(err, campground){
		if(err)
			console.log("Noe har gått galt: " + err);
		else
			console.log("Opprettet følgende campingsted:\n" + campground);
	}
);*/

app.get("/",function(req, res){
	// Put in some code here...
	res.render("landing");
});

app.get("/campgrounds/new",function(req, res){
	// Put in some code here...
	res.render("campgrounds/new.ejs");
});

app.post("/campgrounds", function(req, res){
	// hente data fra skjemaet og legge til i tabellen
	var name = req.body.name; 
	var image = req.body.image;
	var description = req.body.description;
	var newCampground = {name: name, image: image, description: description};
	// Opprett et nytt campingsted og lagre dette i databasen:
	campground.create(newCampground,function(err, newCampground){
		if(err)
			console.log("Kunne ikke lagre det nye campingstedet i databasen:\n" + err);
		else
		{
			// gå tilbake til campgrounds-siden.
			res.redirect("/campgrounds");
		}		
	});
});

app.get("/campgrounds", function(req, res){
	// Get all campgrounds from the database
	campground.find({}, function(err, allCampgrounds){
		if(err)
			console.log("Noe har gått galt:\n" + err);
		else
		{
			res.render("campgrounds/index", {campgrounds: allCampgrounds});		
		}
	});
	//res.render("campgrounds", {campgrounds: campgrounds});
});


 // SHOW - viser info om gitt campingsted.
app.get("/campgrounds/:id", function(req, res){
	// Finn campingsted med angitt ID.
	campground.findById(req.params.id).populate("comments").exec(function(err, foundCampground){
		if(err)
			console.log("En feil har oppstått:\n" + err);
		else {
			// Vis siden om det aktuelle camptingstedet.
			console.log(foundCampground);
			res.render("campgrounds/show", {campground: foundCampground});		
		}
	});
});

// Restful routes for comments
app.get("/campgrounds/:id/comments/new", function(req, res){
	campground.findById(req.params.id, function(err, campground)
	{
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

app.post("/campgrounds/:id/comments", function(req, res){
	campground.findById(req.params.id, function(err, campground){
		if(err){
			console.log(err);
			res.status(400).send(err);
		}
		else
		{

			comment.create(req.body.comment, function(err, comment)
			{
				if(err){
					console.log(err);
					res.status(400).send(err);
				}
				else
				{
					campground.comments.push(comment);
					campground.save();
					res.redirect("/campgrounds/" + campground._id);
				}
			});
		}
	});
});


// Linjen i koden under kan også skrives sliK:
// app.listen(process.env.PORT, function(){console.log("Serving on port 3000")});
// Dette gjelder først og fremst om du bruker en skytjeneste til å "hoste" siden.
// Kjører du Node lokalt, kan du bruke følgende ukommenterte kode:
app.listen(3000, process.env.IP, function(){
	console.log("YelpCamp-serveren har startet…");
}); 
