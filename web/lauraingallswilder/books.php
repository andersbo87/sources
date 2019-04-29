<html>
  <head>
    <title>Little House-bøkene</title>
    <link rel="shortcut icon" href="./images/lauraingallswilder/little_house_icon.ico" />
    <link rel="stylesheet" type="text/css" href="./css/laura_main.css" />
    <script type="text/javascript" src="./js/laura_main.js"></script>
    <script type="text/javascript" src="./js/laura_klokke.js"></script>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
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
      function openLittleHouseWayside()
      {
         var wayside = window.open("./sources_images/little_house_wayside_replica.html","","scrollbars=1, location=1, status=1, height=300, width=300");
      }
      function openSurveyor()
      {
        var surveior = window.open("./sources_images/surveyors_house.html","","scrollbars=1, location=1, status=1, height=300. width=300");
      }
      function openTrainStuck()
      {
         var trainStuck = window.open("./sources_images/train_stuck_in_snow.html","","scrollbars=1, location=1, status=1, height=300, width=300");
      }
      function askUserConfirmation()
      {
         var ans = confirm("Denne sien har et innhold som ennå ikke er oversatt til norsk. Er du sikker på at du vil fortsette?");
         if(ans == true)
         {
            window.location.href="tvseries.php?season=0";
         }
      }
    </script>
  </head>
  <body onload="show3();" oncontextmenu="alert('No copying is allowed'); return false">
    <noscript>
      Enten har du slått av JavaScript, eller så bruker du en
      utdatert nettleser. Vennligst gjør et av følgende:<br />
      1) Slå på JavaScript i nettleserinnstillingene, eller <br />
      2) Last ned nyeste utgave av browserne nedenfor:<br />
      <a href="http://www.apple.com/safari/">Safari (Mac, Windows)</a><br />
      <a href="http://www.opera.com">Opera(FreeBSD, Linux, Mac, Solaris,
          Windows)</a><br />
      <a href="http://www.mozilla.com/en-US/firefox/firefox.html">
          Mozilla FireFox (Linux, Mac, Windows)</a><br />
      <a href="http://www.microsoft.com/windows/internet-explorer/default.aspx">Microsoft Internet Explorer(Windows)</a>
      </noscript>
    <div id="main" style="visibility:hidden">
    <!-- 
       Oppretter en tabell som skal brukes på alle sidene…
      -->
    <table border="0">
      <tr>
	<td colspan="2">
	  <img src="images/laura-banner.jpg" />
	  <br />
	  <script type="text/javascript" src="js/dateScript.js"></script>
	   klokken 
	  <!-- 
	     laster så inn en hel haug med bilder 
	     som skal bli til en digital klokke 
	    -->
	  <img src="./images/c0.gif" name="a"><img src="./images/c0.gif" name="b"><img src="./images/colon.gif" name="c"><img src="./images/c0.gif" name="d"><img src="./images/c0.gif" name="e"><img src="./images/colon.gif" name="f"><img src="./images/c0.gif" name="g"><img src="./images/c0.gif" name="h">
	</td>
      </tr>
      <tr>
	<td valign="top" rowspan="2" id="menu">
	  <!-- gjør det slik at all tekst begynner på toppen-->
	  MENY<br />
	   <form>
		<!--lager en rekke med knapper for at menyen skal bli "jevn"-->
		<input type="button"
		       value="Byene Laura Bodde i"
		       style="width: 200px"
		       onclick="window.location.href='towns.php'" />
		<br />
		<input type="button"
		       value="Familien Ingalls"
		       style="width: 200px"
		       onclick="window.location.href=
				'characters.php'" />
		<br />
		<input type="button"
		       value="Kontakt"
		       style="width: 200px"
		       onclick="window.location.href='contact.php'" />
		<br />
		<input type="button"
		       value="Little House-bøkene"
		       style="width: 200px"
		       onclick="window.location.href='books.php'" />
		<br />
		<input type="button"
		       value="TV-serie"
		       style="width: 200px"
		       onclick="askUserConfirmation();" />
		<br />
	   </form>
	</td>
	 <td valign="top" id="main">
	   <h1>Little House-bøkene</h1>
	 </td>
      </tr>
      <tr>
	 <td valign="top" width="700px" id="main">
	   <!--er finner du informasjon om den virkelige familien Ingalls.<br />
	   Informasjonen er basert på Wikipedia og biografien 
	   "Laura Ingalls Wider: A Biography" av William Anderson.<br />
	   Velg et av navnene fra lisen nedenfor for å lære mer om-
	   og bli "bedre 'kjent'" med denne karakteren/personen. <br />-->
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
	      $sql = new mysqli("localhost", "webuser", "wEb4321User!", "little_house");
	      if($sql->connect_errno)
	      {
		echo "Kunne ikke koble til databasen: (" . $sql->connect_errno . "): " . $sql->connect_error;
	      }
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
	      $result = $sql->query("SELECT * FROM tbl_books WHERE bookTitle='" . $chosen . "'");
	      $row = $result->fetch_assoc();
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
	      //mysql_close($link);
	   ?>
	</td>
      </tr>
    </table>
    </div>
    <script>
      document.getElementById("main").style.visibility = 'visible';
    </script>
  </body>
</html>
