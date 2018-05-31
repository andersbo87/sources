var express = require('express'),
	app     = express(),
	bodyParser = require('body-parser'),
	pg = require('pg');
	methodOverride 	= require("method-override");

// Oppsett av databasetilkobling:
var connString = process.env.DATBASE_URL || 'postgres://user:passwd@localhost:5432/jobber';	
var client = new pg.Client(connString);
client.connect();

app.use(bodyParser.urlencoded({extended: true}));
// views is directory for all template files
app.set('views', __dirname + '/views');
app.set("view engine", "ejs");
app.use(express.static("public"));
app.use(methodOverride("_method"));

// RESTful routes for jobber:
app.get("/", function(req, res){
	res.redirect("/jobb");
});

app.get("/jobb/", function(req, res){
	
	client.query("SELECT soknadid, tittel, bedrift FROM soknad ORDER BY soknadid ASC", function(err, result){
		//done();
		if(err){
			console.log("Kan ikke hente data: " + err);
			res.status(400).send(err);
		}
		else
			res.render("index", {data: result.rows});
	});
});

// Ny jobb
app.get("/jobb/newjob", function(req, res){
	res.render("newjob");
});

app.post("/jobb", function(req, res){
	var tittel = req.body.tittel,
		bedrift = req.body.bedrift,
		stedid = req.body.stedid,
		statusid = req.body.statusid,
		soknadsfrist = req.body.soknadsfrist,
		motivasjon = req.body.motivasjon; 
	client.query("INSERT INTO soknad (tittel, bedrift, stedid, statusid, soknadsfrist, motivasjon) values ('" + tittel + "', '" + bedrift + "', " + stedid + ", " + statusid + ", '" + soknadsfrist + "', '" + motivasjon + "')", function(err, nyJobb){
		if(err){
			console.log("Kan ikke opprette den nye jobben: " + err);
			res.status(400).send(err);
		}
		else {
			res.redirect("/jobb");
		}
	});
});
// Slutt ny jobb

// Vis angitt jobb basert på unik ID:
app.get("/jobb/:id", function(req, res){
	client.query("SELECT soknadid, tittel, bedrift, stedid, statusid, soknadsfrist, motivasjon FROM soknad WHERE soknadid = " + req.params.id, function(err, result){
		if(err) {
			console.log("Kan ikke hente data: " + err);
			res.status(400).send(err);
		}
		else {
			res.render("show", {data: result.rows});
		}
	});
});

// Oppdater angitt jobb basert på unik ID:
app.get("/jobb/:id/edit", function(req, res){
	client.query("SELECT soknadid, tittel, bedrift, stedid, statusid, soknadsfrist, motivasjon FROM soknad WHERE soknadid = " + req.params.id, function(err, result){
		if(err){
			console.log("Kan ikke hente data: " + err);
			res.status(400).send(err);
		}
		else
			res.render("editjob", {jobb: result.rows});
	});
});
app.put("/jobb/:id", function(req, res){
	// Do something
	// Henter dataene i de ulike tekstboksene og lagrer disse i variabler:
	var soknadid = req.params.id,
		tittel = req.body.tittel,
		bedrift = req.body.bedrift,
		stedid = req.body.stedid,
		statusid = req.body.statusid,
		soknadsfrist = req.body.soknadsfrist,
		motivasjon = req.body.motivasjon;

	// Generer en SQL-spørring:
	var qry = "UPDATE soknad SET tittel='" + tittel + "', bedrift='" + bedrift + "', stedid=" + stedid +", statusid=" + statusid + ", soknadsfrist='" + soknadsfrist + "', motivasjon='" + motivasjon + "' WHERE soknadid=" + soknadid;

	// Gjennomfører endringen
	client.query(qry, function(err, result){
		if(err){
			console.log("Kan ikke oppdatere data: " + err);
			res.status(400).send(err);
		}
		else
			res.redirect("/jobb");
	});
	//res.send("Du har kommet til ruten for å oppdatere en eksisterende jobb.");
});

