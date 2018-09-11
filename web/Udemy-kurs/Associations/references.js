var mongoose = require("mongoose");
mongoose.connect("mongodb://localhost/blog_demo_2");

var post = require("./models/post"),
	 user = require("./models/user");


/*user.create({
	email: "bob@gmail.com",
	name: "Bob Hansen"
});*/


post.create({
	title: "Hvordan man lager den beste hamburgeren del 4",
	content: "Det er helt sant at dette bare er TullTullTullTullTullTullTullTullTullTullTull."
}, function(err, post){
	if(err){
		console.log(err);
	}
	else{
		user.findOne({email: "bob@gmail.com"}, function(err, foundUser){
			if(err){
				console.log(err);
			}
			else{
				foundUser.posts.push(post);
				foundUser.save(function (err, data) {
					if(err)
						console.log(err);
					else
						console.log(data);
				});
			}
		});		
	}
});


// Finn bruker og deretter finn alle innlegg skrevet av denne brukeren:
/*
user.findOne({email: "bob@gmail.com"}).populate("posts").exec(function (err, user){
	if(err)
		console.log(err);
	else {
		console.log(user);
	}
});
*/
