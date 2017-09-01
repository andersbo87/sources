<html>
  <head>
    <title>Byene som Laura og familien har bodd i</title>
    <link rel="shortcut icon" href="/lauraingallswilder/images/lauraingallswilder/little_house_icon.ico" />
    <link rel="stylesheet" type="text/css" href="/lauraingallswilder/css/laura_main.css" />
    <script type="text/javascript" src="/lauraingallswilder/js/laura_main.js"></script>
    <script type="text/javascript" src="/lauraingallswilder/js/laura_klokke.js"></script>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <script type="text/javascript">
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
	    <h1>Kontakt webmasteren</h1>
	  </td>
	</tr>
	<tr>
	  <td valign="top" width="700px" id="main">
	     På denne siden kan du ta kontakt med webmasteren.
    Dette gjør du ved å fylle ut skjemaet som står nedenfor.
    Merk at alle felt med * må fylles ut, enten du liker det eller ikke. 
	    <br />
	    <br />
	    <?php
	       if(isset($_REQUEST["navn"])) //&& isset($_REQUEST["epost"]) && isset($_REQUEST["melding"]))
	       {
                 //send the above message as a mail...
                  $to = "andersbo87@icloud.com";
                  $from = $_REQUEST["navn"];
                  $subject = $_REQUEST["emne"];
                  $sender_email = $_REQUEST["epost"];
                  $message = $_REQUEST["melding"];
                  // send the email.
                  mail($to, $subject, $message, "Fra " . $from . " (" . $sender_email . ")");
                  echo "<div id='sentMessage'>\n";
                  echo "\nDin epost skal ha blitt sendt.\n";
                  echo "</div>\n";
	       }
	       else
	       {
	          echo "<form action='contact.php' method='post'>\n";
	          echo "<table border=0 id='main'>\n";
	          echo "<tr>\n";
	          echo "<td>\n";
                  echo "Navn*";
	          echo "</td>";
	          echo "<td valign='top'>\n";
	          echo "<input type='text' name='navn' /><br />\n";
	          echo "</td>";
	          echo "</tr>";
	          echo "<tr>";
	          echo "<td>";
                  echo "E-post*";
	          echo "</td>";
	          echo "<td valign='top'>\n";
	          echo "<input type='text' name='epost' /><br />\n";
	          echo "</td>";
	          echo "</tr>";
	          echo "<tr>";
	          echo "<td>";
                  echo "Emne";
	          echo "</td>";
	          echo "<td valign='top'>";
	          echo "<input type='text' name='emne' /><br />\n";
	          echo "</td>";
	          echo "</tr>";
	          echo "<tr>";
	          echo "<td valign='top'>";
                  echo "Melding*";
	          echo "</td>";
	          echo "<td valign='top'>";
	          echo "<textarea name='melding' rows='10' cols='32'></textarea><br />\n";
	          echo "</td>";
	          echo "</tr>";
	          echo "<tr>";
	          echo "<td>";
                  echo "<input type='Submit' value='Send' />\n";
	          echo "</td>";
	          echo "</tr>";
	          echo "</table>";
                  echo "</form>\n";
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
