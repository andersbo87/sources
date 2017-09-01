<html>
  <head>
    <title>Familien Ingalls</title>
    <?php
       require_once("browsercheck.php");
       if($newstring == "Lynx")
       {
         //naviger til en konsollvennlig side
         header('Location: /lauraingallswilder/console_browsers/characters.php');
       }
       else if($newstring == "ELinks")
       {
         header('Location: /lauraingallswilder/console_browsers/characters.php');
       }
    ?>
    <link rel="shortcut icon" href="images/lauraingallswilder/little_house_icon.ico" />
    <link rel="stylesheet" type="text/css" href="css/laura_main.css" />
    <script type="text/javascript" src="js/laura_main.js"></script>
    <script type="text/javascript" src="js/laura_klokke.js"></script>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <script type="text/javascript">
      function redirect(page)
      {
          if(page == "0")
          {
             window.loacation = "characters.php";
          }
          if(page == "1")
          {
             window.loacation = "characters.php?character=1";
          }
          if(page == "2")
          {
             window.loacation = "characters.php?character=2";
          }
          if(page == "3")
          {
             window.loacation = "characters.php?character=3";
          }
          if(page == "4")
          {
             window.loacation = "characters.php?character=4";
          }
          if(page == "5")
          {
             window.loacation = "characters.php?character=5";
          }
          if(page == "6")
          {
             window.loacation = "characters.php?character=6";
          }
      }
      function askUserConfirmation()
      {
         var ans = confirm("Denne siden inneholder elementer som foreløpig ikke er oversatt til norsk. Er du sikker på at du vil fortsette?");
         if(ans == true)
         {
            window.location.href="tvseries.php?season=0";
         }
      }
      function openCarrie()
      {
        var open = window.open("/lauraingallswilder/sources_images/carrie_1.html","","location=1, status=1, width=200,height=200, scrollbars=1");
      }
      function openGrace()
      {
        var open=window.open("/lauraingallswilder/sources_images/grace_1.html","","location=1,status=1, width=200, height=200, scrollbars=1");
      }
      function openLittleHouseWayside()
      {
         var wayside = window.open("/lauraingallswilder/sources_images/little_house_wayside_replica.html","","scrollbars=1, location=1, status=1, height=300, width=300");
      }
      function openLauraAlmanzo()
      {
         var laura_almanzo = window.open("/lauraingallswilder/sources_images/laura_and_almanzo.html","","location=1, status=1, width=300, height=300, scrollbars=1");
      }
      function openCarrieMaryLaura()
      {
         var carrie_mary_laura = window.open("/lauraingallswilder/sources_images/carrie_mary_laura_1870.html","","location=1,status=1,height=300, width=300, scrollbars=1");
      }
      function openFamilyIngalls()
      {
         var familyIngalls = window.open("/lauraingallswilder/sources_images/familien_ingalls_1894.html","","status=1, location=1, height=300, width=300, scrollbars=1");
      }
      function openOldLaura()
      {
         var grandma_laura = window.open("/lauraingallswilder/sources_images/laura_gammel.html","","status=1, location=1, height=300, width=300, scrollbars=1");
      }
      function openMary()
      {
         var openWin = window.open("/lauraingallswilder/sources_images/mary_1.html","","location=1, status=1, width=200, height=200, scrollbars=1");
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
    <div id="main"><!-- style="visibility:hidden">-->
    <!-- 
       Oppretter en tabell som skal brukes på alle sidene…
      -->
    <table border="0">
      <tr>
	<td colspan="2">
	  <img src="images/laura-banner.jpg" oncontextmenu="return true;" />
	  <br />
	  <script type="text/javascript" src="js/dateScript.js"></script>
	   klokken 
	  <!-- 
	     laster så inn en hel haug med bilder 
	     som skal bli til en digital klokke 
	    -->
	  <img src="images/c0.gif" name="a"><img src="images/c0.gif" name="b"><img src="images/colon.gif" name="c"><img src="images/c0.gif" name="d"><img src="images/c0.gif" name="e"><img src="images/colon.gif" name="f"><img src="images/c0.gif" name="g"><img src="images/c0.gif" name="h">
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
	  <h1>Familien Ingalls</h1>
	</td>
      </tr>
      <tr>
	<td valign="top" width="700px" id="main">
	  <!-- diverse PHP-scripts her -->
	  Her finner du informasjon om den virkelige familien Ingalls.<br />
	  Informasjonen er basert på Wikipedia-artikler og biografien 
	  "Laura Ingalls Wider: A Biography" av William Anderson.<br />
	  Velg ett av navnene fra lisen nedenfor for å lære mer om-
	  og bli "bedre 'kjent'" med denne karakteren/personen. 
	  <br />
	  <br />
	  <?php
	     $sql = new mysqli("localhost", "webuser", "webuser", "little_house");
	     if($sql->connect_errno) {
	        echo "Kunne ikke koble til databasen (" . $sql->connect_errno . "): " . $sql->connect_error;
	     }
	     echo "<form action='characters.php' method='get'>\n";
	     echo "<select name='character' onchange=redirect(this.value);>\n";
	     echo "<option selected>Velg en person</option>\n";
	     echo "<option>Caroline Ingalls</option>\n";
	     echo "<option>Carrie Ingalls</option>\n";
	     echo "<option>Charles Ingalls</option>\n";
	     echo "<option>Grace Ingalls</option>\n";
	     echo "<option>Laura Ingalls</option>\n";
	     echo "<option>Mary Ingalls</option>\n";
	     echo "</select>\n";
	     echo "<input type='submit' value='Send' />\n";
	     echo "</form>\n";
	     $chosen = $_GET["character"];
	     if($chosen == "Velg en person")
	     {
	        echo "Vennligst velg en person fra listen ovenfor.\n";
	     }
	     else
	     {
	  	$result = $sql->query("SELECT * FROM tbl_characters WHERE name='" . $chosen . "'");
	     	$row = $result->fetch_assoc();
	     	echo "<h2>" . $row["name"] . "</h2>\n";
	     	echo "<br /><br />\n";
	     	echo $row["biography"] . "\n";
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
