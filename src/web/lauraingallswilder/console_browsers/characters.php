<html>
  <head>
    <title>Familien Ingalls</title>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <script type="text/javascript" src="../js/laura_main.js"></script>
    <script type="text/javascript">
      function redirect(page)
      {
        if(page == 0)
        {
          window.location = "characters.php";
        }
        if(page =1)
        {
          window.location = "characters.php?character=1";
        }
        if(page =2)
        {
          window.location = "characters.php?character=2";
        }
        if(page =3)
        {
          window.location = "characters.php?character=3";
        }
        if(page =4)
        {
          window.location = "characters.php?character=4";
        }
        if(page =5)
        {
          window.location = "characters.php?character=5";
        }
        if(page =6)
        {
          window.location = "characters.php?character=6";
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
    <a href="tvminiseries.php">TV-miniserie</a><br />
    <br />
    <h1>Familien Ingalls</h1>
    <br />
    <br />
    Her finner du informasjon om den virkelige familien Ingalls. <br />
    Informasjonen er basert på engelskspråklige Wikipedia-artikler
    og biografien "Laura Ingalls Wilder: A Biography" 
    av William Anderson.<br />
    
    Velg ett av navnene fra listen nedenfor for å lære mer om- eller
    bli "bedre 'kjent'" med denne karakteren/personen.
    <br />
    <br />
    <?php 
       $link = mysql_connect("localhost", "webuser", "webuser");
       if(!$link)
       {
         die("Could not connect: " . mysql_error());
       }
       $dbname = "little_house";
       mysql_select_db($dbname);
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
          $result = mysql_query("SELECT * FROM tbl_characters WHERE name='" . $chosen . "'") or die(mysql_error());
          $row = mysql_fetch_array($result);
          echo "<h2>" . $row["name"] . "</h2>\n";
          echo "<br /><br />\n";
          echo $row["biography"] . "\n";
       }
       mysql_close($link);
    ?>
  </body>
</html>
