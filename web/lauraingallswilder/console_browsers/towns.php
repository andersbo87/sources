<html>
  <head>
    <title>Byene Laura og familien har bodd i</title>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <script type="text/javascript" src="../js/laura_main.js"></script>
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
     </script>
  </head>
  <body>
    MENY<br />
    <a href="characters.php">Familien Ingalls</a><br />
    <a href="towns.php">Byene Laura bodde i</a><br />
    <a href="books.php">Little House-bøkene</a><br />
    <a href="contact.php">Kontakt</a><br />
    <a href="tvseries.php">TV-serie</a><br />
    <a href="tvminiseries.php">TV-miniserie</a><br >
    <br />
    <h1>Byene Laura og familien har bodd i</h1>
    <br />
    <br />
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
       $link = mysql_connect("localhost", "webuser", "webuser");
       if(!$link)
       {
          die("Kunne ikke koble til: " . mysql_error());
       }
       $dbname = "little_house";
       mysql_select_db($dbname);
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
          $result=mysql_query("SELECT * FROM tbl_town WHERE townName='" . $chosen . "'") or die(mysql_error());
          $row = mysql_fetch_array($result);
          echo "<h2>" . $row["townName"] . "</h2>\n";
          echo "<br /><br />\n";
          echo $row["townInfo"] . "\n";
       }
       mysql_close($link);
    ?>
  </body>
</html>
