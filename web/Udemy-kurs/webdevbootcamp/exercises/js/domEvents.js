var btn = document.querySelector("button");
btn.addEventListener("click", btnClicked);
var isPurple = false;
function btnClicked(){
	/*var body = document.getElementsByTagName("body")[0];
	if(!isPurple){
		body.style.background = "purple";
	}
	else {
		body.style.background = "white";
	}
	isPurple = !isPurple;*/

	document.body.classList.toggle("purple");
}