<html>
  <head>
    <?php
      include('readfile.php');
    ?>
    <link rel="stylesheet" type="text/css" href="css/main.css" />
    <script type="text/javascript" src="js/main.js"></script>
    <script type="text/javascript" src="js/klokke.js"></script>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <title>Lag</title>
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
	  Her vil du få informasjon om de ulike lagene (aldersbestemte og A-lag) til Cardiff.
	  Velg et lag fra listen nedenfor.
	  <?php
	    //echo "$file";
	     $link = pg_connect("user=webuser dbname=cardiffcityfc password=$file") or die("<br />Could not connect " . pg_last_error());
             $stat = pg_connection_status($link);
             if($stat === PGSQL_CONNECTION_OK)
             {
	       echo "<form action='lag.php' method='get'>";
	       echo "<select name='team' onchange='redirect(this.value);'>\n";
	       $res1 = pg_query($link, "select teamname from tbl_team");
               if(!$res1)
               {
                 echo "En feil har oppstått.\n";
                 exit;
               }
               echo "<option selected>Velg et lag</option>\n";
	       while($row = pg_fetch_row($res1))
	       {
	         echo "<option>$row[0]</option>\n";
	       }
	       echo "</select>\n";
               echo "<input type='submit' value='Send'>\n";
               echo "</form>\n";
	       $chosen = $_GET["team"];
               if($chosen == "Velg et lag")
               {
                 echo "Vennligst velg et lag fra listen ovenfor.\n";
                 exit;
               }
               $teamres = pg_query($link, "select teamname, teamdescription from tbl_team where teamname='" . $chosen . "';");
               if(!$teamres)
               {
                 echo "En feil har oppstått.";                  
	         exit;
               }
               if($row = pg_fetch_row($teamres))
               {
	         echo "<table border='0'>\n<tr><td colspan='2'>\n";
	         echo "<h1>Cardiffs $row[0]</h1>\n";
	         echo "</td></tr><tr><td valign='top'>\n";
	         echo "</td><td valign='top'>\n";
	         echo "$row[1]\n";
	         echo "</tr></td></table>\n";
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
