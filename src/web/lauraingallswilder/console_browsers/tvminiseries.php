<html>
  <head>
    <title>TV-miniserie</title>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <script type="text/javascript" src="../js/laura_main.js"></script>
  </head>
  <body>
    MENY<br />
    <a href="characters.php">Familien Ingalls</a><br />
    <a href="towns.php">Byene Laura bodde i</a><br />
    <a href="books.php">Little House-bøkene</a><br />
    <a href="contact.php">Kontakt</a><br />
    <a href="tvseries.php">TV-serie</a><br />
    <a href="tvminiseries.php">TV-miniserie</a><br />
    <br />
    <h1>TV-miniserie</h1>
    <br />
    <br />
    På denne siden vil du finne informasjon om en miniserie som ble
    produsert av amerikanske ABC og sendt i 2005.
    Serien består av i alt 3 episoder som hver er delt opp i 2 deler.
    <?php
       $link = mysql_connect("localhost", "webuser", "webuser");
       if(!$link)
       {
          die("Could not connect: " . mysql_error());
       }
       $dbname = "little_house";
       echo "<form action='tvminiseries.php' method='get'>\n";
       echo "Episode ID: \n";
       echo "<select name='miniseries' onchange=redirect(this.value);>\n";
       echo "<option selected='chosen'>Velg en episode</option>\n";
       echo "<option>Little House in the Big Woods</option>\n";
       echo "<option>The Ingalls' Journey</option>\n";
       echo "<oprion>Adventures on the Kansas Prairie</option>\n";
       echo "</select>\n";
       echo "<input type='submit' value='Send'>\n";
       echo "</form>\n";
       $chosen = $_GET["miniseries"];
       if($chosen == "Velg en episode")
       {
          echo "Vennligst velg en episode fra listen ovenfor";
       }
       else
       {
          $result = mysql_query("SELECT * FROM tbl_tvseries WHERE episodeName=\"" . $chosen . "\"") or die(mysql_error());
          $row = mysql_fetch_array($result);
          echo "<h2>" . $row["episodeName"] . "</h2>\n";
          echo "<br /><br />\n";
          echo $row["episodeInfo"] . "\n";
       }
       mysql_close($link);
    ?>
  </body>
</html>
