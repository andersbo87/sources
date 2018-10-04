var obj = {
	name: "Chuck",
	age: 45,
	isCool: false,
	friends: ["bob", "tina"],
	add: function(x, y){
		return x + y;
	}
}

document.write(obj.add(10, 5) + "<br>");
var dogSpace = {};
var catSpace = {};
dogSpace.speak = function() {
	return "Voff!";
}

catSpace.speak = function() {
	return "Mjau!";
}
document.write(catSpace.speak() + " " + dogSpace.speak() + "<br>");

var comments = {};
comments.data = ["Godt jobba!","Farvel"];
comments.print = function() {
	this.data.forEach(function(el){
		document.write(el + "<br>");
	});
}

comments.print();