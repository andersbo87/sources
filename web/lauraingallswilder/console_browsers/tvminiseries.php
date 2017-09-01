<html>
  <head>
    <title>TV miniserie</title>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <script type="text/javascript" src="../js/laura_main.js"></script>
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
    <h1>TV miniserie</h1>
    <br />
    <br />
    På denne siden vil du finne informasjon om en miniserie som ble
    produsert av amerikanske ABC og sendt i 2005.
    Serien består av i alt 3 episoder som hver er delt opp i 2 deler.
    <?php
       echo "<form action='tvminiseries.php' method='get'>\n";
       echo "Episode ID: \n";
       echo "<select name='miniseries' onchange=redirect(this.value);>\n";
       echo "<option selected='chosen'>Velg en episode</option>\n";
       echo "<option>Little House in the Big Woods</option>\n";
       echo "<option>The Ingalls' Journey</option>\n";
       echo "<option>Adventures on the Kansas Prairie</option>\n";
       echo "</select>\n";
       echo "<input type='submit' value='Send'>\n";
       echo "</form>\n";
       $chosen = $_GET["miniseries"];
       if($chosen == "Velg en episode")
       {
          echo "Vennligst velg en episode fra listen ovenfor";
       }
       else
       {
          if($chosen == "Little House in the Big Woods")
          {
             echo "This is the first of 3 2-part episodes.\n";
             echo "<b>Del 1</b>: ";
             echo "<br />";
             echo "<a href='characters.php?character=Charles+Ingalls'> Charles</a>";
             echo " tar med seg familien ut fra"; 
             echo " <a href=books.php?book=Little+House+in+the+Big+Woods'>de store";
             echo " skogene</a>, ved byen <a href=towns.php?town=Pepin>Pepin</a> og leder dem ut på";
             echo " stien mot et prærieliv i Kansas. På ferden krysser de en ikke helt frossen";
             echo " Lake Pepin (en del av elva Mississippi) og får med det en smaksprøve på alle";
             echo " farene de vil møte på. Etter å ha krysset elven, blir den ene hesten bitt av en";
             echo " slange, og må skytes. Hestene blir byttet ut mot et par unge mustanger.";
             echo " Etterhvert som reisen skrider frem, slår kjedsomheten seg inn over";
             echo " <a href=characters.php?character=Mary+Ingalls>Mary</a>";
             echo " og <a href=characters.php?character=Laura+Ingalls>Laura</a>,";
             echo " mens <a href=characters.php?character=Caroline+Ingalls>Caroline ('Ma')</a>";
             echo " begynner å lure på om det var en god idé å reise.";
             echo "<br /><br />";
             echo "<b>Del 2</b>";
             echo "<br />";
             echo "Etter å ha krysset en elv med sterk strøm, tror familien";
             echo " at de har mistet sin kjære hund Jack, men det viser seg";
             echo " etterhvert at han ikke døde. De kommer seg frem til";
             echo " Kansas og møter så en fremtidig spyttende 'villkatt'";
             echo " av en nabo som heter Edwards. Pa bygger huset de skal";
             echo " bo i, spesielt med hjelp fra Edwards";
             echo " etter et uhell med Caroline.";
          }
          else if($chosen == "The Ingalls' Journey")
          {
             echo "<b>Del 1</b>";
             echo "<br />";
             echo "Nå som familien har slått seg ned,";
             echo " møter de på nye utfordringer: Mygg og indianere.";
             echo " Samtidig møter de på nye naboer i familien Scott:";
             echo " Den avskyelige Mrs. Scott og hennes langt mer hyggelige";
             echo " ektemann, Mr. Scott. Etter å ha gjort sitt for å";
             echo " beskytte hjemmet deres, blir familien Ingalls rammet";
             echo " av et malariautbrudd. De kommer seg gjennom prøvelsene,";
             echo " og mot slutten av 1. del, blir ";
             echo "<a href=characters.php?character=Charles+Ingalls>Charles</a> ";
             echo " tilbudt en cowboyjobb hvor belønningen er ei ku og en kalv.";
             echo "<br />";
             echo "<br />";
             echo "<b>Del 2</b>";
             echo "<br />";
             echo "Del 2 av denne episoden kan deles opp slik:";
             echo " De første 2/3 inneholder flere vanskeligheter";
             echo " ved at Charles tar seg en tur til byen for å handle";
             echo " og hente et brev hjemmefra, men han møter isteden";
             echo " på en mindre hyggelig lokalbefolkning.";
             echo " Samtidig begynner indianerne på nytt å vise seg ved";
             echo " å dra på et nytt overraskende besøk til familien.";
             echo " Den siste delen handler om jul.";
             echo " Pga mye regn virker det ut til at jula blir";
             echo " en \"katastrofe\" ved at Charles verken får skaffet";
             echo " julemiddag eller gaver. Men for julenissen kan det";
             echo " ikke bli for mye regn, pga Mr. Edwards som sørget for at";
             echo " Ingalls-familien tross alt fikk en hyggelig feiring.";
          }
          else if($chosen == "Adventures on the Kansas Prairie")
          {
             echo "<b>Del 1</b>";
             echo "<br />";
             echo "<a href=characters.php?character=Charles+Ingalls>Pa</a>";
             echo " må kjempe for livet når han møter en fjelløve.";
             echo " Dette skal vise seg bare å være starten på diverse";
             echo " bekymringer for familien. Gården deres blir rammet";
             echo " av brann, og ryktene i";
             echo " <a href=towns.php?town=Independence>Independence</a>";
             echo " vil ha det til at det er indianere som står bak.";
             echo " Edwards (som selv fikk hjemmet sitt ødelagt av indianerne";
             echo " mens han selv var hjemme) og Ingalls-familen forbereder";
             echo " seg på den fryktede, men ventede krigen ved å barrikadere";
             echo " seg i huset til familien Scott.";
             echo "<br />";
             echo "<br />";
             echo "<b>Del 2</b>";
             echo "<br />";
             echo "Som en følge av forhandlinger som foregikk mellom";
             echo " myndigheter og indianere, samtidig som krigen foregikk,";
             echo " bestemmer indianerne seg til slutt for å flytte vestover,";
             echo " hvilket gir Ingalls-familien en mulighet til å utforske";
             echo " indianerleieren. Men gleden over å ha vunnet over";
             echo " indianerne blir kortvarig når noen soldater kommer";
             echo " og forteller familien at de hadde slått seg ned mens det";
             echo " var forbudt å slå seg ned på jorda indianerne måtte forlate.";
             echo " Selv om <a href=characters.php?character=Charles+Ingalls>";
             echo "Charles</a> og";
             echo " <a href=characters.php?character=Laura+Ingalls>Laura</a>";
             echo " bønnfaller mannen på jordbrukskontoret, blir avgjørelsen";
             echo " stående som et eksempel på avtalen med indianerne.";
             echo " Den siste delen innehoer farvelet familien tar med naboene";
             echo " i det de legger ut på en reise mot et ubestemt sted.";
          }
       }
       //mysql_close($link);
    ?>
  </body>
</html>
