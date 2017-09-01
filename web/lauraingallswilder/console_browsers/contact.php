<html>
  <head>
    <title>Kontakt webmasteren</title>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <link rel="stylesheet" type="text/css" href="../css/laura_main.css" />
    <script type="text/javascript" src="../js/laura_main.js"></script>
  </head>
  <body>
    MENY<br />
    <a href="characters.php">Familien Ingalls</a><br />
    <a href="towns.php">Byene Laura bodde i</a><br />
    <a href="books.php">Little House-bøkene</a><br />
    <a href="contact.php">Kontakt</a><br />
    <a href="tvseries.php">TV-serie</a><br />
    <a href="tvminiseries.php">TV-miniserie</a>
    <br />
    <h1>Kontakt webmasteren</h1>
    <br />
    <br />
    På denne siden kan du ta kontakt med webmasteren.
    Dette gjør du ved å fylle ut skjemaet som står nedenfor.
    Merk at alle felt med * må fylles ut, enten du liker det eller ikke.    
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
          //echo "<div id='sentMessage'>\n"
          echo "\nDin epost skal ha blitt sendt.\n";
          //echo "</div>\n";
       }
       else
       {
          echo "<form action='contact.php' method='post'>\n";
          echo "Navn*   : <input type='text' name='navn' /><br />\n";
          echo "E-post* : <input type='text' name='epost' /><br />\n";
          echo "Emne    : <input type='text' name='emne' /><br />\n";
          echo "Melding*: <textarea name='melding' rows='10' cols='32'></textarea><br />\n";
          echo "<input type='Submit' value='Send' />\n";
          echo "</form>\n";
       }
    ?>
  </body>
</html>

