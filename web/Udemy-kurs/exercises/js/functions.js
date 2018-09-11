// Denne koden er ikke brukt i noen HTML-filer,
// men kan brukes ved å åpne nettleserens konsoll og lime
// inn ønskede funksjoner. 
function isEven(number)
{
	/*if(number % 2 === 0)
		return true;
	return false;*/
	// Kursleders forslag:
	return number % 2 === 0;
}

function factorial(number)
{
	if(number === 0)
		return 1;
	
	var res=1;
	while(number >= 1)
	{
		res*=number;
		number--;
	}
	return res;
}

function kebabToSnake(string)
{
	return string.replace(/-/g, "_");
}

