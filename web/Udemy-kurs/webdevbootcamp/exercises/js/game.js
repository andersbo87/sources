while(true)
{
	var corrAns = 6;
	var userAns = prompt("Skriv inn et tall som er større enn 0.");
	var num = parseInt(userAns);
	if(num < 0)
		console.log("Du må skrive inn et tall >= 0.");
	if(num === corrAns){
		alert("Gratulerer! Du gjettet riktig!");
		break;
	}
	else if(num < corrAns)
		alert("Beklager, " + num + " er for lavt.");
	else
		alert("Beklager, " + num + " er for høyt.");
}


//Kan også skrives slik:
/*var corrAns = 6;
var userAns = 0;
while(userAns != corrAns)
{
	var userAns = prompt("Skriv inn et tall som er større enn 0.");
	var num = parseInt(userAns);
	if(num < 0)
		console.log("Du må skrive inn et tall >= 0.");
	if(num === corrAns){
		alert("Gratulerer! Du gjettet riktig!");
		//break;
	}
	else if(num < corrAns)
		alert("Beklager, " + num + " er for lavt.");
	else
		alert("Beklager, " + num + " er for høyt.");
}
*/