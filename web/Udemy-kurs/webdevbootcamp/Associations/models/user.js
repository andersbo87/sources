var mongoose = require('mongoose');
// bruker: Navn, e-post
var userSchema = new mongoose.Schema({
	email: String,
	name: String,
	posts: [
	{
		type: mongoose.Schema.Types.ObjectId,
		ref: "Post"
	}
	]
});

module.exports = mongoose.model("User", userSchema);