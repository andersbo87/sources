<html>
  <head>
    <title>Informasjon om Cardiffs spillere</title>
    <link rel="stylesheet" type="text/css" href="css/main.css" />
    <script type="text/javascript" src="js/main.js"></script>
    <script type="text/javascript" src="js/klokke.js"></script>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
  </head>
  <body onload="show3();">
    <table border="1">
	<tr>
	  <td valign="top" colspan="2">
	    <img src="images/c0.gif" name="a"><img src="images/c0.gif" name="b"><img src="images/colon.gif" name="c"><img src="images/c0.gif" name="d"><img src="images/c0.gif" name="e"><img src="images/colon.gif" name="f"><img src="images/c0.gif" name="g"><img src="images/c0.gif" name="h">
	  </td>
	</tr>
	<tr>
	  <td valign="top">
	    <form>
	    MENY<br />
	    <input type="button" value="Arena" style="width:80px" onclick="window.location.href='arena.php'" /><br />
	    <input type="button" value="Divisjon" style="width:80px" onclick="window.location.href='divisjon.php'" /><br />
	    <input type="button" value="Lag" style="width:80px" onclick="window.location.href='lag.php'" /><br />
	    <input type="button" value="Spillere" style="width:80px" onclick="window.location.href='spiller.php'" /><br />
	    </form>
	  </td>
	  <td valign="top">
	    Dette skal etterhvert bli en databaseside om Cardiff City FC.
	    På denne siden vil du, når jeg får tid og lyst til å legge inn info på databasen, få informasjon om de ulike spillerne.
	    <?php
	       $link = pg_connect("user=andersbo dbname=cardiffcityfc") or die("Could not connect " . pg_last_error());
	       $stat = pg_connection_status($link);
	       if($stat === PGSQL_CONNECTION_OK)
	       {
	         echo "<form action='spiller.php' method='get'>\n";
	         echo "<select name='spiller' onchange='redirect(this.value);'>\n";
	         $res1 = pg_query($link, "select playername from tbl_player");
	         if(!$res1)
	         {
	           echo "En feil har oppstått.\n";
	           exit;
	         }
	         echo "<option selected>Velg en spiller</option>\n";
	         while($row = pg_fetch_row($res1))
	         {
	           echo "<option>$row[0]</option>\n";
	         }
	         echo "</select>\n";
	         echo "<input type='submit' value='Send'>\n";
	         echo "</form>\n";
	         $chosen = $_GET["spiller"];
	         if($chosen == "Velg en spiller")
	         {
	           echo "Vennligst velg en spiller fra listen ovenfor.\n";
	           exit;
	         }
	         $res2 = pg_query($link, "select playername, playernumber, positionname, nationname, teamname from qry_player where playername='" . $chosen . "';");
	         if(!$res2)
	         {
	           echo "En feil har oppstått.";
	           exit;
	         }
	         if($row = pg_fetch_row($res2))
	         {
	           echo "<table border='0'>";
	           echo "<tr>";
	           echo "<td colspan='2'>";
	           echo "<h1>$row[0]</h1>";
	           echo "</td>\n</tr>";
	           echo "<tr>\n<td valign='top'>";
	           echo "Nummer";
	           echo "</td>\n<td valign='top'>";
	           echo "$row[1]\n";
	           echo "</td>\n</tr>\n<tr>\n<td valign='top'>\n";
	           echo "Baneposisjon\n";
	           echo "</td>\n<td valign='top'>\n";
	           echo "$row[2]\n";
	           echo "</td>\n</tr>\n<tr>\n<td valign='top'>\n";
	           echo "Nasjon\n";
	           echo "</td>\n<td valign='top'>\n";
	           echo "$row[3]\n";
	           echo "</td>\n</tr>\n<tr>\n<td valign='top'>\n";
	           echo "Lag\n";
	           echo "</td>\n<td valign='top'>\n";
	           echo "$row[4]\n";
	           echo "</td>\n</tr>\n";
	           echo "</table>";
	         }
	       }
	       else
	       {
	         echo "Not connected/bad connection.\n";
	       }
	    ?>
	  </td>
	</tr>
	<tr>
	  <td colspan="2">
	    MERK: Bakgrunnsbildet er av Millennium Stadium, ikke Cardiffs hjemmebane.
	  </td>
	</tr>
      </table>
  </body>
</html>
