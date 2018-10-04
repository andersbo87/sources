var faker = require('faker');


function printFakeNameAndPrice()
{
	for(var i = 1; i <= 10; i++){
		//console.log(faker.fake("{{commerce.productName}}, {{commerce.price}}"));
		var price = faker.commerce.price();
		var name = faker.commerce.productName();
		console.log(name + " - " + price + " kr");
	}
}

printFakeNameAndPrice();