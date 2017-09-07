<html>
   <head>
     <title>Ingen tilgang</title>
    
   </head>
   <body>
      <h1>Ingen tilgang</h1>
      <br />
      Du har ikke tilgang til denne siden her, er jeg redd. Klikk <a href="javascript:history.back(1);">her</a> for å gå tilbake til siden du kom fra.
      <br />
      <br />
      <script type="text/javascript">
	kjorEksempel("Bruker");
	function kjorEksempel(navn)
	{
	  var korrektNavn = false;
	  if(navn == "Bruker"){
	    korrektNavn = true;
	    document.write("Du skrev korrekt brukernavn.");
	  }
	  else{
	    korrektNavn = false;
	    document.write("Du skrev feil brukernavn.");
	  }
	}
      </script>
   </body>
</html>
