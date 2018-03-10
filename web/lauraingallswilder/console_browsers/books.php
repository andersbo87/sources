<html>
  <head>
    <title>Little House-bøkene</title>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <script type="text/javascript" src="../js/laura_main.js"></script>
    <script type="text/javascript" src="../js/laura_main.js"></script>
    <script type="text/javascript">
      function redirect(page)
      {
        if(page == "0")
         {
            window.location = "books.php";
         }
         if(page == "1")
         {
            window.location = "books.php?book=1";
         }
         if(page == "2")
         {
            window.location = "books.php?book=2";
         }
         if(page == "3")
         {
            window.location = "books.php?book=3";
         }
         if(page == "4")
         {
            window.location = "books.php?book=4";
         }
         if(page == "5")
         {
            window.location = "books.php?book=5";
         }
         if(page == "6")
         {
            window.location = "books.php?book=6";
         }
         if(page == "7")
         {
            window.location = "books.php?book=7";
         }
         if(page == "8")
         {
            window.location = "books.php?book=8";
         }
         if(page == "9")
         {
            window.location = "books.php?book=9";
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
	<a href="tvminiseries.php">TV-miniserie</a><br />
	<br/>
	<h1>Little House-bøkene</h1>
	<br />
	<br />
	Her finner du informasjon om de 9 bøkene som inngår i den
	originale "Little House"-serien. I tillegg til en beskrivelse av
	handlinga i bøkene finner du en liste over karakterer/personer
	som er med i de ulike bøkene, når de kom ut, 
	eventuelle norske titler (ikke alle bøkene er oversatt til norsk),
	og merknader som bl. a. forteller om forskjeller
	mellom bøkene og virkeligheten (basert på historiske bevis).
	Er det noen navn du også kjenner fra TV-serien?
	<br /> 
	<br />
	Du finner informasjon om de ulike bøkene ved å velge en
	tittel fra listen under og klikke "Send."
	<br />
	<?php 
	   $link = mysql_connect("localhost", "webuser", "wEb4321User!");
	   if(!$link)
	   {
	      die("Could not connect: " . mysql_error());
	   }
	   $dbname = "little_house";
	   mysql_select_db($dbname);
	   echo "<form action='books.php' method='get'>\n";
	   echo "<select name='book' onchange=redirect(this.value);>\n";
	   echo "<option selected='selected'>Velg en boktittel</option>\n";
	   echo "<option>Little House in the Big Woods</option>\n";
	   echo "<option>Farmer Boy</option>\n";
	   echo "<option>Little House on the Prairie</option>\n";
	   echo "<option>On the Banks of Plum Creek</option>\n";
	   echo "<option>By the Shores of Silver Lake</option>\n";
	   echo "<option>The Long Winter</option>\n";
	   echo "<option>Little Town on the Prairie</option>\n";
	   echo "<option>These Happy Golden Years</option>\n";
	   echo "<option>The First Four Years</option>\n";
	   echo "</select>\n";
	   echo "<input type='submit' value='Send' />\n";
	   echo "</form>\n";
	   $chosen = $_GET["book"];
	   if($chosen == "Velg en boktittel")
	   {
	       echo "Vennligst velg en bok fra listen ovenfor\n";
	   }
	   else
	   {
	      $result = mysql_query("SELECT * FROM tbl_books WHERE bookTitle='" . $chosen . "'") or die(mysql_error());
	      $row = mysql_fetch_array($result);
	      echo "<table border='0' id='bookData'>\n";
	      echo "<tr>\n";
	      echo "<td valign='center' colspan='2'>\n";
	      echo "Fakta om bok " . $row["bookID"] . " av 9\n";
	      echo "</td>\n";
	      echo "</tr>\n";
	      echo "<tr>\n";
	      echo "<td valign='top' width='200px'>\n";
	      echo "Originaltittel\n";
	      echo "</td>\n";
	      echo "<td valign='top'>\n";
	      echo "'" . $row["bookTitle"] . "'\n";
	      echo "</td>\n";
	      echo "</tr>\n";
	      echo "<tr>\n";
	      echo "<td valign='top'>\n";
	      echo "Norsk tittel\n";
	      echo "</td>\n";
	      echo "<td valign='top'>\n";
	      echo "'" . $row["norwegianTitle"] . "'\n";
	      echo "</td>\n";
	      echo "</tr>\n";
	      echo "<tr>\n";
	      echo "<td valign='top'>\n";
	      echo "Publisert første gang\n";
	      echo "</td>\n";
	      echo "<td valign='top'>\n";
	      echo $row["initialRelease"] . "\n";
	      echo "</td>\n";
	      echo "</tr>\n";
	      echo "<tr>\n";
	      echo "<td valign='top'>\n";
	      echo "Nyeste utgave\n";
	      echo "</td>\n";
	      echo "<td valign='top'>\n";
	      echo $row["newestRelease"] . "\n";
	      echo "</td>\n";
	      echo "</tr>\n";
	      echo "<tr>\n";
	      echo "<td valign='top'>\n";
	      echo "Hovedkarakterer (alfabetisk)\n";
	      echo "</td>\n";
	      echo "<td valign='top'>\n";
	      echo $row["mainCharacters"] . "\n";
	      echo "</td>\n";
	      echo "</tr>\n";
	      echo "<tr>\n";
	      echo "<td valign='top'>\n";
	      echo "'Gjestekarakterer' (i 'tilfeldig' rekkefølge)\n";
	      echo "</td>\n";
	      echo "<td valign='top'>\n";
	      echo $row["guestCharacters"] . "\n";
	      echo "</td>\n";
	      echo "</tr>\n";
	      echo "<tr>\n";
	      echo "<td valign='top'>\n";
	      echo "Andre karakterer (i 'tilfeldig' rekkefølge)\n";
	      echo "</td>\n";
	      echo "<td valign='top'>\n";
	      echo $row["otherCharacters"] . "\n";
	      echo "</td>\n";
	      echo "</tr>\n";
	      echo "<tr>\n";
	      echo "<td valign='top'>\n";
	      echo "Antall sider\n";
	      echo "</td>\n";
	      echo "<td valign='top'>\n";
	      echo $row["pages"] . "\n";
	      echo "</td>\n";
	      echo "</tr>\n";
	      echo "</table>\n";
	      echo "<h2>Beskrivelse</h2>\n";
	      echo "<br /><br />\n";
	      echo $row["description"] . "\n";
	   }
	   mysql_close($link);
	?>
  </body>
</html>
