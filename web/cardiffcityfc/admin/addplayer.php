<html>
  <head>
    <title>Legg til spiller</title>
  </head>
  <body>
    <h1>Ny spiller</h1>
    Her kan administrator legge til en ny spiller i databasen. Dette forutsetter selvsagt at han har et passord som kan benyttes.
    Dette er foreløpig bare en testside for å teste ut ulike funksjoner.
    Passordet er:
    <?php
       $myfile = fopen("/usr/home/andersbo/passwd.txt", "r") or die("Unable to open file!");
       //echo "Passord: " . fread($myfile,filesize("/usr/home/andersbo/passwd,txt"));
       $correctPass = fgets($myfile);
       $correctPass = trim($correctPass);
       echo $correctPass . "."; // Of course the correct password shouldn't be echoed, but for now, this is a test site...
       fclose($myfile)
     ?>
    <!--
	Poenget med denne siden, er å registrere nye spillere i databasen. Dette foregår ved at webmaster fyller ut skjemaet nedenfor, som da skal inneholde de dataene som skal legges inn i databasen.
	Systemet vil be brukeren om å angi et passord og sjekker dette opp mot det innleste passordet i funksjonen ovenfor. Dette er for å se til at det ikke er noen som er ute etter å ødelegge.
	Dersom feil passord angis, vil webmasteren bli varslet over e-post.
      -->
    <form action="addplayer.php" method="post">
      Skriv inn korrekt passord: <input type="password" name="passord">
      <br />
      <input type="submit" value="Send">
    </form>
    <?php
       function updateDB()
       {
          echo "Nå skal databasen oppdateres!\n";
          
       }
       echo "Innskrevet passord: " . $_POST["passord"] . "<br />";
       echo "Korrekt passord: " . $correctPass;
       echo $n = strcmp($_POST["passord"], $correctPass);
       if(strcmp($_POST["passord"], $correctPass) == 0)
       {
          echo "Passordene stemmer!<br />";
          //<!-- Det er her som databasen skal oppdateres. -->
	  updateDB();
       }
       else
       {
         echo "Du skrev inn feil passord.<br />";
       }
    ?>
  </body>
</html>
