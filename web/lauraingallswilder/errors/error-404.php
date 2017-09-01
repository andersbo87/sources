<html>
<head>
	<title>Siden ble ikke funnet.</title>
	<link rel="shortcut icon" href="/lauraingallswilder/images/lauraingallswilder/little_house_icon.ico" />
    	<link rel="stylesheet" type="text/css" href="/lauraingallswilder/css/laura_main.css" />
    	<script type="text/javascript" src="/lauraingallswilder/js/laura_main.js"></script>
    	<script type="text/javascript" src="/lauraingallswilder/js/laura_klokke.js"></script>
    	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
</head>
<body onload="show3();">
<table border="0">
       <tr>
		<td colspan="2">
		    <img src="/lauraingallswilder/images/laura-banner.jpg" oncontextmenu="return true;" />
		    <br />
		    <script type="text/javascript" src="/lauraingallswilder/js/dateScript.js"></script>
		    klokken
		    <img src="/lauraingallswilder/images/c0.gif" name="a"><img src="/lauraingallswilder/images/c0.gif" name="b"><img src="/lauraingallswilder/images/colon.gif" name="c"><img src="/lauraingallswilder/images/c0.gif" name="d"><img src="/lauraingallswilder/images/c0.gif" name="e"><img src="/lauraingallswilder/images/colon.gif" name="f"><img src="/lauraingallswilder/images/c0.gif" name="g"><img src="/lauraingallswilder/images/c0.gif" name="h">
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
                       onclick="window.location.href='/lauraingallswilder/towns.php'" />
                <br />
                <input type="button"
                       value="Familien Ingalls"
                       style="width: 200px"
                       onclick="window.location.href='/lauraingallswilder/characters.php'" />
                <br />
                <input type="button"
                       value="Kontakt"
                       style="width: 200px"
                       onclick="alert('Kontaktsiden er ikke opprettet ennå.');" />
                <br />
                <input type="button"
                       value="Little House-bøkene"
                       style="width: 200px"
                       onclick="window.location.href='/lauraingallswilder/books.php'" />
                <br />
                <input type="button"
                       value="TV-miniserie"
                       style="width: 200px"
                       onclick="alert('Siden med informasjon om miniserien fra 2005 er ikke opprettet ennå');" />
                <br />
                <input type="button"
                       value="TV-serie"
                       style="width: 200px"
                       onclick="askUserConfirmation();" />
                       <br />
           	    </form>
		</td>
		<td valign="top" id="main">
	    		 <h1>Siden ble ikke funnet.</h1>
	    	</td>
	</tr>
	<tr>
		<td valign="top" width="700px" id="main">
		    <?php
			$map = array('/old/1' => '/new/2.html',
	     		'/old/2' => '/new/3.html');

			if (isset($map[$_SERVER['REDIRECT_URL']])) 
			{
    			   $new_loc = 'http://' . 
               		   $_SERVER['HTTP_HOST'] . 
               		   $map[$_SERVER['REDIRECT_URL']];
    			   if (isset($_SERVER['REDIRECT_QUERY_STRING'])) {
        		      $new_loc .= '?' . 
                    	      $_SERVER['REDIRECT_QUERY_STRING'];
    			   }
    			   header("Location: $new_loc");
			}
			else 
			{
    			   print "Siden ble ikke funnet.<br />Innholdet på dette systemet er <i>case-sensitivt</i><br />hvilket betyr at det er forskjell mellom store og små bokstaver.<br />Vennligst se til at du bruker små og store bokstaver på rett plass i adressefeltet.";
			}
		    ?>
		</td>
	</tr>
	</table>
	</body>
</html>