// Slett jobb basert på angitt ID:
app.delete("/jobb/:id", function(req, res){
	// Do something.
	var id = req.params.id;
	var qry = "DELETE FROM soknad WHERE soknadid=" + id;
	client.query(qry, function(err, result){
		if(err){
			console.log("Kan ikke slette data: " + err);
			res.status(400).send(err);
		}
		else
			res.redirect("/jobb");
	});
});

// RESTful routes for steder:
app.get("/by", function(req, res){
	client.query("SELECT stedid, stedsnavn, landid, land FROM view_sted ORDER BY stedid ASC", function(err, result){
		//done();
		if(err){
			console.log("Kan ikke hente data: " + err);
			res.status(400).send(err);
		}
		else
			res.render("cities", {data: result.rows});
	});
});

app.get("/by/nyby", function(req, res){
	res.render("newcity");
});

app.post("/by", function(req, res){
	var stedsnavn = req.body.stedsnavn,
		landid    = req.body.landid;
	var qry = "INSERT INTO sted (stedsnavn, landid) VALUES('" + stedsnavn + "', " + landid + ")";
	client.query(qry, function(err){
		if(err){
			console.log("Kan ikke sette inn en ny by: " + err);
			res.status(400).send(err);
		}
		else{
			res.redirect("/by");
		}
	});
});

app.get("/by/:id", function(req, res){
	var id = req.params.id;
	var qry = "SELECT stedid, stedsnavn, landid, land FROM view_sted WHERE stedid=" + id;
	client.query(qry, function(err, result){
		if(err){
			console.log("Kan ikke hente data: " + err);
			res.status(400).send(err);
		}
		else
			res.render("showcity", {data: result.rows});
	});
});

app.get("/by/:id/redigerby", function(req, res){
	client.query("SELECT stedid, stedsnavn, landid FROM sted WHERE stedid = " + req.params.id, function(err, result){
		if(err){
			console.log("Kan ikke hente data: " + err);
			res.status(400).send(err);
		}
		else
			res.render("editcity", {by: result.rows});
	});
});

app.put("/by/:id", function(req, res){
	var stedid    = req.params.id,
		stedsnavn = req.body.stedsnavn;
		landid    = req.body.landid;
	var qry = "UPDATE sted SET stedsnavn='" + stedsnavn + "', landid=" + landid + " WHERE stedid=" + stedid;
	client.query(qry, function(err, oppdatertBy){
		if(err){
			console.log("Kan ikke oppdatere byen: " + err);
			res.status(400).send(err);
		}
		else
			res.redirect("/by");
	});
});

app.delete("/by/:id", function(req, res){
	var stedid = req.params.id;
	var qry = "DELETE FROM sted WHERE stedid=" + stedid;
	client.query(qry, function(err){
		if(err)
		{
			console.log("Kan ikke slette stedet/byen: " + err);
			res.status(400).send(err);
		}
		else
			res.redirect("/by");
	});
});

// RESTful routes for land:
app.get("/land", function(req, res){
	var qry = "SELECT landid, land FROM land ORDER by LANDID asc";
	client.query(qry, function(err, land){
		if(err) {
			console.log("Kan ikke vise oversikt over land: " + err);
			res.status(400).send(err);
		}
		else
			res.render("countries", {data: land.rows});
	});
});

app.get("/land/nyttland", function(req, res){
	res.render("newcountry");
});

app.post("/land", function(req, res){
	var landnavn = req.body.landnavn;
	var qry = "INSERT INTO land (land) VALUES('" + landnavn + "')";
	client.query(qry, function(err){
		if(err) {
			console.log("Kan ikke sette inn det nye landet: " + err);
			res.status(400).send(err);
		}
		else
			res.redirect("/land");
	});
});

app.get("/land/:id", function(req, res){
	var landid = req.params.id;
	var qry = "SELECT landid, land FROM land WHERE landid=" + landid;
	client.query(qry, function(err, land){
		if(err) {
			console.log("Kan ikke hente informasjon om dette landet: " + err);
			res.status(400).send(err);
		}
		else
			res.render("showcountry", {data: land.rows});
	});
});

