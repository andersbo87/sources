var colours = [];
var header = document.querySelector("h1");
var squares = document.querySelectorAll(".square");
var pickedColour = pickColour();
var colourDisplay = document.querySelector("#colourDisplay");
colourDisplay.textContent = pickedColour;
const backgroundColour = "#232323";
var messageDisplay = document.getElementById("message");
var btnNewGame = document.getElementById("newColors");
var modeButtons = document.querySelectorAll(".mode");
var easyMode = "Vanskelig";
init();

function init(){
	setupButtons();
	setupSquares();
	easyMode === "Lett" ? newGame(3) : newGame(6);
}

function setupSquares(){
	for(var i = 0; i < squares.length; i++){
		// La oss begynne med å legge til farger i kvadratene.
		squares[i].style.backgroundColor = colours[i];

		// Deretter legger til til en "click event" på hvert kvadrat.
		squares[i].addEventListener("click", function()
		{
			/* 
			Få tak i fargen som tilhørte kvadratet brukeren
			klikket på. Deretter sammenligner vi denne koden
			med koden til den utvalgte fargen.
			*/
			var clickedColour = this.style.backgroundColor;
			console.log(clickedColour, pickedColour);
			if(clickedColour === pickedColour){
				messageDisplay.textContent = "Riktig!";
				changeColour(clickedColour);
				header.style.backgroundColor = clickedColour;
				btnNewGame.textContent = "Spille igjen?";
			}
			else
			{
				this.style.backgroundColor = backgroundColour;
				messageDisplay.textContent = "Prøv igjen";
			}
		});
	}
}

function setupButtons(){
	btnNewGame.addEventListener("click", function(){
		easyMode === "Lett" ? newGame(3) : newGame(6);
	});
	for(var i = 0; i < modeButtons.length; i++){
		modeButtons[i].addEventListener("click", function(){
			modeButtons[0].classList.remove("selected");
			modeButtons[1].classList.remove("selected");
			this.classList.add("selected");
			easyMode = this.textContent;
			easyMode === "Lett" ? newGame(3) : newGame(6);
		});
	}
}

function newGame(nums)
{
	// Generer alle nye farger
	colours = generateRandomColours(nums);
	// Velg en ny tilfeldig farge fra tabellen
	pickedColour = pickColour();
	// Bytt colourDisplay, slik at rett fargekode vises.
	colourDisplay.textContent = pickedColour;
	// Gi kvadratene en ny farge
	for(var i = 0; i < squares.length; i++){
		if(colours[i]){
			squares[i].style.display = "block";
			squares[i].style.backgroundColor = colours[i];
		}
		else
			squares[i].style.display = "none";
	}
	messageDisplay.textContent = "";
	header.style.backgroundColor = "steelblue";
}

function changeColour(colour)
{
	// Gå gjennom alle kvadratene.
	for(var i = 0; i < squares.length; i++)
		// Bytte alle farger til riktig farge
		squares[i].style.backgroundColor = colour;
}

function pickColour()
{
	var rand = Math.floor(Math.random() * colours.length);
	return colours[rand];
}

function generateRandomColours(num)
{
	// Opprett en tabell
	var arr = [];
	// Legg til angitt (num) antall farger i tabelen
	var i = 0;
	while(i < num){
		// Hent en tilfeldig farge og legg til denne i tabellen.
		arr.push(randomColour());
		i++;
	}
	// Returner tabellen
	return arr;
}

function randomColour()
{
	// Plukk ut en "rød" verdi mellom 0 og 255
	var red = Math.floor(Math.random() * 256);
	// Plukk ut en "grønn" verdi mellom 0 og 255
	var green = Math.floor(Math.random() * 256);
	// Plukk ut en "blå" verdi mellom 0 og 255
	var blue = Math.floor(Math.random() * 256);
	return "rgb(" + red + ", " + green + ", " + blue + ")";
}