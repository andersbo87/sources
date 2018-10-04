var ans = prompt("Skriv inn alderen din i antall år");
var age;

if(!isNaN(ans))
{
	age = parseInt(ans);
}
else
{
	alert(ans + " må være et gyldig tall.");
}

if(age < 0)
{
	alert(age + " må være større enn eller lik 0.");
}
else if(age === 21)
{
	alert("Gratulerer med " + age + "-årsdagen din!");
}
else if(age % 2 != 0)
{
	alert("Alderen din er et oddetall!");
}
else if(age % Math.sqrt(age) === 0)
{
	alert("Alderen din er et primtall!");
}

/*
function isSquare(n)
{
	var i = 1;
	for(;;){
		if(n < 0)
			return false;
		else if(n === 0)
			return true;
		n-=i;
		i+=2;
	}
}
*/