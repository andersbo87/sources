<html>
  <head>
    <title>Byene som Laura og familien har bodd i</title>
    <link rel="shortcut icon" href="./images/lauraingallswilder/little_house_icon.ico" />
    <link rel="stylesheet" type="text/css" href="./css/laura_main.css" />
    <script type="text/javascript" src="./js/laura_main.js"></script>
    <script type="text/javascript" src="./js/laura_klokke.js"></script>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <script type="text/javascript">
      function redirect(page)
      {
        if(page=="0")
        {
          window.location="towns.php";
        }
        if(page=="1")
        {
          window.location="towns.php?town=1";
        }
        if(page=="2")
        {
          window.location="towns.php?town=2";
        }
        if(page=="3")
        {
          window.location="towns.php?town=3";
        }
        if(page=="4")
        {
          window.location="towns.php?town=4";
        }
        if(page=="5")
        {
          window.location="towns.php?town=5";
        }
        if(page=="6")
        {
          window.location="towns.php?town=6";
        }
        if(page=="7")
        {
          window.location="towns.php?town=7";
        }
        if(page=="8")
        {
          window.location="towns.php?town=8";
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
         var museum = window.open("./sources_images/walnut_grove_museum.html","","status=1\, scrollbars=1, location=1, height=300, width=300");
      }
       function openLittleHouseWayside()
      {
         var wayside = window.open("./sources_images/little_house_wayside_replica.html","","scrollbars=1, location=1, status=1, height=300, width=300");
      }
      function openSurveyor()
      {
         var surveyor = window.open("./sources_images/surveyors_house.html","","scrollbars=1, location=1, status=1, height=300, width=300");
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
	    <img src="./images/laura-banner.jpg" oncontextmenu="return true;">
	    <br />
	    <script type="text/javascript" src="./js/dateScript.js"></script>
	    klokken
	    <img src="./images/c0.gif" name="a"><img src="./images/c0.gif" name="b"><img src="./images/colon.gif" name="c"><img src="./images/c0.gif" name="d"><img src="./images/c0.gif" name="e"><img src="./images/colon.gif" name="f"><img src="./images/c0.gif" name="g"><img src="./images/c0.gif" name="h">
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
                     value="TV-serie"
                     style="width: 200px"
                     onclick="askUserConfirmation();" />
              <br />
            </form>
          </td>
	  <td valign="top" id="main">
	    <h1>"Little House"-byene</h1>
	  </td>
	</tr>
	<tr>
	  <td valign="top" width="700px" id="main">
	    Her finner du informasjon om byene Laura og familien
	    hennes bodde i i løpet av <br />
	    "Little House"-årene mot slutten av 1800-tallet, 
	    samt informasjon om byen Laura bodde i da hun
	    skrev de 9 bøkene.
	    Velg en av byene fra listen nedenfor for å
	    lese mer om denne byen.
	    <br />
	    <br />
	    <?php
	      $sql = new mysqli("localhost", "webuser", "wEb4321User!", "little_house");
	      if($sql->connect_errno) {
	         echo "Kan ikke koble til databasen (" . $sql->connect_errno . "): " . $sql->connect_error;
	       }
	       echo "<form action='towns.php' method='get'>\n";
	       echo "<select name='town' onchange=redirect(this.value);>\n";
	       echo "<option selected>Velg en by</option>\n";
	       echo "<option>Burke</option>\n";
	       echo "<option>Burr Oak</option>\n";
	       echo "<option>De Smet</option>\n";
	       echo "<option>Independence</option>\n";
	       echo "<option>Manchester</option>\n";
	       echo "<option>Mansfield</option>\n";
	       echo "<option>Pepin</option>\n";
	       echo "<option>Walnut Grove</option>\n";
	       echo "</select>\n";
	       echo "<input type='submit' value='Send' />\n";
	       echo "</form>\n";
	       $chosen = $_GET["town"];
	       if($chosen == "Velg en by")
	       {
	         echo "Vennligst velg en by fra listen ovenfor.\n";
	       }
	       else
	       {
	       $result=$sql->query("SELECT * FROM tbl_town WHERE townName='" . $chosen . "'");
	       $row = $result->fetch_assoc();
	       echo "<h2>" . $row["townName"] . "</h2>\n";
	       echo "<br /><br />\n";
	       echo $row["townInfo"] . "\n";
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
