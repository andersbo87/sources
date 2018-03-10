<html>
  <head>
    <title>"Little House on the Prairie" TV-serie</title>
    <link rel="stylesheet" type="text/css" href="css/laura_main.css" />
    <link rel="shortcut icon" href="images/lauraingallswilder/little_house_icon.ico" />
    <script type="text/javascript" src="js/laura_main.js"></script>
    <script type="text/javascript" src="js/klokke.js"></script>
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
      function askUserConfirmation()
      {
        var ans = confirm("Denne siden inneholder elementer som foreløpig ikke er oversatt\
 til norsk. Er du sikker på at du vil fortsette?");
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
	    <script type="text/javascript">
	      var currentTime = new Date();
	      var day = currentTime.getDate();
	      var month = currentTime.getMonth() + 1;
	      var year = currentTime.getFullYear();
	      document.write(day + "." + month + "." + year);
	    </script>
	    klokken 
	    <img src="images/c0.gif" name="a"><img src="images/c0.gif" name="b"><img src="images/colon.gif" name="c"><img src="images/c0.gif" name="d"><img src="images/c0.gif" name="e"><img src="images/colon.gif" name="f"><img src="images/c0.gif" name="g"><img src="images/c0.gif" name="h">
	  </td>
	</tr>
	<tr>
	  <!--Gjør det slik at all tekst begynner på toppen-->
	  <td valign="top" rowspan="2" id="menu">
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
                       onclick ="window.location.href='contact.php'"/>
                <br />
                <input type="button"
                       value="Little House-bøkene"
                       style="width: 200px"
                       onclick="window.location.href='books.php'" />
                <br />
                <input type="button"
                       value="TV-miniserie"
                       style="width: 200px"
                       onclick="window.location.href='tvminiseries.php'" />
                <br />
                <input type="button"
                       value="TV-serie"
                       style="width: 200px"
                       onclick="askUserConfirmation();" />
                <br />
	    </form>
	  </td>
	  <td valign="top" id="main" height="10px">
	    <h1>"Little House on the Prairie" - TV-serie</h1>
	  </td>
	</tr>
	</tr>
	  <td valign="top" id="main" width="700px">
	    Denne siden inneholder informasjon om samtlige episoder<br />
	    i Little House-tv-serien fra 1970- og 1980-tallet.<br />
	    For å finne informasjonen om en gitt episode,<br />
	    velg først sesong fra listen til høyre for "Sesong".<br /> 
	    Når dette er gjort, åpner
	    du opp listen til høyre for teksten "Episode".<br />
	    Velg hvilken episode du vil slå opp, og trykk på send
	    en gang til.
	    <?php
	      $sql = new mysqli("localhost", "webuser", "wEb4321User!", "little_house");
	      if($sql->connect_errno) {
	         echo "Kunne ikke koble til databasen (" . $sql->connect_errno . "):" . $sql->connect_error; 
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
	       echo "<input type='submit' value='Send' />\n";
	       echo "</form>\n";
	       $chosen = $_GET["episode"];
	       if($chosen == "Choose an episode title")
	       {
	          echo "Please choose an episode from the above list";
	       }
	       
	       $result2 = $sql->query("SELECT * FROM qry_episodes WHERE episodeName=\"" . $chosen . "\"");
	       $row = $result2->fetch_assoc();
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
	  </td>
	</tr>
	<tr>
	  <td valign="top" colspan="2" id="footer">
	    Copyright © 2010 Anders. Alle rettigheter forbeholdt. 
	  </td>
	</tr>
      </table>
    </div>
    <script>
      document.getElementById("main").style.visibility = 'visible';
    </script>
  </body>
</html>
