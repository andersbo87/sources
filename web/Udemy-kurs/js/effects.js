var fadedOut = false;
$("button").click(function(){
	// Koden under kan erstattes med fadeToggle.
	if(fadedOut === false){
		$("div").fadeOut(2000, function(){
			console.log("Faded out");
    	});
    	fadedOut = true;
	}
	else
	{
		$("div").fadeIn(2000, function(){
			console.log("Faded in");
    	});
    	fadedOut = false;
	}
});