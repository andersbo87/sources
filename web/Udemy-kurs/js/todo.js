var todoList = [];
var ans = prompt("Hva vil du gjøre?").toLowerCase();
window.setTimeout(function()
{
	while(ans !== "avslutt")
	{
		// Skriv koden som skal kjøres her…
		
		if(ans === "ny"){
			add();
		}
		else if(ans === "list")
		{
			list();
		}
		else if(ans === "slett")
		{
			remove();
		}
		ans = prompt("Hva vil du gjøre?").toLowerCase();
	}
}, 500);

function add() {
	console.log("Legg til nytt element");
	var obj = prompt("Skriv inn en ny ting som skal gjøres.");
	todoList.push(obj);
	console.log("Element lagt til.");
}

function list() {
	todoList.forEach(function(ls, i)
	{
		console.log(i + ": " + ls);
	});
}

function remove()
{
	var rmObj = prompt("Skriv inn hvilken indeks som skal fjernes.");
	todoList.splice(rmObj, 1);
	console.log("Element fjernet.");
}

function quit()
{
	console.log("OK, du har avsluttet programmet.");
}