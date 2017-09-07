<html>
  <head>
    <title>Test med video</title>
    <link rel="stylesheet" type="text/css" href="css/video.css">
    <script type="text/javascropt" src="js/main.js"></script>
    <script type="text/javascript" src="js/klokke.js"></script>
  </head>
  <body onload="show3();" oncontextmenu="return false;">
  <script type="text/javascript">
  </script>
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
      <a href="https://www.microsoft.com/en-us/windows/microsoft-edge">Microsoft Edge (Windows 10 og nyere)</a>
    </noscript>
    <img src="images/c0.gif" name="a"><img src="images/c0.gif" name="b"><img src="images/colon.gif" name="c"><img src="images/c0.gif" name="d"><img src="images/c0.gif" name="e"><img src="images/colon.gif" name="f"><img src="images/c0.gif" name="g"><img src="images/c0.gif" name="h">
    <br />
    Dette er en side hvor jeg tester ut video med HTML 5.
    <br />
    <br />
    <div id="main" style="visibility:hidden">
      <?php
	 echo "IP-adresse: " . $_SERVER['REMOTE_ADDR'];
       $link = pg_connect("user=andersbo password=mPecGt87! dbname=media") or die("Kunne ikke koble til databasen");
       $stat = pg_connection_status($link);
       if($stat === PGSQL_CONNECTION_OK){
         echo "<form action='index.php' method='get'>\n";
         echo "<select name='serie' onchange='redirect(this.value);'>\n";
         $res1 = pg_query($link, "select serienavn, typenr from serie");
         if(!$res1){
       		echo "En feil har oppstått.\n";
       		exit;	
         }
         echo "<option selected>Velg en serie</option>\n";
         while($row = pg_fetch_row($res1)){
         	if($row[0] == "Ingen serie")
         		continue;
         	if($_SERVER['REMOTE_ADDR'] != "::1" && $row[1] == "1"){
                     $sub = substr($_SERVER['REMOTE_ADDR'],0,6);
                     if($sub != "10.0.0"){
	               if($sub != "127.0.")
                          continue;
	             }
         	}
         	echo "<option>$row[0]</option>\n";
         }
         echo "</select>\n";
         echo "<input type='submit' value='Send'>\n";
         echo "</form>";
         $chosen = $_GET["serie"];
         if($chosen == "Velg en serie"){
         	echo "Vennligst velg en serie fra lista ovenfor.\n";
         	//exit;
         }
	 else{
	   $newres = pg_query($link, "select seriebeskrivelse from serie where serienavn='" . $_GET["serie"] . "';");
	   if(!$newres){
	      echo "En feil har oppstått.\n";
	      exit;
	   }
	   if($newrow = pg_fetch_row($newres)){
	     echo "<h3>Seriebeskrivelse</h3>\n";
	     echo "<p>$newrow[0]</p>\n";
	   }
	 }
         //echo "<form action='index.php' method='get'>\n";
         //echo "<select name='film' onchange='redirect(this.value);'>\n";
         $res2 = pg_query($link, "select filmnavn from view_film where serienavn='" . $chosen ."' order by filmnavn asc;");
         /*if(!$res2){
         	echo "En feil har oppstått.\n";
         	exit;
         }*/
         //echo "<option selected>Velg en film</option>\n";
	 echo "Serien består av følgende episoder:<br />\n";
         while($row1 = pg_fetch_row($res2)){
         	//echo "<option>$row1[0]</option>\n";
         	$link = str_replace(' ', '+', $row1[0]);
         	echo "<a href='index.php?film=$link'>$row1[0]</a><br />";
         }
         //echo "</select>\n";
         //echo "<input type='submit' value='Send'>\n";
         //echo "</form>";
	 
         $valgtfilm = $_GET['film'];
         if($valgtfilm == "Velg en film"){
         	echo "Vennligst velg en film fra lista ovenfor.";
         	exit;
         }
         $res3 = pg_query ($link, "select filmnavn, serienavn, typenavn, lengde, beskrivelse, filbane from view_film where filmnavn = '" . $valgtfilm . "';");
         /*if(!$res3){
         	echo "En feil har oppstått.";
         	exit;
         }*/
         if($row3 = pg_fetch_row($res3)){
         	/* 
         	Oppretter en tabell som inneholder følgende informasjon:
         	Tittel, serie, lengde, beskrivelse, i tillegg til selve filmen.
         	*/
         	echo "<table border='0'>\n";
         	echo "<tr>\n";
         	echo "<td colspan='2'>\n";
         	echo "<h1>Filminfo</h1>\n";
         	echo "</td>\n</tr>\n";
         	echo "<tr>\n<td valign='top'>\n";
         	echo "Tittel\n";
         	echo "</td>\n<td valign='top'>\n";
         	echo "$row3[0]\n";
         	echo "</td>\n</tr>\n";
         	echo "<tr><td valign='top'>\n";
         	echo "Serie\n";
         	echo "</td>\n<td valign='top'>\n";
         	$nylink = str_replace(' ', '+', $row3[1]);
         	echo "<a href='index.php?serie=$nylink'>$row3[1]</a>";
         	echo "</td></tr>\n";
         	echo "<tr>\n<td valign='top'>\n";
         	echo "Type\n";
         	echo "</td>\n<td valign='top'>\n";
         	echo "$row3[2]\n";
         	echo "</td>\n</tr>\n";
         	echo "<tr><td valign='top'>\n";
         	echo "Lengde\n";
         	echo "</td>\n<td valign='top'>\n";
         	echo "$row3[3]\n";
         	echo "</td>\n</tr>\n";
         	echo "<tr><td valign='top'>\n";
         	echo "Beskrivelse\n";
         	echo "</td>\n<td valign='top'>\n";
         	echo "$row3[4]\n";
         	echo "</td>\n</tr>\n";
         	echo "<tr>\n<td colspan='2'>\n";
         	echo "<video width='1024' height='576' controls='true'>\n";
         	echo "<source src='$row3[5]' type='video/mp4'>\n";
         	echo "Nettleseren din har ikke støtte for video-tagen. Støtter ikke nettleseren HTML5?\n";
         	echo "</video>\n";
         	echo "</td>\n</tr>\n";
         	echo "</table>\n";
         }
       }
       else{
         echo "Ikke koblet til eller dårlig forbindelse.\n";
       }
    ?>
    <script>
      document.getElementById("main").style.visibility = 'visible';
    </script>
  </body>
</html>
