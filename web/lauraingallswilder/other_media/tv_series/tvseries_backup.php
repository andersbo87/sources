<html>
  <head>
    <title>"Little House on the Prairie" TV-serie</title>
    <link rel="stylesheet" type="text/css" href="../../css/laura_main.css" />
    <link rel="shortcut icon" href="../../images/lauraingallswilder/little_house_icon.ico" />
    <script type="text/javascript" src="../../js/laura_main.js"></script>
    <script type="text/javascript" src="../../js/laura_klokke.js"></script>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
  </head>
  <body oncontextmenu="alert('No copying is allowed'); return false">
    <?php
       $link = mysql_connect('localhost', 'root', 'klaand');
       if(!$link)
       {
          die('Could not connect: ' . mysql_error());
       }
       $dbname = "little_house";
       mysql_select_db($dbname);
       $result = mysql_query("SELECT * FROM qry_episodes WHERE episodeId=1") or die(mysql_error());
       $row = mysql_fetch_array($result);
       echo "<table border='0'>";
       echo "<tr>";
       echo "<td valign='top'>";
       echo "Episode ID";
       echo "</td>";
       echo "<td valign='top'>";
       echo $row["episodeID"];
       echo "</td>";
       echo "</tr>";
       echo "<tr>";
       echo "<td valign='top'>";
       echo "Episode Name";
       echo "</td>";
       echo "<td valign='top'>";
       echo $row["episodeName"];
       echo "</td>";
       echo "</tr>";
       echo "<tr>";
       echo "<td valign='top'>";
       echo "Episode Description";
       echo "</td>";
       echo "<td valign='top'>";
       echo $row["episodeDescription"];
       echo "</td>";
       echo "</tr>";
       echo "<tr>";
       echo "<td valign='top'>";
       echo "Season";
       echo "</td>";
       echo "<td valign='top'>";
       echo $row["season"];
       echo "</td>";
       echo "</tr>";
       echo "<tr>";
       echo "<td valign='top'>";
       echo "Notes";
       echo "</td>";
       echo "<td valign='top'>";
       echo $row["notes"];
       echo "</td>";
       echo "</tr>";
       echo "</table>";
       mysql_close($link);
     ?>
  </body>
</html>
