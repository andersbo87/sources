// La oss begynne med å velge ut elementer fra HTML-siden:
var btnPlayer1 = document.getElementById("player1");
var btnPlayer2 = document.getElementById("player2");
var btnReset = document.querySelector("#reset");
var pOne = document.querySelector("#playerOne");
var pTwo = document.querySelector("#playerTwo");
var maxDisplay = document.querySelector("p span");
var maxScoreInput = document.querySelector("#maxScoreChanger");

var playerOneScore = 0, playerTwoScore = 0;
var maxScore = 7;
var reachedMaxScore = false;

btnPlayer1.addEventListener("click", function(){
	if(!reachedMaxScore)
		playerOneScore++;
	else
		return;

	if(playerOneScore >= maxScore){
		reachedMaxScore = true;
		pOne.classList.add("winner");
	}
	pOne.textContent = playerOneScore;
	console.log(playerOneScore);
});

btnPlayer2.addEventListener("click", function(){
	if(!reachedMaxScore)
		playerTwoScore++;
	else
		return;

	if(playerTwoScore >= maxScore){
		reachedMaxScore = true;
		pTwo.classList.add("winner");
	}
	pTwo.textContent = playerTwoScore;
	console.log(playerTwoScore);
});

btnReset.addEventListener("click", function(){
	reset();
});

maxScoreInput.addEventListener("change", function(){
	var val = document.querySelector("input");
	maxDisplay.textContent = val.value;
	maxScore = Number(val.value);
	reset();
});

function reset(){
	playerOneScore = 0;
	playerTwoScore = 0;
	reachedMaxScore = false;
	pOne.textContent = playerOneScore;
	pOne.classList.remove("winner");
	pTwo.classList.remove("winner");
	pTwo.textContent = playerTwoScore;
}