app.get("/land/:id/redigerland", function(req, res){
	var landid = req.params.id;
	var qry = "SELECT landid, land FROM land WHERE landid=" + landid;
	client.query(qry, function(err, land){
		if(err) {
			console.log("Kan ikke hente informasjon om dette landet: " + err);
			res.status(400).send(err);
		}
		else
			res.render("editcountry", {data: land.rows});
	});
});

app.put("/land/:id", function(req, res){
	var landid = req.params.id,
		landnavn = req.body.landnavn;
	var qry ="UPDATE land SET land='" + landnavn + "' WHERE landid =" + landid;
	client.query(qry, function(err){
		if(err) {
			console.log("Kan ikke oppdatere landet: " + err);
			res.status(400).send(err);
		}
		else
			res.redirect("/land");
	});
});

app.delete("/land/:id", function(req, res){
	var id = req.params.id;
	var qry = "DELETE FROM land WHERE landid=" + id;
	client.query(qry, function(err){
		if(err) {
			console.log("Kan ikke slette landet: " + err);
			res.status(400).send(err);
		}
		else
			res.redirect("/land");
	});
});

// RESTful routes for statuser:
app.get("/status", function(req, res){
	var qry = "SELECT statusid, status FROM status ORDER BY statusid";
	client.query(qry, function(err, status){
		if(err) {
			console.log("Kan ikke hente oversikt over statuser: " + err);
			res.status(400).send(err);
		}
		else
			res.render("statuses", {data: status.rows});
	});
});

app.get("/status/nystatus", function(req, res){
	res.render("newstatus");
});

app.post("/status", function(req, res){
	var status = req.body.status;
	var qry = "INSERT INTO status (status) VALUES('" + status + "')";
	client.query(qry, function(err){
		if(err) {
			console.log("Kan ikke sette inn den nye statusen: " + err);
			res.status(400).send(err);
		}
		else
			res.redirect("/status");
	});
});

app.get("/status/:id", function(req, res){
	var id = req.params.id;
	var qry = "SELECT statusid, status FROM status WHERE statusid=" + id;
	client.query(qry, function(err, status){
		if(err) {
			console.log("Kan ikke hente informasjon om angitt status: " + err);
			res.status(400).send(err);
		}
		else
			res.render("showstatus", {data: status.rows});
	});
});

app.get("/status/:id/redigerstatus", function(req, res){
	var id = req.params.id;
	var qry = "SELECT statusid, status FROM status WHERE statusid=" + id;
	client.query(qry, function(err, status){
		if(err) {
			console.log("Kan ikke hente status: " + err);
			res.status(400).send(err);
		}
		else
			res.render("editstatus", {data: status.rows});
	});
});

app.put("/status/:id", function(req, res){
	var id = req.params.id,
		statusnavn = req.body.status;
	var qry = "UPDATE status SET status='" + statusnavn + "' WHERE statusid=" + id;
	client.query(qry, function(err){
		if(err) {
			console.log("Kan ikke oppdatere statusen: " + err);
			res.status(400).send(err);
		}
		else
			res.redirect("/status");
	});
});

app.delete("/status/:id", function(req, res){
	var statusid = req.params.id;
	var qry = "DELETE FROM status WHERE statusid=" + statusid;
	client.query(qry, function(err){
		if(err) {
			console.log("Kan ikke slette statusen: " + err);
			res.status(400).send(err);
		}
		else
			res.redirect("/status");
	});
});

// Linjen i koden under kan også skrives sliK:
// app.listen(process.env.PORT, function(){console.log("Serving on port 3000")});
// Dette gjelder først og fremst om du bruker en skytjeneste til å "hoste" siden.
// Kjører du Node lokalt, kan du bruke følgende ukommenterte kode:
app.listen(3000, process.env.IP, function(){
	console.log("Serveren har startet…");
});
