var express    		 = require("express"),
	expressSanitizer = require("express-sanitizer"),
	app        		 = express(),
	bodyParser 		 = require("body-parser"),
	mongoose   		 = require("mongoose"),
	methodOverride 	 = require("method-override");


mongoose.connect("mongodb://localhost/blog");

// Konfigurasjon av selve programmet
app.use(bodyParser.urlencoded({extended: true}));
app.use(expressSanitizer());
app.set("view engine", "ejs");
app.use(express.static("public"));
app.use(methodOverride("_method"));

// Konfigurasjon av MongoDB/Mongoose
var blogSchema = new mongoose.Schema({
	title: String,
	image: String,
	body:  String,
	created:{type: Date, default: Date.now}
});

var blog = mongoose.model("Blog", blogSchema);

// RESTful "Ruter"
app.get("/", function(req, res){
	res.redirect("/blogs");
});
app.get("/blogs", function(req, res){
	blog.find({}, function(err, blogs){
		if(err){
			console.log("En feil har oppstått: " + err);
		}
		else
		{
			res.render("index", {blogs: blogs});
		}
	});
});

// rute for "nytt" innlegg
app.get("/blogs/new", function(req, res){
	res.render("new");
});

// Opprett et nytt innlegg
app.post("/blogs", function(req, res){
	req.body.blog.body = req.sanitize(req.body.blog.body);
	blog.create(req.body.blog, function(err, newBlog){
		if(err)
			//console.log("Noe gikk galt under oppretting av blogginnlegg: " + err);
			res.render("new");
		else{
			res.redirect("/blogs");
		}
	});
});

// Rute som gjør at vi kan vise innhold
app.get("/blogs/:id", function(req, res){
	blog.findById(req.params.id, function(err, foundBlog){
		if(err){
			console.log("Noe gikk galt under henting av data: " + err);
		}
		else {
			res.render("show", {blog: foundBlog});
		}
	});
});

// Redigere et eksisterende innlegg:
app.get("/blogs/:id/edit", function(req, res){
	blog.findById(req.params.id, function(err, foundBlog){
		if(err){
			console.log("Noe gikk galt. Kunne ikke hente data for oppdaternig: " + err);
			res.redirect("/blogs");
		}
		else
		{
			res.render("edit", {blog: foundBlog});
		}
	});
	
});

// Oppdatere det eksisterende innlegget:
app.put("/blogs/:id", function(req, res){
	req.body.blog.body = req.sanitize(req.body.blog.body);
	blog.findByIdAndUpdate(req.params.id, req.body.blog, function(err, updatedBlog){
		if(err){
			console.log("Noe gikk galt under oppdatering: " + err);
			res.redirect("/blogs");
		}
		else
		{
			res.redirect("/blogs/" + req.params.id);
		}
	});
});

// Slette et eksisterende innlegg
app.delete("/blogs/:id", function(req, res){
	blog.findByIdAndRemove(req.params.id, function(err){
		if(err){
			console.log("Kan ikke slette dataen fra databasen: " + err);
			res.redirect("/blogs");
		}
		else
		{
			res.redirect("/blogs");
		}
	});
});

// Linjen i koden under kan også skrives sliK:
// app.listen(process.env.PORT, function(){console.log("Serving on port 3000")});
// Dette gjelder først og fremst om du bruker en skytjeneste til å "hoste" siden.
// Kjører du Node lokalt, kan du bruke følgende ukommenterte kode:
app.listen(3000, process.env.IP, function(){
	console.log("Serveren har startet…");
});