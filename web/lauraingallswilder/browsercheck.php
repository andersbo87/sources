<html>
  <head>
    <title>Browser Check</title>
  </head>
  <body>
    <?php
       $oldstring = $_SERVER['HTTP_USER_AGENT'] . "\n\n";
       //echo "Old string: " . $oldstring;
       //echo "<br />";
       $i = strpos($oldstring, "/");
       $newstring = substr($oldstring,0,$i);
       //echo $newstring;
    ?>
  </body>
</html>
