<html>
  <head>
    <title>Miniserien fra 2005</title>
    <link rel="shortcut icon" href="/lauraingallswilder/images/lauraingallswilder/little_house_icon.ico" />
    <link rel="stylesheet" type="text/css" href="/lauraingallswilder/css/laura_main.css" />
    <script type="text/javascript" src="/lauraingallswilder/js/laura_main.js"></script>
    <script type="text/javascript" src="/lauraingallswilder/js/laura_klokke.js"></script>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <script type="text/javascript">
      function redirect(page)
      {
        if(page == 0)
        {
          window.location = "tvminiseries.php";
        }
        if(page == 1)
        {
          window.location = "tvminiseries.php?episode=1";
        }
        if(page == 2)
        {
          window.location = "tvminiseries.php?episode=2";
        }
        if(page == 3)
        {
          window.location = "tvminiseries.php?episode=3";
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
      function openMuseum()
      {
         var museum = window.open("/lauraingallswilder/sources_images/walnut_grove_museum.html","","status=1\, scrollbars=1, location=1, height=300, width=300");
      }
       function openLittleHouseWayside()
      {
         var wayside = window.open("/lauraingallswilder/sources_images/little_house_wayside_replica.html","","scrollbars=1, location=1, status=1, height=300, width=300");
      }
      function openSurveyor()
      {
         var surveyor = window.open("/lauraingallswilder/sources_images/surveyors_house.html","","scrollbars=1, location=1, status=1, height=300, width=300");
      }
    </script>
  </head>
  <body onload="show3();" oncontextmenu="alert('Kopiering er ikke tillatt.'); return false">
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
    <!--<div id="main" style="visibility:hidden">-->
    <div id="main" style="visibility:hidden">
      <table border="0">
	<tr>
	  <td colspan="2">
	    <img src="/lauraingallswilder/images/laura-banner.jpg" oncontextmenu="return true;">
	    <br />
	    <script type="text/javascript" src="/lauraingallswilder/js/dateScript.js"></script>
	    klokken
	    <img src="/lauraingallswilder/images/c0.gif" name="a"><img src="/lauraingallswilder/images/c0.gif" name="b"><img src="/lauraingallswilder/images/colon.gif" name="c"><img src="/lauraingallswilder/images/c0.gif" name="d"><img src="/lauraingallswilder/images/c0.gif" name="e"><img src="/lauraingallswilder/images/colon.gif" name="f"><img src="/lauraingallswilder/images/c0.gif" name="g"><img src="/lauraingallswilder/images/c0.gif" name="h">
	  </td>
	</tr>
	<tr>
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
                     onclick="window.location.href='characters.php'" />
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
	  <td valign="top" id="main">
	    <h1>TV miniserie</h1>
	  </td>
	</tr>
	<tr>
	  <td valign="top" width="700px" id="main">
	     På denne siden vil du finne informasjon om en miniserie som ble
	     produsert av amerikanske ABC og sendt i 2005.
	     Serien består av i alt 3 episoder som hver er delt opp i 2 deler.
	    <br />
	    <br />
	    <?php
	      $sql = new mysqli("localhost", "webuser", "wEb4321User!", "little_house");
	      if($sql->connect_errno) {
	        echo "Kunne ikke koble til databasen (" . $sql->connect_errno . "): " . $sql->connect_error;
	      }
	      echo "<form action='tvminiseries.php' method='get'>\n";
	      echo "Episode: \n";
	      echo "<select name='episode' onchange=redirect(this.value);>\n";
	      echo "<option selected='chosen'>Velg en episode</option>\n";
	      echo "<option>Little House in the Big Woods</option>\n";
	      echo "<option>The Ingalls' Journey</option>\n";
	      echo "<option>Adventures on the Kansas Prairie</option>\n";
	      echo "</select>\n";
	      echo "<input type='submit' value='Send'>\n";
	      echo "</form>\n";
	      $chosen = $_GET["episode"];
	      if($chosen == "Velg en episode")
	      {
                echo "Vennligst velg en episode fra listen ovenfor";
	      }
	      else
	      {
	        $result = $sql->query("SELECT * FROM tbl_miniseries WHERE name='" . $chosen . "'");
	        $row = $result->fetch_assoc();
	        echo "<h2>" . $row["name"] . "</h2>\n";
                echo "<br /><br />Beskrivelse:<br /><br />\n";
	        echo $row["description"] . "\n";
              }
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
