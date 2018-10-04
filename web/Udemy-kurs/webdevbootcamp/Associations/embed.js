var mongoose = require("mongoose");
mongoose.connect("mongodb://localhost/blog_demo");

// innlegg: tittel, innhold
var postSchema = new mongoose.Schema({
	title: String,
	content: String
});
var post = mongoose.model("Post", postSchema);

// bruker: Navn, e-post
var userSchema = new mongoose.Schema({
	email: String,
	name: String,
	posts: [postSchema]
});

var user = mongoose.model("User", userSchema);

/*var newUser = new user({
	email: "veronica@lodge.no",
	name: "Veronica Lodge",
});
newUser.posts.push({
	title: "Veronica's first post",
	content: "This is Veronica Lodge's first post."
});
newUser.save(function(err, user){
	if(err)
		console.log(err);
	else
		console.log(user);
});*/
/*
var newPost = new post({
	title: "Testeinnlegg",
	content: "Dette er et innlegg for å teste om alt fungerer som det skal."
});
newPost.save(function(err, post){
	if(err)
		console.log(err);
	else
		console.log(post);
});*/


user.findOne({name: "Veronica Lodge"}, function(err, user){
	console.log("Trying to find user Veronica Lodge…");
	if(err)
		console.log(err);
	else{
		console.log(user);
		console.log("Adding another post as user Veronica Lodge…");
		user.posts.push({
			title: "2 persons I love",
			content: "I love Betty Cooper and Archie Andrews"
		});
		user.save(function(err, user){
			if(err)
				console.log(err);
			else
				console.log(user);
		});
	}
});