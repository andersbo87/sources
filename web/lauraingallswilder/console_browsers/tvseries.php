<html>
  <head>
    <title>TV-serie</title>
    <script type="text/javascript" src="../js/laura_main.js"></script>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <script type="text/javascript">
      function redirect(page)
      {
         if(page == "0")
         {
            window.location = "tvseries.php?season=0";
         }
         if(page == "1")
         {
            window.location = "tvseries.php?season=1";
         }
         if(page == "2")
         {
            window.location = "tvseries.php?season=2";
         }
         if(page == "3")
         {
            window.location = "tvseries.php?season=3";
         }
         if(page == "4")
         {
            window.location = "tvseries.php?season=4";
         }
         if(page == "5")
         {
            window.location = "tvseries.php?season=5";
         }
         if(page == "6")
         {
            window.location = "tvseries.php?season=6";
         }
         if(page == "7")
         {
            window.location = "tvseries.php?season=7";
         }
         if(page == "8")
         {
            window.location = "tvseries.php?season=8";
         }
         if(page == "9")
         {
            window.location = "tvseries.php?season=9";
         }
         if(page == "10")
         {
            window.location = "tvseries.php?season=10";
         }
      }
    </script>
  </head>
  <body>
    MENY<br />
    <a href="characters.php">Familien Ingalls</a><br />
    <a href="towns.php">Byene Laura bodde i</a><br />
    <a href="books.php">Little House-bøkene</a><br />
    <a href="contact.php">Kontakt</a><br />
    <a href="tvseries.php">TV-serie</a><br />
    <br />
    <h1>TV-serie</h1>
    <br />
    <br />
    Denne siden inneholder informasjon om samtlige episoder<br />
    i Little House-tv-serien fra 1970- og 1980-tallet.<br />
    For å finne informasjonen om en gitt episode,<br />
    velg først sesong fra listen til høyre for "Sesong" og klikk "Send sesong".<br /> 
    Når dette er gjort, åpner du opp listen til høyre for teksten "Episode" og klikk "Send episode".<br />
    Velg hvilken episode du vil slå opp, og trykk på send
    en gang til.
    <?php
	$sql = new mysqli("localhost", "webuser", "wEb4321User!", "little_house");
	if($sql->connect_errno)
	{
	   echo "Kunne ikke koble til databasen: (" . $sql->connect_errno . "): " . $sql->connect_error;
        }
       echo "<form action='tvseries.php' method='get'>\n";
       echo "Season: ";
       echo "<select name='season' onchange=redirect(this.value);>\n";
       echo "<option selected='chosen'> " . $_GET["season"] . "</options>\n";
       echo "<option>0</option>\n";
       echo "<option>1</option>\n";
       echo "<option>2</option>\n";
       echo "<option>3</option>\n";
       echo "<option>4</option>\n";
       echo "<option>5</option>\n";
       echo "<option>6</option>\n";
       echo "<option>7</option>\n";
       echo "<option>8</option>\n";
       echo "<option>9</option>\n";
       echo "<option>10</option>\n";
       echo "</select>\n";
echo "<input type='submit' value='Send sesong' />\n";
       echo "<br />\n";
       echo "Episode: ";
       echo "<select name='episode'>\n";
       echo "<option selected='selected'> " . $_GET["episode"] . "</option>\n";
       $result1 = $sql->query("SELECT episodeName FROM tbl_episodes WHERE seasonID = " . $_GET["season"] . " ORDER BY episodeID ASC");
               while($row = $result1->fetch_assoc())
	       {
	         $return[] = $row;
	         echo "<option>" . $row["episodeName"] . "</option>\n";
	       }
       echo "</select>\n";
       echo "<input type='submit' value='Send episode' />\n";
       echo "</form>\n";
       $chosen = $_GET["episode"];
       if($chosen == "Choose an episode title")
       {
          echo "Please choose an episode from the above list";
       }
       
       $result = $sql->query("SELECT * FROM qry_episodes WHERE episodeName=\"" . $chosen . "\"") or die(mysql_error());
       $row = $result->fetch_assoc();
       echo "<table border='0' id='filmData'>\n";
       echo "<tr>\n";
       echo "<td valign='top' width='200px'>\n";
       echo "Episode ID\n";
       echo "</td>\n";
       echo "<td valign='top' width='400px'>\n";
       echo $row["episodeID"] . "\n";
       echo "</td>\n";
       echo "</tr>\n";
       echo "<tr>\n";
       echo "<td valign='top' width='200px'>\n";
       echo "Episode Title\n";
       echo "</td>\n";
       echo "<td valign='top' width='400px'\n>";
       echo $row["episodeName"] . "\n";
       echo "</td>\n";
       echo "</tr>\n";
       echo "<tr>\n";
       echo "<td valign='top' width='200px'>\n";
       echo "Episode Description\n";
       echo "</td>\n";
       echo "<td valign='top' width='400px'>\n";
       echo $row["episodeDescription"] . "\n";
       echo "</td>\n";
       echo "</tr>\n";
       echo "<tr>\n";
       echo "<td valign='top' width='200px'>\n";
       echo "Season\n";
       echo "</td>\n";
       echo "<td valign='top' width='400px'>\n";
       echo $row["season"] . "\n";
       echo "</td>\n";
       echo "</tr>\n";
       echo "<tr>\n";
       echo "<td valign='top' width='200px'>\n";
       echo "Notes\n";
       echo "</td>\n";
       echo "<td valign='top' width='400px'>\n";
       echo $row["notes"] . "\n";
       echo "</td>\n";
       echo "</tr>\n";
       echo "</table>\n";
    ?>
  </body>
</html>
