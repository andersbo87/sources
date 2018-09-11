var body = document.querySelector("body");
var isBlue = false;

function chooseBackgroundColor()
{
	if(isBlue)
		body.style.background = "white";
	else
		body.style.background = "#3498db";

	isBlue = !isBlue;
}

setInterval(chooseBackgroundColor, 1000);