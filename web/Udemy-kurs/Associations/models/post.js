var mongoose = require('mongoose');
// innlegg: tittel, innhold
var postSchema = new mongoose.Schema({
	title: String,
	content: String
});
module.exports = mongoose.model("Post", postSchema); 