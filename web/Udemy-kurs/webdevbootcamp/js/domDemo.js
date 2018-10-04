var h1 = document.querySelector("h1");
var lis = document.querySelectorAll("li");
/*
Merk at man kan ha mer enn én "event listener" per 
HTML-tagg.
*/
h1.addEventListener("click",headerClicked);
//document.querySelector("ul").addEventListener("click", ulClicked);

function headerClicked()
{
	alert("User clicked on the title!");
	h1.style.background = "orange";
}

/*
function ulClicked(){
	console.log("Du klikket inne i UL-taggen!");
	alert("Du klikket inne i UL-taggen!");	
}
*/

function liClicked()
{
	console.log("Du klikket LI");
	this.style.color = "red";
}

for(var i = 0; i<lis.length; i++){
	lis[i].addEventListener("click", liClicked);
}