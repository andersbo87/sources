/*
 *  database_commands.c
 *  lh
 *
 *  Created by Anders Bolt-Evensen on 19.06.10.
 *  Copyright 2010 Høgskolen i Østfold. All rights reserved.
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <mysql.h>
#include <assert.h>
//#include <readline/readline.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <pwd.h>
#include <unistd.h>
#include <ctype.h>
#include "database_commands.h"
char user[100];
char *password;
MYSQL *conn;

void catch_sigill(int sig_num)
{
  signal(SIGILL, catch_sigill);
  if(conn != NULL){
    fprintf(stdout, "Closing MySQL connection...\n");
    mysql_close(conn);
    fprintf(stderr, "MySQL database connection closed because of a fatal error.\n");
  }
  fprintf(stderr,
	  "\n***Caught SIGILL signal.***\n"
	  "lh has made an illegal instruction and needs to be closed. If core dumps are enabled, a core dump will be created for further debugging.\n"
	  "Quitting...\n");
  signal(sig_num, SIG_DFL);
  kill(getpid(), sig_num);
}

void catch_int7(int sig_num)
{
  signal(SIGBUS, catch_int7);
  if(conn != NULL){
    fprintf(stdout, "Closing MySQL connection...\n");
    mysql_close(conn);
    fprintf(stderr, "MySQL database connection closed because of a fatal error.\n");
  }
  printf("\n***Caught SIGBUS signal. Quitting.\n");
  //exitApp(SIGBUS, "A bus error has occurred.");
  signal(sig_num, SIG_DFL);
  kill(getpid(), sig_num);
}

void catch_int6(int sig_num)
{
  signal(SIGSEGV, catch_int6);
  if(conn != NULL){
    fprintf(stdout, "Closing MySQL connection...\n");
    mysql_close(conn);
    fprintf(stderr, "MySQL database connection closed because of a fatal error.\n");
  }
  printf("\nA segmentation violation error has been caught. "
	 "The program is trying to access memory that has "
	 "not been allocated to this program, "
	 "due to, in most cases, a bug in the program code.\n"
	 "If you have enabled core dumps, a core will be dumped "
	 "so that you can debug the program using i.e. gdb.\n");
  printf("\n***Process %d caught SIGTERM signal. Quitting...***\n", getpid());
  signal(sig_num, SIG_DFL);
  kill(getpid(), sig_num);
}

void catch_int5(int sig_num)
{
  signal(SIGQUIT, catch_int5);
  printf("\n***Caught ctrl-\\ signal***\n");
  printf("Please press ctrl-c on your keyboard to quit.\n");
  search();
}

void catch_int4(int sig_num)
{
  signal(SIGHUP, catch_int4);
  printf("\n***Caught SIGHUP signal***\n"
	 "Please press ctrl-c on your keyboard to quit.\n");
  search();
}

void catch_int3(int sig_num)
{
  signal(SIGABRT, catch_int3);
  if(conn != NULL){
    fprintf(stdout, "Closing MySQL connection...\n");
    mysql_close(conn);
    fprintf(stderr, "MySQL database connection closed because of a fatal error.\n");
  }
  printf("\n***An abort trap has been caught.***\n"
	 "Process %d is quitting...\n", getpid());
    signal(sig_num, SIG_DFL);
    kill(getpid(),sig_num);
}

void catch_int2(int sig_num)
{
  signal(SIGTSTP, catch_int2);
  printf("\n***Caught ctrl-z signal\n"
	 "Please press ctrl-c on your keyboard to quit.\n");
  search();
}

void catch_int(int sig_num)
{
  signal(SIGINT, catch_int);
  printf("\n***Caught ctrl-c signal.***\n"
	 "Please type 'q' to quit.\n");
  //search();
}


void usernameAndPasswordInitialize()
{
  signal(SIGBUS, catch_int7);
  signal(SIGSEGV, catch_int6);
  signal(SIGILL, catch_sigill);
  //asking for the MySQL username
  fprintf(stdout, "Type your MySQL username: ");
  fgets(user, 100, stdin);
  if(user[strlen(user) -1] == '\n')
    {
      user[strlen(user)-1] = '\0';
    }
  assert(&user != NULL);
  password = getpass("Type your mysql password: "); //reads the mysql password
  long passwdlength=strlen(password);
  /*
   * Checking the password length. To prevent a SIGBUS, I require that the
   * password be 1 or more characters long.
   */
  if (passwdlength == 0)
  {
    char msg[] = 
      "A password longer than 1 character is required. "
      "Please type 'mysqladmin -u ";
    strcat(msg, user);
    strcat(msg, " password', and then run lh again.");
    exitApp(1, msg);
  }
  createDatabase(user);
  createTable();
  insertCharacters();
  insertTowns();
  insertBooks();
  insertSeasons();
  insertEpisodes();
}
void createDatabase(char *u)
{
  fprintf(stdout, "Creating database unless it exists.\n");
  MYSQL *conn;
  char errorString[1000] = "In function createDatabase(): MySQL error: ";
  char *server = "localhost";
  char *mysql_user = user;
  char *mysql_passwd = password;
  //char *database = "little_house";
  conn = mysql_init(NULL);
  if(conn == NULL)
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  //if(!mysql_real_connect(conn, server, u, mysql_passwd, NULL, 0, NULL,0))
  if(!mysql_real_connect(conn, server, mysql_user, mysql_passwd, NULL, 0, NULL, 0))
    {
        //exitApp(mysql_errno(conn), "Incorrect combination of username and password.");
        if(mysql_errno(conn) == 1045)
            exitApp(mysql_errno(conn), strcat(errorString, "Incorrect combination of username and password."));
        else
            exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  if(mysql_query(conn, "CREATE DATABASE IF NOT EXISTS little_house DEFAULT CHARACTER SET utf8 COLLATE UTF8_UNICODE_CI;"))
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  mysql_close(conn);
}

void createTable()
{
  fprintf(stdout, "Creating tables...\n");
  char ctErrorString[250] = "In function createTable(): MySQL error: ";
  //MYSQL *conn;
  char *server = "localhost";
  char *userName = user;
  char *passwd = password;
  char *database = "little_house";
  conn = mysql_init(NULL);
  if(conn == NULL)
    {
      const char *err = mysql_error(conn);
      strlcat(ctErrorString, err, sizeof(ctErrorString));
      exitApp(mysql_errno(conn), ctErrorString);
    }
  if(!mysql_real_connect(conn, server, userName, passwd, database, 0, NULL,0))
    {
      const char *err = mysql_error(conn);
      strlcat(ctErrorString, err, sizeof(ctErrorString));
      exitApp(mysql_errno(conn), ctErrorString);
    }
  if(mysql_query(conn, "CREATE TABLE IF NOT EXISTS tbl_characters(characterID int not null, name varchar(100) not null, biography text not null, primary key(characterID));"))
    {
      const char *err = mysql_error(conn);
      strlcat(ctErrorString, err,sizeof(ctErrorString));
      exitApp(mysql_errno(conn), ctErrorString);
    }
  if( mysql_query(conn, "CREATE TABLE IF NOT EXISTS tbl_books(bookID int not null, bookTitle varchar(100) not null, norwegianTitle varchar(100) not null, initialRelease int not null, newestRelease int not null, mainCharacters varchar(500) not null, guestCharacters varchar(500), otherCharacters varchar(500), pages int not null, description varchar(10000) not null, primary key(bookID));"))
    {
      const char *err = mysql_error(conn);
      long l = strlen(err);
      strlcat(ctErrorString, err, sizeof(ctErrorString));
      exitApp(mysql_errno(conn), ctErrorString);
    }
  if (mysql_query(conn, "CREATE TABLE IF NOT EXISTS tbl_movie(movieID int not null, title varchar(100) not null, companyID int not null, primary key(movieID));"))
    {
      const char *err = mysql_error(conn);
      strlcat(ctErrorString, err, sizeof(ctErrorString));
      exitApp(mysql_errno(conn), ctErrorString);
    }
  if(mysql_query(conn, "CREATE TABLE IF NOT EXISTS tbl_town(townID int not null, townName varchar(50) not null, townInfo varchar(10000) not null, primary key(townID));"))
    {
      const char *err = mysql_error(conn);
      strlcat(ctErrorString, err, sizeof(ctErrorString));
      exitApp(mysql_errno(conn), ctErrorString);
    }
  if(mysql_query(conn, "CREATE TABLE IF NOT EXISTS tbl_company(companyID int not null, companyName varchar(100) not null, primary key(companyID));"))
    {
      const char *err = mysql_error(conn);
      strlcat(ctErrorString, err, sizeof(ctErrorString));
      exitApp(mysql_errno(conn), ctErrorString);
    }
  if (mysql_query(conn, "CREATE TABLE IF NOT EXISTS tbl_episodes(episodeID int not null, episodeName varchar(100) not null unique, episodeDescription varchar(12000) not null, seasonID int not null, notes varchar(1000), primary key(episodeID));"))
    {
      const char *err = mysql_error(conn);
      strlcat(ctErrorString, err, sizeof(ctErrorString));
      exitApp(mysql_errno(conn), ctErrorString);
    }
  if (mysql_query(conn, "CREATE TABLE IF NOT EXISTS tbl_season(seasonID int not null, season varchar(100) not null, season_description varchar(10000) not null, primary key(seasonID));"))
    {
      const char *err = mysql_error(conn);
      strlcat(ctErrorString, err, sizeof(ctErrorString));
      exitApp(mysql_errno(conn), ctErrorString);
    }
  if (mysql_query(conn, "CREATE OR REPLACE VIEW qry_episodes as select episodeID, episodeName, episodeDescription, tbl_episodes.seasonID, season, notes from tbl_episodes, tbl_season where tbl_season.seasonID = tbl_episodes.seasonID;"))
    {
      const char *err = mysql_error(conn);
      strlcat(ctErrorString, err, sizeof(ctErrorString));
      exitApp(mysql_errno(conn), ctErrorString);
    }
  if (mysql_query(conn, "CREATE OR REPLACE VIEW qry_movieAndCompany AS SELECT movieID, title, tbl_movie.companyID, companyName FROM tbl_movie, tbl_company WHERE tbl_company.companyID=tbl_movie.companyID;"))
    {
      const char *err = mysql_error(conn);
      strlcat(ctErrorString, err, sizeof(ctErrorString));
      exitApp(mysql_errno(conn), ctErrorString);
    }
  mysql_close(conn);
}

void insertTowns()
{
  fprintf(stdout, "Inserting towns...\n");
  char errorString[150] = "In function insertTowns(): MySQL error: ";
  //MYSQL *conn;
  char *server = "localhost";
  char *userName = user;
  char *passwd = password;
  char *database = "little_house"; 
  conn = mysql_init(NULL);
  if(conn == NULL)
    { 
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  if(!mysql_real_connect(conn,server,userName, password, database, 0, NULL, 0))
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  if(mysql_query(conn, 
		 "INSERT IGNORE INTO tbl_town VALUES (1, \"Burke\",\""
		 "Burke er en liten by i fylket Franklin County "
		 "i New York State. Etter folketellinga i 2000 "
		 "var det 1359 innbyggere i Burke. "
		 "Byen er oppkalt etter filosofen Edward Burke "
		 "<br /><br /><b>Historie</b></br></br> "
		 "Området rundt Burke ble bebygd rundt år 1800 ved navn "
		 "Zachary Tyler Burke. Dette området var da kjent som "
		 "'West Chateaugay' og ble foreslått til å være "
		 "'Town of Birney', men man bestemte seg for å bruke navnet "
		 "Burke isteden. I 1844 ble byen formet fra Chateaugay. "
		 "Almanzo Wilder som mange forbinder med den nærliggende "
		 "landsbyen Malone, vokste faktisk opp i en bondegård i "
		 "Burke. Almanzo var "
		 "<a href='characters.php?character=Laura+Ingalls'>Lauras</a>"
		 " ektemann. Lauras andre bok i serien om "
		 "'Det lille huset på prærien', 'Farmer Boy', "
		 "forteller om Almanzos barndomshistorie. "
		 "Han var sønn av James og Angeline Day Wilder, "
		 "og ble født på familiens bondegård 13. februar 1857. "
		 "I 1871 flyttet familien til Minnesota."
		 "<br />"
		 "<br />"
		 "<b>Geografi</b>"
		 "<br />"
		 "<br />"
		 "Ifølge United States Census Bureau har byen et område "
		 "på 114 km2. Grensa i nord grenser mot Quebec, "
		 "og er en del av den internasjonale grensa mellom "
		 "USA og Canada."
		 "\");"))
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  if(mysql_query(conn, "INSERT IGNORE INTO tbl_town VALUES (2, \"Burr Oak\",\""
		 "Burr Oak er et lite samfunn nord i delstaten Iowa, "
		 "bare noen få kilometer sør for grensen til Minnesota. "
		 "<br /> "
		 "<br /> "
		 "Stedet er kjent for å være et av "
		 "<a href='characters.php?character=Laura+Ingalls'>"
		 "Laura Ingalls Wilders</a> tidligere hjem. "
		 "Hit flyttet familien etter at "
		 "<a href='towns.php?town=Walnut+Grove'>"
		 "Walnut Grove, Minnesota</a>, ble rammet av en "
		 "gresshoppeinvasjon, 2 år på rad. "
		 "<a href='characters.php?character=Grace+Ingalls'>"
		 "Grace Ingalls</a>, Lauras yngste søster, ble født her "
		 "(1877). "
		 "<br /> "
		 "I Masters Hotel, stedet der familien Ingalls bodde, "
		 "er det i dag et museum. Laura skrev aldri om dette "
		 "oppholdet, men boka "
		 "<a href='books.php?book=Old+Town+in+the+Green+Groves'>"
		 "'Old Town in the Green Groves'</a> "
		 "beskriver dette 'manglende året'."
		 "\");"))
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  if(mysql_query(conn, "INSERT IGNORE INTO tbl_town VALUES (3, \"De Smet\", \""
		 "De Smet er en by og fylkeshovedstad i Kingsbury County, "
		 "South Dakota. I år 2000 hadde byen et innbyggertall "
		 "på 1164. Byen er oppkalt etter den belgiske "
		 "jesuittmisjonæren Pierre De Smet. Byen er i dag mest "
		 "kjent for å være et av ungdomshjemmene til "
		 "<a href='characters.php?character=Laura+Ingalls'>"
		 "Laura Ingalls</a>, og fødestedet til Rose Wilder Lane, "
		 "Lauras datter."
		 "<br /> "
		 "<br /> "
		 "<b>Attraksjoner</b> "
		 "<br /> "
		 "<br /> "
		 "<table border='0'> "
		 "<tr> "
		 "<td valign='top' id='main'> "
		 "Hvert år arrangeres det et historespill som handler " 
		 "om Lauras opphold "
		 "i De Smet. Arrangementene er basert på de 4 siste "
		 "bøkene Laura skrev; "
		 "årets arrangement er basert på den siste boka, "
		 "<a href='books.php?book=The+First+Four+Years'>"
		 "'The First Four Years'</a> " 
		 "og arrangeres flere weekender i juli. "
		 "<br /> "
		 "Generelt sett fortelles historien om hvordan "
		 "<a href='characters.php?character=Charles+Ingalls'>"
		 "Charles Ingalls</a> "
		 "og kona "
		 "<a href='characters.php?character=Caroline+Ingalls'>"
		 "Caroline</a> "
		 "kom til De Smet fra "
		 "<a href='towns.php?town=Walnut+Grove'>Walnut Grove</a> "
		 "med hest og vogn av et cast på 30 skuespillere i et "
		 "utendørs teater "
		 "like i nærheten av den gamle gården til familien Ingalls. "
		 "</td>"
		 "<td valign='top' width='480'>"
		 "<a href='javascript:openSurveyor();'> "
		 "<img src='images/lauraingallswilder/surveyors_house.jpg' height='320' width='480' /> "
		 "</a>"
		 "<div id='imgtxt'>"
		 "The Surveyor's* house hvor Laura og " 
		 "familien hennes tilbrakte "
		 "den første vinteren i De Smet. "
		 "I dag ligger dette huset i den nordøstlige delen av "
		 "senteret i De Smet. "
		 "</div>"
		 "</td>"
		 "</tr>"
		 "</table>"
		 "Like i nærheten finner vi både Silver Lake "
		 "og Big Slough som nevnes "
		 "i flere av bøkene hennes. Det som er igjen "
		 "fra pionertiden er "
		 "innlysende; blant annet kirken som Laura "
		 "og familien gikk til. "
		 "<br /> "
		 "I år 1895 dro Laura, Almanzo Wilder og dattera "
		 "Rose Wilder Lane til "
		 "<a href='towns.php?town=Mansfield'>"
		 "Mansfield i delstaten Missouri</a>, "
		 "etter å ha dratt rundt omkring i USA på "
		 "jakt etter et bedre klima. "
		 "Det var i Mansfield hvor Laura skrev sine "
		 "'Little House'-bøker, hvorav "
		 "<a href='books.php?book=The+Long+Winter'>"
		 "'The Long Winter'</a>, "
		 "<a href='books.php?book=Little+Town+on+the+Prairie'>"
		 "Little Town on the Prairie'</a>, "
		 "<a href='books.php?book=These+Happy+Golden+Years'>"
		 "'These Happy Golden Years'</a> og "
		 "<a href='books.php?book=The+First+Four+Years'>"
		 "'The First Four Years'</a> "
		 "handler om oppholdet i De Smet. "
		 "Lauras fortellinger er en viktig "
		 "del av byen, og mange av innbyggerne setter "
		 "gjerne av både tid "
		 "og ressurser til å lære seg mest mulig om henne for å kunne "
		 "hjelpe til med å svare på spørsmål som turistene som besøker "
		 "byen, måtte ha om henne. "
		 "Dessuten er De Smet et populært sted å overnatte "
		 "for de som er på "
		 "vei til Mount Rushmore og Black Hills som ligger litt lenger "
		 "vest i Sør-Dakota. "
		 "<br />"
		 "<br />"
		 "<b>Ordforklaring</b>"
		 "<br /> "
		 "<br /> "
		 "Surveyor = landmåler"
		 "\");"))
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  if(mysql_query(conn, "INSERT IGNORE INTO tbl_town VALUES (4,\"Independence\",\""
		 "Independence er en by og fylkeshovedstad i "
		 "Montgomery County, Kansas. "
		 "I 2000 var det en befolkning på 9846 innbyggere i byen."
		 "<br />"
		 "<br />"
		 "<b>Kort om Independences historie</b> "
		 "<br />"
		 "<br /> "
		 "Byen ble grunnlagt i 1869 langs elvekantene til "
		 "elva Verdigris River. "
		 "En gruppe menn, under ledelse av R. W. Wright "
		 "bestemte seg for "
		 "å grunnlegge en by i den delen av Kansas "
		 "som ikke var bebodd. "
		 "Navnet stammer fra motet som førte til at "
		 "den ble grunnlagt: Independence."
		 "<br /> "
		 "I 1872 kom jernbanen til byen. "
		 "På den tiden var innbyggertallet "
		 "på 3000 innbyggere. "
		 "På den tiden ble et 'land office' bygd, "
		 "hvilket betød at nye innbyggere kunne slå "
		 "seg ned i et større "
		 "område rundt byen (funksjonen til dette "
		 "'land office' var å se "
		 "til at ingen hadde blitt tildelt jorda du ville bygge ut, og "
		 "at du bygde på jord som var eid av den "
		 "amerikanske regjerninga "
		 "(slik at du ikke bygde på 'de innfødte amerikanernes' "
		 "territorium), "
		 "at du var amerikansk statsborger "
		 "og var mer enn 21 år gammel). "
		 "<br /> "
		 "Det var også på denne tiden som "
		 "<a href='characters.php?character=Laura+Ingalls'>Laura"
		 "</a> "
		 "og hennes familie "
		 "<a href='books.php?book=Little+House+on+the+Prairie'>"
		 "slo seg ned i dette området."
		 "</a>"
		 "<br /> "
		 "I 1881 ble det funnet gass, og i 1903 ble det " 
		 "funnet olje i området. "
		 "Dette sørget for at velstanden i byen økte. "
		 "<br />"
		 "<br />"
		 "<b>Noen interessante steder i og rundt Independence</b>"
		 "<br />"
		 "<br />"
		 "**Independence Community College er hjemstedet til William "
		 "Inge Center for the Arts. Her finner man arkiver av bøker "
		 "som er skrevet av skuespillforfatteren William Inge. "
		 "<br />"
		 "**Staten Kansas har utpekt et av barndomshjemmene til "
		 "<a href='characters.php?character=Laura+Ingalls'> " 
		 "Laura Ingalls Wilder</a> "
		 "og resten av Ingalls-familien som et historisk sted som er "
		 "åpen for besøkende. Dette er stedet hvor hendelsene i boka "
		 "<a href='books.php?book=Little+House+on+the+Prairie'>"
		 "'Little House on the Prairie'</a> "
		 "fant sted. Her finner man et tømmerhus som "
		 "er modellert etter "
		 "det originale huset og postkontoret som egentlig ble bygd i "
		 "nærheten av stedet Wayside, Kansas. Her finner man også "
		 "The Sunnyside School, et enroms skolehus "
		 "som senere ble flyttet til dette stedet. "
		 "Mye av landsbygda rundt dette historiske stedet har bevart "
		 "sin åpne og uutbygde natur. "
		 "Stedet ligger ca. 21 km (13 miles)* "
		 "sørvest for Independence. "
		 "<br /> "
		 "**Apekatten Miss Able ble født i Ralph Mitchell Zoo. "
		 "Miss Able "
		 "er kjent for å være et av de to første dyrene "
		 "(det andre dyret var apekatten Miss Baker) som ble tatt med "
		 "opp i verdensrommet og returnert tilbake til Jorda i live. "
		 "Dette skjedde den 28. mai 1959"
		 "\");"))
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  if(mysql_query(conn, "INSERT IGNORE INTO tbl_town VALUES(5, \"Manchester\",\""
		 "Manchester var en liten småby i Kingsbury County, "
		 "i den østlige delen av Sør-Dakota. "
		 "Den 24. juni 2003 ble småbyen ødelagt av en kraftig "
		 "<a href='http://en.wikipedia.org/wiki/Fujita_Scale'>"
		 "F4-tornado</a>, og har siden den gang vært en spøkelsesby. "
		 "<a href='characters.php?character=Grace+Ingalls'>"
		 "Grace Ingalls</a>, "
		 "søstera til "
		 "<a href='characters.php?character=Laura+Ingalls'>"
		 "Laura Ingalls Wilder</a>, "
		 "tilbragte storparten av livet hennes i denne byen. "
		 "Her jobbet hun som lærer i den lokale skolen. "
		 "<a href='characters.php?character=Mary+Ingalls'>"
		 "Mary Ingalls</a> "
		 ", Graces eldste søster bodde noen år sammen med "
		 "Grace i denne byen. "
		 "<br />"
		 "<br />"
		 "<b>Selve tornadoen</b>"
		 "<br />"
		 "<br />"
		 "Den 24. juni 2003 brøt det ut et uvær over den østlige delen "
		 "av Sør-Dakota. Dette uværet formet en kraftig tornado. "
		 "Da Manchester ble truffet av tornadoen, hadde den en styrke "
		 "på F4 på Fujita-skalaen og var mellom "
		 "800 og 1600 meter bred. "
		 "<br />"
		 "<br />"
		 "<a href='http://no.wikipedia.org/wiki/Mesosyklon'>"
		 "Mesosyklonen</a> "
		 "som som var assosiert med tornadoen ble etterfulgt av "
		 "meteorologer og stormjegere. Før tornadoen rammet byen "
		 "hadde man plassert ut et måleinstrument "
		 "som målte værforholdene "
		 "inne i selve tornadoen, en såkalt probe. " 
		 "Ved hjelp av denne proben "
		 "samlet man inn rekordsettende meteorologiske data: "
		 "F.eks. var vindstyrken på 418 km/t, og lufttrykket var "
		 "på ca. 100 millibar i selve øyet av tornadoen. "
		 "<br />"
		 "<br />"
		 "Manchester var en liten og komakt by som var 'omringet' av "
		 "'bondeland' på alle sider. Byen var for det meste bygd rundt "
		 "et veikryss. Tornadoen traff i senteret av dette krysset, og "
		 "var bred og kraftig nok til å jevne alle bygningene "
		 "som tilhørte byen, med jorda. "
		 "Likevel omkom ingen som befant seg i "
		 "denne byen da tornadoen slo til. "
		 "<br />"
		 "<br />"
		 "Selv om byen er forlatt og øde (det er ingen planer om å "
		 "gjenoppbygge byen) er den fortsatt å finne på kartet. "
		 "I dag finner man byen på lista over "
		 "naturkatastrofespøkelsesbyene."
		 "Den 25. juni 2007 ble det satt opp et monument "
		 "til minne om de "
		 "som hadde bodd i småbyen Manchester. "
		 "\");"))
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  if(mysql_query(conn, "INSERT IGNORE INTO tbl_town VALUES(6, \"Mansfield\",\""
		 "Mansfield er en småby i den sørlige delen av Missouri"
		 "<br />"
		 "<br />"
		 "<b>Kjente mennesker</b>"
		 "<br />"
		 "<br />"
		 "I 1894 flyttet "
		 "<a href='characters.php?character=Laura+Ingalls'>"
		 "Laura Ingalls Wilder</a> "
		 ", ektemannen Almanzo Wilder og dattera Rose Wilder Lane fra "
		 "<a href='towns.php?town=De+Smet'>"
		 "De Smet</a> "
		 "til Mansfield. Familien slo seg ned her i "
		 "60 år og stablet etterhvert "
		 "en stor og vellykket fjørfe-, melke-, og fruktgård på beina. "
		 "I dag er deres unike 10-roms gårdshus et nasjonalhistorisk "
		 "landemerke, og 'hjemmet' til "
		 "Laura Ingalls Wilder-Rose Wilder "
		 "Lane Home and Museum, som trekker tusenvis av"
		 "turister til Mansfield hvert eneste år."
		 "\");"))
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  if(mysql_query(conn, "INSERT IGNORE INTO tbl_town VALUES(7, \"Pepin\",\""
		 "Pepin er en liten småby som ligger vest i Wisconsin, "
		 "langs med "
		 "Lake Pepin som er en del av Mississippi-elva. "
		 "Etter folkeopptellinga i år 2000 var det 878 "
		 "innbyggere i Pepin. "
		 "<br />"
		 "<br />"
		 "<b>Historie</b>"
		 "<br />"
		 "<br />"
		 "Midt på 1600-tallet hadde franskmennene "
		 "startet en ekspedisjon til "
		 "Wisconsin via De store innsjøene og St. Lawrence River. "
		 "Kong Ludvig XIII av Frankrike skal ha gitt et "
		 "stort landområde i Upper Mississippi River Valley "
		 "til 2 brødre, "
		 "Etiene Pepin de la Fond og Guillaume dit Tranchemontagne. "
		 "2 av Guillaumes sønner, Pierre Pepin og "
		 "Jean Pepin du Cardonnets, "
		 "begynte etterhvert å utforske og handle i dette området, "
		 "hvilket førte til at etternavnet deres ble forbundet med "
		 "innsjøen, og etterhvert også landsbyen "
		 "og fylket den ligger i. "
		 "<br />"
		 "<br />"
		 "<a href='characters.php?character=Laura+Ingalls'>"
		 "Laura Ingalls Wilder</a> "
		 "ble født i dette området "
		 "(se avsnittet 'Little House Wayside' " 
		 "nedenfor). Hver september feirer "
		 "landsbyen dette med tradisjonell musikk, " 
		 "en 'Laura Look-Alike'-konkurranse, "
		 "en stavekonkurranse og andre hendelser. "
		 "<br /> "
		 "<br /> "
		 "<b>Little House wayside</b>"
		 "<br />"
		 "<br />"
		 "<table border='0'>"
		 "<tr>"
		 "<td valign='top' id='main'>"
		 "Little House Wayside er et 12,000 kvadratmeters område i "
		 "Pepin County, Wisconsin, ca 11 kilometer nordvest for "
		 "byen Pepin, langs med County Highway CC, på stedet der "
		 "<a href='characters.php?character=Laura+Ingalls'>"
		 "Laura Ingalls Wilder</a> "
		 "ble født den 7. februar 1867. "
		 "<br />"
		 "Her finner man en kopi av huset som ble beskrevet i boka "
		 "<a href='books.php?book=Little+House+in+the+Big+Woods'>"
		 "'Little House in the Big Woods'</a>. "
		 "Huset som er umøblert inneholder 2 soverom, et loft "
		 "og litt informasjon om Laura og familien hennes. "
		 "I dag er det åpent landskap som ligger rundt huset, "
		 "selv om det var tett skog der da Laura og familien hennes "
		 "bodde der. Huset (som er vinterstengt "
		 "pga store snømengder) og "
		 "området rundt det vedlikeholdes av "
		 "Laura Ingalls Wilder Memorial Society. "
		 "</td>"
		 "<td valign='top'>"
		 "<a href='javascript:openLittleHouseWayside();'>"
		 "<img src='images/lauraingallswilder/little_house_wayside_replica.jpg' height='320' width='400' /></a>"
		 "<div id='imgtxt'>"
		 "En kopi av huset Laura beskriver i boka"
		 "'Little House in the Big Woods'"
		 "</div>"
		 "</td>"
		 "</tr>"
		 "</table> "
		 "\");"))
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  if(mysql_query(conn, "INSERT IGNORE INTO tbl_town VALUES(8, "
		 "\"Walnut Grove\",\""
		 "Walnut Grove er en småby i fylket Redwood County, sørvest i "
		 "Minnesota. "
		 "Etter folkeopptellingen i 2000 var det "
		 "599 innbyggere i byen. "
		 "Walnut Grove er hjemstedet til Laura Ingalls Wilder Museum, "
		 "dedikert til forfatteren av 'Little House'-bokserien. "
		 "Det var her hvor Lauras eneste lillebror, "
		 "Charles Frederick 'Freddy' Ingalls  "
		 "(1. november 1876 - 27. august 1877 i "
		 "South Troy, Minnesota), "
		 "ble født. "
		 "<br /> "
		 "<br /> "
		 "<b>Historie</b> "
		 "<br /> "
		 "<br /> "
		 "Samfunnet i Walnut Grove oppstod en gang i år 1870, "
		 "og vokste i løpet av 1870-årene. Pionerer slo seg ned "
		 "ved Plum Creek sine bredder. Dette på tross av at en "
		 "gresshoppeinvasjon i 1870 holdt på å ødelegge hele "
		 "samfunnet i den lille byen. Utholdenhet, "
		 "hardt arbeid og en sterk kristen tro var det "
		 "som skulle til for å løfte samfunnet gjennom harde tider. "
		 "I 1873 åpnet Lafayette Bedal, byens første postmann, sitt "
		 "hjem til barn, og tok seg av skoleklasser i stua hans. "
		 "I 1874 ble <i>The Congregational Church</i> bygd i byen. "
		 "I tillegg hadde man åpnet 3 butikker, maskinvare, apotek, "
		 "et hotell, brenselforhandler, trelasthandler, smedbutikk, "
		 "doktorkontor, én saloon, m.m. "
		 "Walnut Grove fikk sitt navn i 1879, 9 år etter at byens historie begynte. "
		 "Navnet fikk byen fra et nydelig skogholt med valnøttrær "
		 "langs med Plum Creek. "
		 "<br /> "
		 "<br />"
		 "<a href='characters.php'>FAMILIEN INGALLS</a> I WALNUT GROVE "
		 "<br /> "
		 "<br /> "
		 "Historien om familien Ingalls' opphold i Walnut Grove "
		 "begynte da "
		 "<a href='characters.php?character=Charles+Ingalls'>Charles</a> "
		 "solgte gården sin i Wisconsin for $1000 "
		 "i oktober 1873 og familien begynte reisen vestover mot Minnesota. "
		 "De gjorde først et stopp i New Ulm, hvor Charles fort ble overbevist "
		 "om at byen var for tett befolket, så de fortsatte ferden vestover "
		 "langs med Cottonwood River. Etterhvert hvilte de på en gård tilhørende "
		 "nordmannen Eleck Nelson, like i nærheten av landsbyen Walnut Grove. "
		 "<a href='characters.php?character=Charles+Ingalls'>Charles</a> "
		 "fikk nå høre om et lite stykke ledig land som var til salgs "
		 "i det som heter North Hero Township. Dette landområdet, inkludert "
		 "denne jordhytta som de ifølge "
		 "<a href='books.php?book=On+the+Banks+of+Plum+Creek'>On the Banks of Plum Creek</a> "
		 "bodde i, kjøpte de fra nordmannen Mr. Hanson. "
		 "Familien bodde der i noen få år. Den 1. november 1875 ble Charles "
		 "Frederick Ingalls født. I august 1876 solgte "
		 "<a href='characters.php?character=Charles+Ingalls'>Charles</a> "
		 "farmen etter et par "
		 "år med gresshoppeinvasjon, og familien flyttet til Burr Oak, Iowa "
		 "for å drive et hotell. "
		 "Dessverre døde lille Charles Frederick på veien til Burr Oak. "
		 "Familien var heller ikke særlig fornøyde med oppholdet sitt i Burr Oak; "
		 "riktignok skal <a href='characters.php?character=Laura+Ingalls'>Laura</a> "
		 "ha sagt at Burr Oak var et fint sted. "
		 "Kort tid etter at Grace ble født den 23. mai 1877, kom familien til "
		 "Walnut Grove for andre gang, bestemt på å prøve lykken på nytt. "
		 "Byen hadde nå vokst. <i>Winona & St. Peter Railroad</i> var bygd ut "
		 "mot Dakota-territoriet. <i>The Congregational Church</i> "
		 "var blitt organisert med hjelp av pastor Edward Alden. "
		 "Charles ble en slags tillitsmann i den nye meigheten. "
		 "Barna fikk nå utdannelse i et eget skolebygg som ble bygd i 1875. "
		 "Præriesamfunnet vokste og ble sakte men sikkkert "
		 "del av den siviliserte vesten. "
		 "Innbyggerne i byen var med andre ord noen hardinger. "
		 "De hadde mot alle odds klart å bekjempe den harde naturen "
		 "og realisert sine drømmer. For Charles og familien Ingalls "
		 "sin del, ledet den amerikanske drømmen dem vestover til "
		 "<a href='towns.php?town=De+Smet'>De Smet.</a>"
		 "<br /> "
		 "<br /> "
		 "<table border='0'>"
		 "<tr>"
		 "<td valign='top'>"
		 "<a href='javascript:openMuseum();'>"
		 "<img src='images/lauraingallswilder/walnutgrovelauramuseum.jpg' width='320' height='250' />"
		 "</a>"
		 "</td>"
		 "</tr>"
		 "<tr>"
		 "<td valign='top'>"
		 "<div id='imgtxt'> "
		 "Inngang til Laura Ingalls Wilder Museum i "
		 "Walnut Grove, Minnesota "
		 "</div> "
		 "</td>"
		 "</tr>"
		 "</table>"
		 "\");"))
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
}

void insertCharacters()
{
  fprintf(stdout, "Inserting characters...\n");
  char errorString[100] = "In function insertCharacters(): MySQL error: ";
  MYSQL *conn;
  char *server = "localhost";
  char *userName = user;
  char *passwd = password;
  char *database = "little_house";
  conn = mysql_init(NULL);
  if(conn == NULL)
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  if(!mysql_real_connect(conn, server, userName, password, database, 0, NULL,0))
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  if(mysql_query(conn, "INSERT IGNORE INTO tbl_characters VALUES(1, \"Caroline Ingalls\", \"Caroline Lake (Quiner) Ingalls ble født den 12 desember 1839 "
	  "i Brookfield, Wisconsin. Hun hadde til sammen 6 søsken, "
	  "brødrene Joseph, Henry og Thomas, og søstrene "
	  "Marth, Jane, Eliza og Martha Morse. "
	  "<br />"
	  "<br />"
	  "Da Caroline var 5 år gammel omkom Carolines far, Henry Quiner "
	  "i en ulykke på Lake Michigan. "
	  "I 1849 giftet moren hennes seg på nytt, "
	  "denne gangen med Frederick Holbrock og fikk ett barn med henne, "
	  "Charlotte 'Lottie' Holbrock. "
	  "Caroline ble glad i den nye stedfaren "
	  "og da Caroline fødte en sønn, "
	  "ble han oppkalt etter stedfaren hennes. "
	  "<br />"
	  "<br />"
	  "Da Caroline var 16 år gammel begynte hun "
	  "å jobbe som lærer, og den "
	  "1. februar 1860 giftet hun seg med "
	  "<a href='characters.php?character=Charles+Ingalls'>Charles Ingalls</a>. "
	  "Sammen fikk de 5 barn: "
	  "<a href='characters.php?character=Mary+Ingalls'>Mary Amelia Ingalls</a>, "
	  "<a href='characters.php?character=Laura+Ingalls'>Laura Elizabeth Ingalls Wilder</a>, "
	  "<a href='characters.php?character=Carrie+Ingalls'>Caroline 'Carrie' Celestia Ingalls Swanzey</a>, "
	  "Charles Frederick 'Freddie' Ingalls og "
	  "<a href='charaters.php?character=Grace+Ingalls'>Grace Pear Ingalls Dow</a>. "
	  "Familien bodde i Wisconsin, Kansas, "
	  "Minnesota og Dakota-territoriet. "
	  "Caroline døde den 20. april 1924, 84 år gammel. Hun ligger i dag "
	  "begravet i De Smet Cementry sammen med resten av familien, "
	  "med unntak av Laura. "
	  "<br />"
	  "<br />"
	  "<b>I media</b>"
	  "<br />"
	  "<br />"
	  "<ul>"
	  "  <li>Karen Grassle spilte rollen som "
	  "    Caroline Lake Quiner Ingalls "
	  "    i TV-serien 'Det lille huset på prærien' sesong 1-8 "
	  "    (1974-1982), "
	  "    'Little House Years' (1979) "
	  "    og i den etterfølgende filmen "
	  "    'Little House: The Last Farewell' "
	  "    (sesong 10, 1984) "
	  "  <li>Katy Kurtzman spilte rollen som den unge Caroline Ingalls i "
	  "    en episode som heter 'I Remember, I Remember' i sesong 4 i "
	  "    TV-serien 'Det lille huset på prærien' (1979) "
	  "  <li>Lindsay Crouse spilte rollen som "
	  "    Caroline Lake Quiner Ingalls "
	  "    i TV-filmen 'Bortenfor prærien: den sanne historien om "
	  "    Laura Ingalls Wilder' (2000) "
	  "  <li>Erin Cottrell spilte rollen som " 
	  "    Caroline Lake Quiner Ingalls "
	  "    i ABC sin miniserie om 'Det lille huset på prærien' (2005) "
	  "</ul>\");"))
	{
	  exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if(mysql_query(conn, "INSERT IGNORE INTO tbl_characters VALUES(2,\"Carrie Ingalls\", \"<table border='0'>"
		       "<tr>"
		       "<td valign='top' id='main'> "
		       "Caroline Celestia 'Carrie' Ingalls Swanzey "
		       "er en av Lauras" 
		       "lillesøstere, og det tredje av i alt 5 barn. "
		       "Hun ble født den 3. august 1871 ikke langt fra "
		       "Independence, Kansas. "
		       "<br />"
		       "<br />"
		       "Ifølge storesøstera Laura, " 
		       "var det Carrie som hadde slitt mest med "
		       "tanke på helsa i løpet av- og etter "
		       "<a href='books.php?book=The+Long+Winter'>'den lange vinteren'</a>. "
		       "I kapittel 12 i boka "
		       "<a href='books.php?book=Little+Town+on+the+Prairie'>'Little Town on the Prairie'</a> "
		       "sier Laura at Carrie ikke kom seg etter den lange vinteren "
		       "som hun skulle. Hun var ikke konstant syk, "
		       "men hun hadde ikke "
		       "den samme robuste helsa som de andre i familien hadde. "
		       "Laura fortalte også at hun om morgenene f. eks. kunne huske "
		       "leksene i staving, "
		       "</td>"
		       "<td valign='top'>"
		       "<a href='javascript:openWin();'>"
		       "<img src='images/lauraingallswilder/carrie_1.jpg' width='267' height='229' />"
		       "</a>"
		       "<div id='imgtxt'>"
		       "Caroline Celestia 'Carrie' Ingalls Swanzey "
		       "</div>"
		       "</td>"
		       "</tr>"
		       "</table>"
		       "men da læreren, Eliza Jane Wilder, " 
		       "skulle kalle henne frem til tavla for å stave det hun lærte, "
		       "hadde hun som regel så vondt i hodet at hun ikke klarte "
		       "å stave det hun skulle. Dette førte til at hun ble "
		       "unødig hardt straffet ved at hun måtte skrive 3 ord "
		       "korrekt 50 ganger hver, noe som startet en 'krig' mellom "
		       "Laura, Carrie og lærerinna (Laura og Carrie "
			"en dag ble sendt hjem fra skolen for resten av den dagen, "
			"og når Laura og Carrie møter på skolen dagen etter, "
			"begynner en periode på flere uker med bråk, spetakkel og uorden "
			"mellom alle elevene og læreren). "
		       "<br />"
		       "<br />"
		       "Etter å ha tilbragt den siste delen av tenårene til å reise rundt "
		       "for å prøve å finne et mer komfortabelt klima "
		       "(hun kom tilbake til De Smet hver gang), begynte hun å "
		       "jobbe for avisen De Smet News som en trykker før hun etterhvert "
		       "begynte å jobbe for andre aviser over hele delstaten. Da Carrie "
		       "var 41 år gammel, i august 1912 giftet hun seg "
		       "med enkemann David N. Swanzey, "
		       "best kjent for å ta del i navngivningen av Mount Rushmore. "
		       "De fikk ingen barn sammen; David hadde 2 fra hans tidligere "
		       "ekteskap. "
		       "Den 8. april 1938 døde ektemannen hennes. "
		       "<br />"
		       "<br />"
		       "Etter at foreldrene "
		       "<a href='characters.php?character=Charles+Ingalls'>Charles</a>, "
		       "<a href='characters.php?character=Caroline+Ingalls'>Caroline</a> "
		       "og søstera <a href='characters.php?character=Grace+Ingalls'>Grace</a> "
		       "døde, var det Carrie som tok seg av "
		       "<a href='characters.php?character=Mary+Ingalls'>Mary</a>. "
		       "Da Laura begynte å dele på barndomsminnene hennes i "
		       "'Little House'- "
		       "bokserien, var Carrie en entusiastisk medhjelper. "
		       "Hun hjalp til med å dele minnene med Laura, og hun komplimenterte "
		       "Laura da Laura skulle utgi den siste boka, "
		       "<a href='books.php?book=These+Happy+Golden+Years'>'These Happy Golden Years'</a>. "
		       "<br />"
		       "Carrie døde den 2. juni 1946, 75 år gammel i Keystone, Sør-Dakota "
		       "av en komplisert form for diabetes, "
		       "en sykdom som både "
		       "<a href='characters.php?character=Laura+Ingalls'>Laura</a> og "
		       "<a href='characters.php?character=Grace+Ingalls'>Grace</a>døde av. "
		       "Hun ligger begravet i De Smet Cementry. "
		       "<br />"
		       "<br />"
		       "<b>I media</b>"
		       "<br />"
		       "<br />"
		       "<ul>"
		       "<li>I sesong 1-8 (1974-1982) TV-serien "
		       "'Det lille huset på prærien' og i filmen "
		       "'Little House Years' (1979) "
		       "spilte de identiske tvillingene "
		       "Lindsay og Sidney Greenbush rollen "
		       "som Carrie Celestia Ingalls Swanzey. "
		       "<li>Haley McCormick spilte rollen som "
		       "Carrie Celestia Ingalls Swanzey "
		       "i TV-filmen 'Bortenfor prærien: "
	      "Laura Ingalls Wilders sanne historie' (2000). "
		       "</ul>\");"))
	{
	  exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if(mysql_query(conn, "INSERT IGNORE INTO tbl_characters VALUES(3, \"Charles Ingalls\", \"Charles Philip Ingalls ble født den 10. januar 1836 "
	  "i Cuba, New York. Han var det andre av i alt 9 barn av "
	  "Landsford Whiting Ingalls og Laura Louise Colby Ingalls, som "
	  "Laura i sin første bok, "
	  "<a href='books.php?book=Little+House+in+the+Big+Woods'>'Little House in the Big Woods' (Det lille huset i den store skogen)</a> "
	  "kalte for 'Grandpa' og 'Grandma'. I 1840 flyttet familien fra New "
	  "York til byen Elgin i delstaten Illiois, før de flyttet til "
	  "Wisconsin. Der møtte han på "
	  "<a href='/caroline_ingalls.html'>Caroline Ingalls</a> "
	  "som han giftet seg med den 1. februar 1860. "
	  "Sammen fikk de 5 barn: "
	  "<a href='characters.php?character=Mary+Ingalls'>Mary Amelia Ingalls</a>, "
	  "<a href='characters.php?character=Laura+Ingalls'>Laura Elizabeth Ingalls Wilder</a>, "
	  "<a href='charaters.php?character=Carrie+Ingalls'>Caroline 'Carrie' Celestia Ingalls Swanzey</a>, "
	  "Charles Frederick 'Freddie' Ingalls og "
	  "<a href='characters.php?character=Grace+Ingalls'>Grace Pearl Ingalls Dow</a> "
	  "<br />"
	  "<br />"
	  "I Lauras bøker beskrives Charles som en mann med mye "
	  "vandrelyst; han likte ikke å oppholde seg på 'tett' "
	  "befolkede steder. Først tok han med seg Caroline til "
	  "Pepin, Wisconsin (huset ble bygd ca 14 km fra Pepins). "
	  "Etter at Mary og Laura ble født (Laura var ett år gammel), " 
	  "flyttet de til Kansas hvor Carrie "
	  "ble født. Da de etter et år i Kansas, og bare noen uker etter "
	  "Carries fødsel fikk vite at de bodde på indiansk territorium, "
	  "flyttet de tilbake til Wisconsin, for så å flytte til "
	  "Walnut Grove, Minnesota. Deretter tilbragte de et år i Iowa "
	  "før de flyttet tilbake til Walnut Grove, for deretter å flytte "
	  "til De Smet i det som den gang het Dakota-territoriet "
	  "(De Smet ligger i dag i Sør-Dakota) hvor han slo seg ned. "
	  "Da hadde han lovet Caroline at de ikke skulle flytte mer, "
	  "fordi Caroline blant annet var bekymret for barnas utdannelse. "
	  "Etter at de flyttet til De Smet holdt Charles på med gårdsbruk "
	  "i noen år, men etter at han hadde oppfylt kravene til  "
	  "<a href='http://en.wikipedia.org/wiki/Homestead_Act'>'Homestead Act'</a>, "
	  "solgte han gården og bygde et hjem på Third Street i De Smet. "
	  "Der bodde han resten av livet. "
	  "Den 2. juni 1902 døde Charles av hjerteproblemer. "
	  "Han ble begravd i De Smet Cementry i en alder av 66 år. "
	  "<br />"
	  "<br />"
	  "<b>I media</b>"
	  "<br />"
	  "<br />"
	  "<ul>"
	   " <li>Michael Landon spilte rollen som Charles Philip Ingalls " 
	    "  i TV-serien 'Det lille huset på prærien' i sesongene 1-8 "
	     " (1974- 1982) og 'Little House Years' (1979). "
	     " Han hadde også en gjesterolle som Charles i sesong 9 og 2 "
	     " av de etterfølgende filmene "
	      "('Little House: Look Back to Yesterday' (1983) og "
	      "'Little House: The Last Farewell' (1984)) "
	    "<li>Mathew Laborteaux spilte rollen som den unge Charles "
	    "  Philip Ingalls i episoden "
	    "  'A Journey in the Spring' i sesong 3 "
	    "  (1976) og 'I Remember, I Remember' i sesong 4 av " 
	    "  'Det lille huset på prærien' (1977) "
	    "<li>Richard Thomas hadde rollen som Charles Philip Ingalls "
	    "  i TV-filmene 'Bortenfor prærien: den sanne historien om "
	    "  Laura Ingalls Wilder' (2000 og 2002) "
	    "<li>Cameron Bancroft hadde rollen som Charles Philip Ingalls "
	    "  ABC sin miniserie om 'Det lille huset på prærien' (2005) "
	  "</ul>\");"))
	{
	  exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if(mysql_query(conn, "INSERT IGNORE INTO tbl_characters VALUES(4, \"Grace Ingalls\", \"<table border='0'>"
	    "<tr>"
	      "<td valign='top' id='main'>"
		"Grace Pearl Ingalls ble født den 23. mai 1877 i Burr "
		"Oak, Iowa. "
		"Hun var den yngste av Lauras 5 søsken. "
		"Da "
		"<a href='characters.php?character=Caroline+Ingalls'>Caroline Ingalls</a> "
		"hadde født Grace, sa hun at ''Grace' betyr i Guds nåde', " 
		"eller 'The spirit of God in someone's heart'. "
		"<br />"
		"<br />"
		"I voksen alder jobbet Grace som lærer i en skole i byen "
		"Manchester, Sør-Dakota. Da hun var 24 år gammel, "
		"den 16. oktober 1901 "
		"giftet hun seg med Nathan William Dow. " 
		"Paret fikk ingen barn sammen. "
		"I tillegg til å være ei gårdskvinne jobbet " 
		"Grace til dels som "
		"journalist for flere aviser," 
		"og da begge foreldrene døde, tok "
		"hun seg av hennes storesøster Mary som var blind. "
		"Den 10. november 1941 sovnet Grace stille inn i "
		"en alder av 64 år. "
		"Hun døde av en komplisert form for diabetes, i likhet med "
		"både "
		"<a href='characters.php?character=Laura+Ingalls'>Laura Ingalls Wilder</a> og "
		"<a href='characters.php?character=Carrie+Ingalls'>Carrie Ingalls</a>. "
		"Hun var den første av Ingalls-søskenene som "
		"døde av sykdommen. "
		"Hun ligger begravet i De Smet Cementry."
	      "</td>"
	      "<td valign='top'>"
		"<a href='javascript:openWin();'>"
		"<img src='images/lauraingallswilder/grace_1.jpg' height='329' width='245'></a>"
		"<div id='imgtxt'>"
		"  Grace Pearl Ingalls som en baby"
		"</div>"
	      "</td>"
	    "</tr>"
	  "</table>"
	  "<br />"
	  "<b>I mediene</b>"
	  "<br />"
	  "<br />"
	  "<ul>"
	  "  <li> I TV-serien 'Det lille huset på prærien' "
	  "    ble Grace Pearl Ingalls Dow "
	  "    spilt av Wendi og Brenda Turnbaugh fra sesong 5 til 8 "
	  "    (1978-1982) "
	  "    og i filmen 'Little House Years' (1979). "
	  "  <li>"
	  "    Courtnie Bull og Lyndee Probst spilte rollen som "
	  "    Grace Pearl Ingalls Dow i den første delen av TV-filmen "
	  "    'Bortenfor prærien: Laura Ingalls Wilders 'sanne' historie' " 
	  "    (2000) "
	  "</ul>\");"))
	{
	  exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if(mysql_query(conn, "INSERT IGNORE INTO tbl_characters VALUES(5, \"Laura Ingalls\", \"Laura Ingalls Wilder, eller Laura Elizabeth Ingalls "
	    "(hennes opprinnelige navn) ble født den 7. februar "
	    "1867 i et tømmerhus i skogene utenfor Pepin, Wisconsin "
	    "av Caroline ('Ma') Ingalls og Charles ('Pa') Ingalls. "
	    "Hun var det andre barnet av i alt 5; hun hadde "
	    "4 søsken: storesøstera Mary Amelia, lillesøsterene Carrie Celestia " 
	    "og Grace Pearl og en lillebror som het Charles Frederick "
	    "(som bare ble 9 måneder gammel). "
	    "<br />"
	    "<br />"
	    "<b>Prærien og Det Indianske Territoriet</b>"
	    "<br />"
	    "<br />"
	    "Da Laura bare var 1 år gammel bestemte Lauras 'Pa', Charles "
	    "seg for å selge gården de bodde på for å dra sørvestover til "
	    "Kansas og det indianske territoriet hvor det som skjedde i "
	    "boka om <a href='books.php?book=Little+House+on+the+Prairie'>'Little House on the Prairie'</a> "
	    "fant sted. Dette er stedet der Charles og Caroline fikk sitt 3. "
	    "barn, Caroline 'Carrie' Celestia. Problemet var at landet "
	    "de slo seg ned i, ikke var åpnet for innflytting ennå, "
	    "og ca 1,5 år etter at de kom, måtte de flytte. "
	    "I boka utga hun seg for å være 6-7 år gammel, dette var "
	    "for å beholde kronologien i bokserien, i og med at 'Little "
	    "House on the Prairie' var den andre bok i serien. "
	    "<br />"
	    "<br />"
	    "<table border='0'>"
	    "  <tr>"
		"<td valign='top' id='main'>"
		 " <b>'Det vesle huset i den store skogen'</b>"
		  "<br />"
		 " <br />"
		 " De flyttet da tilbake til Pepin i "
		 " Wisconsin som var stedet "
		 " for handlingen i Lauras første bok, "
		 " <a href='books.php?book=Little+House+in+the+Big+Woods'>Little House in the Big Woods</a> skjedde. "
		 " Da hendelsene i denne boka fant sted var hun 3 år gammel, "
		 " og ikke 6 år som det står i boka. "
		 " I tillegg til det som skjedde i boka, begynte Laura på " 
		 " skole - hun var Barry Corner School sin yngste elev; "
		 " bare 4 år gammel. "
		"</td>"
		"<td valign='top'>"
		"  <a href='javascript:openLittleHouseWayside();'>"
		"  <img src='images/lauraingallswilder/little_house_wayside_replica.jpg' height='280' width='440'></a>"
		"  <div id='imgtxt'>"
		"    En eksakt kopi av Laura Ingalls Wilders hjem nær " 
		"    Pepin, Wisconsin, stedet der handlingen i "
		"    'Little House in the Big Woods' fant sted. "
		"    Det som en gang i tiden var en tett skog er "
		"    nå blitt til et åpent landskap. "
		"  </div>"
		"</td>"
	     " </tr>"
	    "</table>"
	    "<br />"
	    "<br />"
	    "<table border='0' width='760'>"
	    "  <tr>"
	    "	<td valign='top'>"
	    "	  <a href='javascript:openCarrieMaryLaura();'>"
		"  <img src='images/lauraingallswilder/carrie_mary_laura_1870_tallet.jpg'></a>"
		"  <div id='imgtxt'>"
		"    Fra venstre: Carrie, Mary og Laura. "
		"    Bildet er tatt en gang "
		"    på 1870-tallet. "
		"  </div>"
		"</td>"
		"<td valign='top' id='main'>"
		"  <b>Minnesota og Burr Oak, Iowa</b>"
		"  <br />"
		"  <br />"
		"  På Lauras syvende fødselsdag krysset familien Lake Pepin, "
		"  en del av Mississippi-elva for andre gang. Charles syntes "
		"  det var kommet for mange innflyttere til "
		"  'den store skogen'; "
		"  han likte ikke tanken på at ville dyr "
		"  skulle leve i konstant "
		"  frykt for mennesker; dessuten var det ikke trygt å jakte " 
		"  med for mange folk i området, så "
		"  Charles hadde på nytt bestemt "
		"  seg for å selge gården og dra vestover. " 
		"  Denne gangen endte de "
		"  opp langs med "
		"  <a href='books.php?book=On+the+Banks+of+Plum+Creek'>Plum Creek</a> "
		"  utenfor den sannsynligvis mest kjente byen de bodde i "
		"  (pga TV-serien fra 1974-83), Walnut Grove, Minnesota. "
		"  Først bodde de i ei jordhytte, så bygde Charles et trehus "
		"  oppe på prærien. Laura begynte på skolen igjen og fikk "
		"  nye venner og 'fiender' som Nellie Owens "
		"  (i boka On the Banks of Plum Creek het hun " 
		"  'Nellie Oleson'). "
		"  Oppholdet deres i Minnesota bød på mange utfordringer. "
		"  Plankene Charles brukte for å bygge huset var "
		"  kjøpt på kreditt "
		"  og skulle nedbetales når innhøstingen "
		"  av avlinger var ferdig. "
		"  Da kom det en 'glittering cloud' av gresshoppere "
		"  som spiste opp all avlingen. "
		"  Dette førte til at Charles måtte spassere "
		"  opptil 300 miles (ca 450 kilometer) for å finne en jobb "
		"  som han kunne bruke til å nedbetale det han skyldte. "
		"</td>"
	      "</tr>"
	    "</table>"
	    "Det samme skjedde året etter. I tillegg fikk familien "
	    "for første gang smake på hva en vinter var ute på prærien; "
	    "en dag var Charles borte i 4 hele dager og kom ikke til rette "
	    "før på julaften (4 dager tidligere tok han seg en tur til byen "
	    "og på veien hjem ble han tatt av en såkalt blizzard, "
	    "en kraftig snøstorm). "
	    "<!--</tabble>--> "
	    "Noen måneder etter kom Lauras lillebror " 
	    "Charles Frederick til verden, "
	    "og da gresshopperne kom tilbake for 3. gang fikk Charles "
	    "nok og flyttet familen først til South Troy, Minnesota hvor "
	    "noen slektninger av Laura bodde. "
	    "Dessverre døde Lauras lillebror "
	    "der etter 9 sykdomsfulle måneder. Deretter tok Charles seg "
	    "en jobb på et hotell i Burr Oak, Iowa og ble der i ett år. "
	    "Der ble Lauras yngste søster Grace Pearl født. Da familien "
	    "hadde bodd i Iowa i ett år, "
	    "flyttet de tilbake til Walnut Grove. "
	    "Laura tok seg jobb som kelner i et nytt hotell i Walnut Grove, "
	    "og da hun begynte på skolen der igjen, "
	    "møtte hun for første gang "
	    "på ei som het Genevieve Masters, og som i Lauras siste 2 bøker "
	    "også gikk under navnet 'Nellie Oleson'. "
	    "I tillegg ble Mary syk av skarlagensfeber ('scarlet fever') " 
	    "og etterhvert også helt blind. "
	    "<br />"
	    "<br />"
	    "<table border='0'>"
	    "  <tr>"
		"<td valign='top' id='main'>"
		"  <b>Dakota-territoriet</b> "
		"  <br />"
		"  <br />"
	    "Kort tid etter begynte en periode av Lauras liv som hun " 
	    "beskrev i <a href='books.php?book=By+the+Shores+of+Silver+Lake'>'By the Shores of Silver Lake'</a>. "
	    "Denne perioden fant sted mellom 1879 og 1880. "
	    "Charles ble tilbydt en jobb for jernbanen av Charles' søster, "
	    "som han takket ja til. Dermed satte han ut på en reise "
	    "til det sørøstlige Dakota-territoriet (i dag kjent som "
	    "Nord- og Sør-Dakota) hvor han var ansvarlig for å betale ut "
	    "lønnen til de som bygde jernbanen. Charles dro ut sent på "
	    "våren, men fordi Mary ikke var blitt ordentlig frisk ennå, "
	    "kom resten av familien først ut på høsten. Da vinteren kom "
	    "og jernbanebyggerne var ferdige med sin jobb, flyttet familien "
	    "til bygningsinspektørens hus og overvintret der. "
	    "Stedet de nå var kommet til, ble hetende De Smet, og da våren "
	    "kom, skaffet Charles seg først en tomt i den nye byen som de "
	    "først bodde i, deretter et gårdsbruk ca 1,6 km sør for byen. "
		"  Dette skjedde våren 1880. "
		"</td>"
		"<td valign='top'>"
		"  <a href='javascript:openFamilyIngalls();'>"
		"  <img src='images/lauraingallswilder/familien_ingalls_1894.jpg'></a>"
		"  <div id='imgtxt'>"
		"    Familien Ingalls i 1894. " 
		"    Foran (fra venstre): Charles ('Pa'), Caroline ('Ma') " 
		"    og Mary. Bak (fra venstre): Carrie, Laura og Grace "
		"    </div>"
		"</td>"
	      "</tr>"
	    "</table>"
	    "<br />"
	    "<br />"
	    "Den neste perioden i Lauras liv beskrev hun i boka "
	    "<a href='books.php?book=The+Long+Winter'>'The Long Winter'</a>. "
	    "Dette var en av de aller verste vinterne i "
	    "Dakota-områdets historie. "
	    "Vinteren varte fra oktober til april! "
	    "<br />"
	    "<br />"
	    "Den neste delen av livet hennes er godt dokumentert. I boka "
	    "<a href='books.php?book=Little+Town+on+the+Prairie'>'Little Town on the Prairie'</a> "
	    "følger vi Laura og familien hennes fra våren 1881 til julaften i "
	    "1882. Her tar Laura seg jobb som sydame i byen De Smet, "
	    "Laura og Carrie begynner for alvor på skolen i De Smet og "
	    "blir kjent med mange venninner og fiender (blant annet "
	    "Genevieve Masters, og som i Lauras siste 2 bøker "
	    "også gikk under navnet 'Nellie Oleson'. "
	    "I tillegg ble Mary syk av skarlagensfeber ('scarlet fever') og "
	    "etterhvert også helt blind. "
	    "<br />"
	    "<br />"
	    "Kort tid etter begynte en periode av Lauras liv som hun "
	    "beskrev i <a href='books.php?book=By+the+Shores+of+Silver+Lake'>'By the Shores of Silver Lake'</a>. "
	    "Denne perioden fant sted mellom 1879 og 1880. "
	    "Charles ble tilbydt en jobb for jernbanen av Charles' søster, "
	    "som han takket ja til. Dermed satte han ut på en reise "
	    "til det sørøstlige Dakota-territoriet (i dag kjent som "
	    "Nord- og Sør-Dakota) hvor han var ansvarlig for å betale ut "
	    "lønnen til de som bygde jernbanen. Charles dro ut sent på "
	    "våren, men fordi Mary ikke var blitt ordentlig frisk ennå, "
	    "kom resten av familien først ut på høsten. Da vinteren kom "
	    "og jernbanebyggerne var ferdige med sin jobb, flyttet familien "
	    "til bygningsinspektørens hus og overvintret der. "
	    "Stedet de nå var kommet til, ble hetende De Smet, og da våren "
	    "kom, skaffet Charles seg først en tomt i den nye byen som de "
	    "først bodde i, deretter et gårdsbruk ca 1,6 km sør for byen. "
	    "Dette skjedde våren 1880. "
	    "<br />"
	    "<br />"
	    "Den neste perioden i Lauras liv beskrev hun i boka "
	    "<a href='books.php?book=The+Long+Winter'>'The Long Winter'</a>. "
	    "Dette var en av de aller verste vinterne i Dakota-områdets historie. "
	    "Vinteren varte fra oktober til april, med snøstormer som "
	    "var så kraftige at skolen måtte holdes stengt store "
	    "deler av vinteren. De dagene det var skole møter Laura for "
	    "første gang på Minnie Johnson og Mary Power, som hun også "
	    "møter i Lauras 2 neste bøker. "
	    "<br />"
	    "<br />"
	    "Den neste delen av livet hennes er godt dokumentert. I boka "
	    "<a href='books.php?book=Little+Town+on+the+Prairie'>'Little Town on the Prairie'</a> "
	    "følger vi Laura og familien hennes  "
	    "fra våren 1881 til julaften i "
	    "1882. Her tar Laura seg jobb som sydame i byen De Smet, "
	    "Laura og Carrie begynner for alvor på skolen i De Smet og "
	    "blir blant andre kjent med gode venninner som "
	    "Minnie Johnsen, Mary Power og Ida Brown, og uvenner som "
	    "Miss Wilder (Lauras lærerinne), og Genevieve Masters "
	    "som hun kjente fra hennes siste opphold i Walnut Grove. "
	    "Dessuten møter Laura på hennes kommende ektemann Almanzo Wilder. "
	    "<br />"
	    "<br />"
	    "I Lauras 8. bok (som var den siste som ble "
	    "utgitt før hennes død), "
	    "<a href='books.php?book=These+Happy+Golden+Years'>'These Happy Golden Years'</a> "
	    "begynner Laura å jobbe som lærer. "
	    "Hun var alt annet enn komfortabel "
	    "med det, fordi hun ikke likte å være sammen med fremmede og "
	    "fordi det var den første perioden i livet hennes som hun bodde "
	    "borte fra foreldrene sine. Dette skjer samtidig som hennes enge "
	    "skolegang fortsetter i De Smet. Almanzo forelsker seg i Laura "
	    "og frakter henne frem og tilbake mellom De Smet og skolene  "
	    "hun jobber i (på den tiden jobbet man som regel bare i ca 2-3 "
	    "måneder om gangen på det meste og for Lauras del var det flere "
	    "måneder mellom hver gang hun jobbet som lærer) uansett hvor "
	    "langt og hvor kaldt det var. Handlingen i boka baserer seg på "
	    "en periode på 3 år og avsluttes den 25. august 1885 da Laura "
	    "og Almanzo blir gift. "
	    "<br />"
	    "<br />"
	    "<table border='0'>"
	    "  <tr>"
		"<td valign='top'>"
		"  <a href='javascript:openLauraAlmanzo();'>"
		"  <img src='images/lauraingallswilder/laura_and_almonzo.jpg'></a>"
		"  <div id='imgtxt'>"
		"    Laura og Almanzo kort tid etter bryllupet. "
		"  </div>"
		"</td>"
		"<td valign='top' id='main'>"
		"  <b>Ekteskap og årene etter</b> "
		"  <br />"
		"  <br />"
		"  Ekteskapet mellom Laura og Almanzo bød på " 
		"  store utfordringer. "
		"  De fikk ei datter, Rose Wilder Lane i 1886. " 
		"  Feilslåtte avlinger, "
		"  øknomisk depresjon (eller 'panikk' som de kalte det), " 
		"  tornadoer "
		"  og en brann i huset deres var noen av problemene " 
		"  de hadde. "
		"  Almanzo ble delvis paralysert " 
		"  da han fikk en alvorlig form "
		"  for difteri, og i tillegg, "
		"  i august 1889 fikk Laura en sønn. "
		"  'Han ser ut som Manly,' sa Grace. (Manly var kallenavnet "
		"  Lura brukte om Almanzo). "
		"  Kort tid etter døde den nyfødte sønnen. "
		"  Disse prøvelsene står beskrevet i den siste boka " 
		"  i 'Little House'-serien, "
		"  <a href='books.php?book=The+First+Four+Years'>'The First Four Yers'</a>. " 
		"  Dette er ei bok Laura skrev et utkast til, "
		"  men som hun sannsynligvis "
		"  mistet interessen av å gjøre ferdig da "
		"  Almanzo døde i 1947. "
		"  Boka er blitt utgitt slik Laura skrev den i 1971, " 
		"  etter dattera Rose "
		"  Wilder Lanes død i 1968. "
		"  <br />"
		"  <br />"
		"  Nå begynte en periode av livet hvor Laura, " 
		"  Almanzo og Rose "
		"  flyttet rundt omkring i USA på bare noen få år. " 
		"  I 1890 dro "
		"  de østover til Spring Walley, Minnesota. "
		"  Der bodde de sammen med "
		"  Almanzos foreldre og slektninger. " 
		"  De bodde der i over et år. "
		"  Peter, Almanzos fetter flyttet da ned til Flordia. "
		"</td>"
	      "</tr>"
	    "</table>"
	    "Laura og Almanzo gjorde det samme fordi klimaet der "
	    "var bedre for helsa til Almanzo. "
	    "De ble ikke værende der så lenge; "
	    "naboene så på Laura som en 'up-North gal' og heller ikke "
	    "Peters kone likte henne så godt. Laura savnet prærien, og "
	    "i 1892 flyttet de tilbake til De Smet. Der tok Laura seg "
	    "en jobb som sydame mens Almanzo som en løsarbeider. "
	    "Dette gjorde de i håp om at de på nytt skulle kunne starte en "
	    "gård. "
	    "<br />"
	    "<br />"
	    "<b>Mansfield, Missoury</b>"
	    "<br />"
	    "<br />"
	    "I 1894 flyttet familien en siste gang. Denne gangen flyttet de "
	    "til Mansfield i Missoury, til en gård som var "
	    "0,2 kvadratkilometer "
	    "stort som de kalte 'Rocky Ridge Farm' " 
	    "det var mye stein på tomta. "
	    "20 år senere hadde gården vokst til å være 0,8 kvadratkilometer "
	    "stor melke- og fruktgård. "
	    "Et tømmerhus som de bygde ble etterhvert "
	    "erstattet av et 10-roms gårdshus og andre bygninger."
	    "Etterhvert som årene gikk begynte Laura å skrive korte innlegg "
	    "til et magasin som het Ruralist. "
	    "I 1916 var Laura med på å opprette ei "
	    "gruppe som het 'The Athenians'. Formålet med gruppa var å " 
	    "utvikle vennskap og erfaringer innenfor ting som "
	    "f. eks utdannelse. "
	    "Målet var å få bygget et fylkesbibliotek. Laura bidro med å "
	    "skrive en klubbsang og reportasjer. En gang, kjøpte Rose "
	    "en bil i gave til Papa (Almanzo) og Mama Bess (Laura). "
	    "Det var en 1923-modell Buick. I 1925 la familien ut på en "
	    "biltur til California. Dette skulle vekke Lauras skrivevilje "
	    "til live igjen. Laura hadde sluttet å skrive til the Ruralist, "
	    "og da de kom hjem fra California hjalp Rose Laura med å skrive "
	    "2 artikler til The Country Gentleman. Rose var ivirg etter å "
	    "lære Laura å skrive sånne artikler til høytbetalende magasiner "
	    "fordi Rose mente at dette ville være Lauras sjanse til å tjene "
	    "store penger. Dette varte frem til 1926 da Rose begynte med "
	    "språkstudier og flyttet hjemmefra til Paris og Tiranna, "
	    "hovedstaden i Albania. "
	    "<br />"
	    "<br />"
	    "I 1928 kom Rose tilbake. Nå innså hun at gårdsarbeidet for "
	    "foreldrene hennes ble for tøft for dem og at det var på tide "
	    "at de trakk seg tilbake. Det året bygde Rose et helt nytt "
	    "hus som sto ferdig i desember 1928. Kort tid etter at "
	    "de flyttet inn i det nye huset betalte Laura og Almanzo "
	    "det siste de skyldte penger til. 'Nå er dette stedet vårt,' "
	    "erklærte de. Rose holdt til i deres gamle hus. Da tenkte Laura "
	    "på å skrive en selvbiografi. Hun tenkte over barndommen hun "
	    "hadde i skogen på prærien med Charles, Caroline og søstrene "
	    "Mary, Carrie og Grace. Det hun opplevde kunne ikke oppleves "
	    "på den tiden de nå levde i - på 50 år var kolonigrensene borte. "
	    "Laura tenkte at opplevelsene hennes var "
	    "for gode til å bli borte "
	    "og sa at 'Det var historier som måtte fortelles.' Dette førte "
	    "til at hun begynte å skrive ned historien hennes i ei blålinjet "
	    "skrivebok. Manuskriptet fikk navnet "
	    "'Pioneer Girl' - 'Pionerjente'. "
	    "Hun ga så manuset til Rose og ba henne om å skrive inn manuset "
	    "med en skrivemaskin. Da det var gjort sendte Rose teksten til "
	    "til George Bye, Roses agent som tok seg av Roses verker i "
	    "håp om å få solgt det til et forlag. Selv om alle var enige i "
	    "at det var en interessant amerikansk historie, "
	    "var det ingen som "
	    "ville kjøpe det. Da tok Rose med seg manuskriptet til New York "
	    "for å prøve å selge det til noen magasiner, "
	    "men fikk på nytt avslag. "
	    "<br />"
	    "Noen venner i San Fransisco hørte om manuset. De jobbet med å "
	    "illustrere barnebøker, og tenkte at Pioneer Girl ville vært en "
	    "god barnebok. Igjen ble manuset sendt fra forlag til forlag "
	    "til det til slutt endte opp hos Harper & Brothers som fattet "
	    "interesse."
	    "<br />"
	    "<br />"
	    "<b>Little House-bøkene utgis</b>"
	    "<br />"
	    "<br />"
	    "Nå skrev Laura om manuset. Hun bestemte seg for å skrive en "
	    "bok basert på minnene hennes fra tiden da hun bodde i "
	    "den store skogen i Wisconsin. Boka fikk navnet 'Little "
	    "House in the Big Woods' og inneholder blant annet "
	    "mange av fortellingene Charles fortalte til henne "
	    "da hun var liten. Hun ville gjerne dele disse fortellingene "
	    "med barn. I 1931 sa Harper & Brothers seg enige i å utgi boka. "
	    "<br />"
	    "<br />"
	    "Mens boka var i trykk tok Laura og Almanzo " 
	    "en biltur tilbake til "
	    "Sør-Dakota*. De kjørte den samme ruta som de tok da de dro "
	    "den andre veien 37 år tidligere. De Smet var nå blitt til "
	    "en moderne liten by. "
	    "Derfra dro de til Manchester og besøkte Grace "
	    "og ektemannen Nate. Siden Charles døde i på "
	    "starten av 1900-tallet, "
	    "Ma i 1924 og Mary i 1928, var Grace den " 
	    "eneste gjenlevende Ingalls- "
	    "familiemedlemmet som fortsatt bodde i det området. Deretter "
	    "satte de seg i bilen og dro til De Smet og Charles gårdssted "
	    "hvor Laura og Grace brukte en morgen på å gjennomgå det som "
	    "en gang i tiden tilhørte Caroline og Mary. Dette var lagret "
	    "i et rom i huset som Laura og familien en gang i tiden bodde i, "
	    "men som nå var utleid. "
	    "De skjønte snart at alt som var av verdier"
	    "var blitt borte. Deretter besøkte Laura og Almanzo gamle venner "
	    "i De Smet før de dro vestover til foten av Black Hills, en "
	    "annen del av Sør-Dakota hvor Carrie og ektemannen Davy Swanzey. "
	    "De hadde flyttet til byen Keystone på foten av Mount Rushmore. "
	    "Carrie tok så med Laura og Almanzo på en biltur i Black Hills "
	    "mens de snakket og mimret. "
	    "<br />"
	    "<br />"
	    "<table border='0'>"
	    "  <tr>"
		"<td valign='top' id='main'>"
		"  I 1932 ble 'Little House in the Big Woods' utgitt. "
		"  Laura kjøpte en kopi av boka og viste den til Rose, " 
		"  og de var "
		"  begge fornøyde med resultatet. " 
		"  Boka ble en stor suksess, på "
		"  tross av den økonomiske depresjonen " 
		"  som kom som en følge av "
		"  krakket i 1929. Fortellingene og " 
		"  minnene kom til live i boka "
		"  som ble en favoritt hos bokhandlere og på biblioteker."
		"  Boka ble så populær at Haper & Brothers spurte "
		"  etter en ny bok fra "
		"  henne. Dette skulle bli en bok om " 
		"  Almanzo Wilders barndom, og "
		"  ble hetende 'Farmer Boy'. "
		"  Denne ble utgitt i 1933 og ble også "
		"  en stor sukess. Tiden gikk og "
		"  Laura fikk spørsmål om å publisere "
		"  enda en bok. Denne kom i 1935 og ble hetende " 
		"  'Little House on the Prairie'. "
		"  Dette er den boka hun gjorde mest research rundt. "
		"  Det å finne navnet på indianersoldaten som "
		"  reddet livene deres, "
		"  Soldat du Chêne tok opptil flere uker. " 
		"  Laura hadde et skarpt minne "
		"  og fant ut at hun kunne forbedre det " 
		"  enda mer ved å gå tilbake "
		"  til det som var utenfor hennes ordinære " 
		"  hukommelse. Hun ville "
		"  at historiene hennes skulle bli sett på som sanne, så hun "
		"  sendte manuset inn til historieeksperter "
		"  før boka ble publisert, "
		"  for å se til at alt av historiske detaljer var korrekt. "
		"</td>"
		"<td valign='top'>"
		"  <a href='javascript:openOldLaura();'>"
		"  <img src='images/lauraingallswilder/laura_ingalls_gammel.jpg'></a>"
		"  <div id='imgtxt'>"
		"    Laura Ingalls. Bildet er tatt rundt 1932. "
		"  </div>"
		"</td>"
	      "</tr>"
	    "</table>"
	    "Den 3. "
	    "boka ble også en suksess, " 
	    "og nå bestemte hun seg for noe ingen " 
	    "hadde gjort før henne: hun planla nå å fortsette å skrive om "
	    "historien om barndommen hennes ved å opprette en <i>serie</i> "
	    "med bøker. 'Det vil være en historisk roman for barn som "
	    "handler om alle aspektene ved den amerikanske sivilisasjonens "
	    "yttergrenser. Alle ville at jeg skulle fortsette fortellingen "
	    "for å få vite hva som så skjdde,' sa Laura. "
	    "I 1937 kom boka "
	    "'On the Banks of Plum Creek'. " 
	    "Da boka ble utgitt, ble den tildelt "
	    "Newberry-medaljen. Newberry-medaljen deles ut til en forfatter "
	    "for en utmerket barnebok. I 1937 bestemte man også at bokserien "
	    "skulle hete 'Little House'. "
	    "I 1938 begynte hun på utkastene "
	    "til boka 'By the Shores of Silver Lake'. " 
	    "Den ble publisert i 1939 "
	    "og var Lauras andre bok som fikk Newberry-medaljen. "
	    "Bokhandlere og biblioteker hadde ventet ivrig på at boka skulle "
	    "komme. I 1940 begynte Laura å skrive manuset "
	    "til 'The Hard Winter'. "
	    "Denne sommeren dro Laura og Almanzo for siste gang til " 
	    "Sør-Dakota "
	    "for å besøke Grace og Carrie. Året etter ble boka publisert "
	    "under tittelen 'The Long Winter' fordi forlaget var redd for "
	    "at Lauras opprinnelige tittel skulle virke skremmende på barna. "
	    "'The Long Winter' var den 3. boka Laura utga som fikk Newberry- "
	    "medaljen. "
	    "<br />"
	    "<br />"
	    "Det tok ikke lange tiden fra utgivelsen av 'The Long Winter' "
	    "til Laura på nytt satte seg ned og " 
	    "skrev utkastet til neste bok, "
	    "'Little Town on the Prairie'. Også denne boka ble belønnet med "
	    "Newberry-medaljen etter at den ble publisert i 1941. Den siste "
	    "boka Laura utga før hennes død, var 'These Happy Golden Years'. "
	    "Boka ble utgitt i 1943 og i likhet med de 4 siste bøkene ble "
	    "også denne belønnet med Newberry-medaljen. Carrie skrev i et "
	    "brev at hun var stolt av den nye boka, og Rose komplimenterte "
	    "også denne boka. "
	    "<br />"
	    "<br />"
	    "I 1944 fikk Laura se Carrie for siste gang. Denne gangen kom "
	    "Carrie med tog fra Rapid City, Sør-Dakota for å besøke Laura. "
	    "Det var en spennende gjenforening. Laura sa: 'Kjærligheten i "
	    "vår tidlige barndom har fulgt deg hele veien'. 3 år tidligere "
	    "gikk Grace bort og Laura fortalte barna som skrev brev til henne "
	    "at Carrie og Laura var de eneste gjenlevende. " 
	    "Nå bestemte Laura, "
	    "Carrie og Rose at fela til Charles skulle på museum. De ble "
	    "enige om at fela skulle sendes tilbake til Sør-Dakota, siden "
	    "bøkene var veldig populære der og " 
	    "fordi en ansatt ved The De Smet "
	    "News, Aubrey Sherwood ofte promoterte de populære bøkene. "
	    "<br />"
	    "<br />"
	    "Etterspørselen etter enda ei bok var stor, og " 
	    "selv om Laura hadde "
	    "bestemt seg for at 'These Happy Golden Years' "
	    "skulle bli den siste "
	    "i serien, fikk etterspørselen etter enda en bok " 
	    "Laura til å sette "
	    "seg ned å skrive en ny bok. "
	    "Utkastet ble til 'The First Four Years'. "
	    "Samtidig var krigen i verden over "
	    "og det amerikanske utenriksdepartementet arrangerte en tysk "
	    "og japansk oversettelse av 'Little House'-bøkene, " 
	    "etter forespørsel "
	    "av Genereal Douglas MacArthur fordi han mente at boka var et "
	    "nøyaktig bilde av det amerikanske livet. Han mente at tyskerne "
	    "og japaneserne ville ha fordel av å ha lest dem. "
	    "Det viste seg å være et sjakktrekk. "
	    "Så fort bøkene kom ut i Tyskland "
	    "og Japan, begynte tyske og japanske brev å strømme inn. Og til "
	    "Lauras store forbauselse ble bøkene også oversatt " 
	    "og publisert i "
	    "andre land, deriblant Norge. På et brev til et " 
	    "japansk barn skrev "
	    "Laura: "
	    "'Selv om du er langt borte og snakker et annet språk, "
	    "er tingene som er verdt noe i livet fremdeles det samme " 
	    "for oss alle, og det samme som da jeg var et " 
	    "barn for lenge siden.'"
	    "Bøkenes popularitet økte. "
	    "Harper & Collins bestemte at de skulle "
	    "trykke bøkene på nytt med nye illustrasjoner, denne gang av "
	    "Garth Williams. Da de nye illustrasjonene ble ferdig "
	    "bemerket Laura at karakterene kom til " 
	    "live i de nye illustrasjonene. "
	    "<br /> "
	    "I 1949 fikk Almanzo to hjerteinfarkt. Det ene kom i juli, mens "
	    "det siste kom den 23. oktober 1949. I 1951 bestemte Mansfield "
	    "seg for å oppkalle det lokale biblioteket etter Laura. Denne "
	    "dedikasjonen ble holdt den 28. september 1951. Dette var den "
	    "første seremonien som var til ære om henne som hun deltok i. "
	    "Dette var mest av alt fordi hun ikke ville skuffe tilhengerne "
	    "hennes. Selv om savnet etter Almanzo var skarpt, " 
	    "ble Laura stadig "
	    "varmet av kjærligheten til hennes store familie av lesere. Hver "
	    "dag ble et bord som sto ved siden av rullestolen " 
	    "hennes fylt opp "
	    "av brev fra leserne hennes. "
	    "Og hver sommer var det alltid besøkende "
	    "fra andre delstater som kom for å treffe henne, blant dem var "
	    "vennene hun fikk i De Smet, mens de aller fleste var fremmede. "
	    "<br />"
	    "<br />"
	    "<b>Slutten på Lauras liv</b>"
	    "<br />"
	    "<br />"
	    "Da Laura var 87 år gammel tok hun sin første flytur. "
	    "Da dro hun for å besøke Rose som for mange år siden " 
	    "slo seg ned "
	    "i Danbury, Connecticut. Tidligere på året sa hun "
	    "at hun stort sett var oppgegående, tok seg av posten, gikk "
	    "i kirken, lagde mat og gjorde rent, men at det var dager hun "
	    "måtte ligge for å la hennes gamle, trette hjerte få hvile. "
	    "Hun likte å se Roses hus og hvordan hun levde. "
	    "3 år senere, den 7. februar 1959 fylte Laura 90 år. "
	    "Hun var nå blitt syk av en komplisert form for diabetes. " 
	    "Da fødselsdagen hennes nermet seg " 
	    "kom det brev fra hele verden. "
	    "Barn farget, klippet og limte og lagde "
	    "spesielle hilsener til Laura. "
	    "Med hjelp fra blant annet lærerne sendte de " 
	    "gratulasjonene avgårde. "
	    "Men bare 3 dager senere, den 10. februar 1957, " 
	    "sovnet Laura inn. "
	    "Laura hadde opplevd alt; "
	    "utviklingen fra hest og vogn til tog til bil til fly, "
	    "hun opplevde hvordan det var å leve i de siviliserte skogene, "
	    "hvordan det var å leve sammen med indianere, hvordan det var "
	    "å bo i byer på kanten av sivilisasjonen; hun så på byggingen "
	    "av jernbanen i vilt, ubebodd landskap og gårder og gårdsbruk "
	    "som 'kom opp' på det nye landet - Laura Ingalls Wilder hadde "
	    "sett og opplevd alt. Gjennom Lauras klare minner, "
	    "hennes skarpe "
	    "syn og evnen hennes til å fortelle oss lesere hva hun så "
	    "kan man oppleve det pioner-vesten slik hun opplevde den. "
	    "<br /> "
	    "<br /> "
	    "<b>I media</b> "
	    "<br /> "
	    "<br /> "
	    "<ul>"
	    "  <li>Melissa Gilbert spilte rollen som Laura Elizabeth "
		"Ingalls Wilder gjennom hele TV-serien "
		"'Det lille huset på prærien' (1974-1984) "
	      "<li>Meredith Monroe, Tess Harper som den voksne Laura, "
		"Alandra Bingham som den lille Laura i del 1, og "
		"Michelle Bevan som den lille Laura i del 2 av TV-filmene "
		"'Bortenfor prærien: Laura Ingalls Wilders sanne historie' "
	      "<li>Kyle Chavarria spilte rollen som Laura Elizabeth "
		"Ingalls Wilder i ABC sin miniserie om "
		"'Det lille huset på prærien' (2005) "
	    "</ul>"
	    "<br />"
	    "<br />"
	    "<b>Merknad</b>"
	    "<br />"
	    "<br />"
	    "*) I 1890 ble Dakota-territoriet delt opp i Nord- og Sør-Dakota."
	    "Dette er grunnen til at det i starten av artikkelen står "
	    "Dakota-territoriet, mens det på slutten står Sør-Dakota.\");"))
	{
	  exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if(mysql_query(conn, "INSERT IGNORE INTO tbl_characters VALUES(6, \"Mary Ingalls\", \"<table border='0'>"
	    "<tr>"
	    "  <td valign='top' id='main'> "
		"Mary Amelia Ingalls var Lauras storesøster. "
		"Hun ble født utenfor "
		"den lille byen Pepins 10. januar 1865 av foreldrene "
		"<a href='characters.php?character=Caroline+Ingalls'>Caroline Ingalls</a> og "
		"<a href='characters.php?character=Charles+Ingalls'>Charles Ingalls</a>, "
		"som det første av 5 barn. "
		"Laura beskrev Mary som ei snill og rolig jente. "
		"Dette kom også "
		"til uttrykk da hun i en alder av 14 år ble rammet av "
		"skarlagensfeber, et alvorlig tilfelle av meslinger "
		"og et hjerneslag "
		"og på toppen av det hele, mistet synet, uten at hun skal ha "
		"klaget over det én eneste gang. "
		"<br />"
		"<br />"
		"Det samme året flyttet hun og familien hennes til "
		"<a href='books.php?book=By+the+Shores+of+Silver+Lake'>De Smet</a> "
		"i det som en gang het Dakota Territory. "
		"2 år etter at de flyttet "
		"dit fikk foreldrene en god nok øknonomi til å kunne sende "
		"henne til en skole for de blinde "
		"(The Iowa College for the Blind) i Vinton, Iowa. "
	      "</td>"
	      "<td valign='top'>"
		"<a href='javascript:openWin();'>"
		"<img src='images/lauraingallswilder/mary_1.jpg' width='373' height='359' /></a>"
		"<div id='imgtxt'>"
		 " Mary Amelia Ingalls "
		"</div>"
	      "</td>"
	    "</tr>"
	  "</table>"
	  "På den tiden var det vanlig at de pårørende fikk "
	  "offentlig økonomisk støtte slik at de kunne sende de blinde "
	  "barna til skolen for de blinde i Iowa, selv om Laura ikke "
	  "skrev om dette i sine bøker). "
	  "8 år senere tok hun den siste eksamen "
	  "på skolen og flyttet hjem igjen til foreldrene i De Smet. "
	  "Da de døde flyttet hun til Grace og bodde sammen med henne, "
	  "og deretter til Carrie hvor hun tilbragte sine siste leveår. "
	  "<br />"
	  "Den 20. oktober 1928 sovnet hun inn. Hun døde av lungebetennelse "
	  "og komplikasjoner av et slag. I dag ligger hun begravet sammen "
	  "med resten av familien, med unntak av Laura, i De Smet. "
	  "<br />"
	  "<br />"
	  "<b>I media</b> "
	  "<br /> "
	  "<br /> "
	  "<ul>"
	  "  <li>Melissa Sue Anderson spilte rollen som Mary Amelia Ingalls "
	  "    i TV-serien 'Det lille huset på prærien' i sesong 1-7 og "
	  "    2 episoder i sesong 8 (1974-1982) "
	  "    og i filmen 'Little House Years' (1979) "
	  "  <li>Barbara Jane Reams og Alexandra Smith spilte rollene som "
	  "    Mary Amelia Ingalls (Alexandra Smith spilte den unge Mary) "
	  "    i TV-filmen 'Bortenfor prærien: "
	  "    Laura Ingalls Wilders 'sanne' historie' (2000) "
	  "  <li>Danielle Chuchran spilte rollen som Mary Amelia Ingalls "
	  "    i ABC sin miniserie om 'Det lille huset på prærien' (2005) "
	  "</ul>"
	  "<br />"
	  "<br />"
	  "I tillegg har Elizabeth Cody Kimmel skrevet romanen "
	  "'Mary Ingalls on Her Own (Mary Leaves Little House)'. "
	  "Boka forteller om tiden Mary tilbragte på skolen for de blinde "
	  "i The Iowa College for the Blind, og ble utgitt i desember 2007.\");"))
	{
	  exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	mysql_close(conn);
}
void insertBooks()
{
  char errorString[100] = "MySQL error: ";
  MYSQL *conn;
  char *server = "localhost";
  char *userName = user;
  char *passwd = password;
  char *database = "little_house";
  conn = mysql_init(NULL);
  if(conn == NULL)
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  if(!mysql_real_connect(conn, server, userName, password, database, 0, NULL,0))
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
	if(mysql_query(conn, "INSERT IGNORE INTO tbl_books VALUES (1, \"Little House in the Big Woods\", \"Det vesle huset i den store skogen\", 1933, 2004, \"Caroline Ingalls, Carrie Ingalls, Charles Ingalls, Laura Ingalls, Mary Ingalls\", \"Laura Colby Ingalls ('Grandma')<br />Landsford Whiting Ingslls ('Grandpa')<br />Lotty Holbrook ('Aunt Lotty')<br />Peter Ingalls ('Uncle Peter')<br />Eliza Quiner Ingalls ('Aunt Eliza')<br />Peter Ingalls<br />Alice Ingalls<br />Ella Ingalls\", \"George Ingalls ('Uncle George')<br />Docia Ingalls ('Aunt Docia')<br />Ruby Ingalls ('Aunt Ruby')<br />James Ingalls ('Uncle James')<br />Libby Ingalls ('Aunt Libby')<br />Laura Ingalls ('the other Laura')<br />Henry Ingalls ('Uncle Henry')<br />Charley Ingalls ('Cousin Charley')<br />Mrs. Peterson<br />Mr. Huleatt<br />Mrs. Huleatt<br />Eva Huleatt<br />Clarence Huleatt\", 238, \"'Little House in the Big Woods' (eller "
	    "'Det lille huset i de store skogene') "
	    "er den første av 9 romaner som er skrevet "
	    "av Laura Ingalls Wilder. Romanen handler "
	    "om livet familien Ingalls levde noen kilometer utenfor byen "
	    "Pepin, Wisconsin. "
	    "Boka er basert på Lauras egne minner og beskriver hvordan "
	    "Laura observerte og begynte "
	    "å praktisere levemåten gjennom hennes 5. leveår."
	    "Boka inneholder reelle, men ikke dramatiske temaer som"
	    "de senere bøkene gjør."
	    "<br />"
	    "<br />"
	    "<b>Handlinga i boka</b>"
	    "<br />"
	    "<br />"
	    "Veien til suksess fullføres kun med hjelp av hardt arbeid, "
	    "men midt oppe i det hele "
	    "satte man alltids av tid til hygge og moro. "
	    "Laura ville mer enn gjerne hjelpe til når foreldrene var "
	    "opptatt med noe; "
	    "holdt faren "
	    "<a href='characters/charles_ingalls.html'>Charles</a> "
	    "på å hågge ved, "
	    "hjalp Larua til med å samle sammen trefliser. "
	    "Skulle Laura og storesøsteren "
	    "<a href='characters/mary_ingalls.html'>Mary</a> "
	    "ha det skikkelig gøy, "
	    "lagde de ballonger av griseblærer(!) "
	    "og lekte med disse. "
	    "I denne romanen beskriver Laura hvordan de lager ost og "
	    "annen mat fra bunnen av. "
	    "Høsten er den aller traveleste tiden på året. "
	    "I tillegg til å forberede og lagre maten "
	    "som skal vare vinteren igjennom er det alltid andre ting "
	    "med gården som også må høstes inn."
	    "<br /><br />"
	    "Deretter står jula for døra, og dette året er får de "
	    "besøk av tanter, onkler og søsenbarn. "
	    "Det var kommet mye snø, så når barna fikk tid, "
	    "gikk de ut og 'tok bilder' av seg selv "
	    "ved å stå på en trestamme og legge seg ned i snøen "
	    "og prøve å reise seg opp igjen uten å lage "
	    "noen flere merker i snøen. "
	    "En annen lek de lekte, "
	    "gikk ut på å hoppe fra trestamme til trestamme, "
	    "uten å sette foten i bakken. Da juledagen endelig kom, "
	    "fortalte Laura at hun fikk en egen dukke som hun kalte "
	    "Charlotte."
	    "<br /><br />"
	    "På den tiden var det vanlig at slektninger samles "
	    "for å gjøre  'store oppgaver'. "
	    "Dette var for å gjøre arbeidet både enklere og morsommere. "
	    "Et eksempel på dette var senere den samme vinteren da "
	    "familien dro til "
	    "'Grandma' (der hvor Laura kom fra og på den tiden var det "
	    "ikke vanlig å kalle foreldrene for 'Mother' "
	    "og 'Father', men Ma og Pa, og det samme gjaldt for "
	    "besteforeldrene som ble kalt "
	    "'Grandma' og 'Grandpa') for å lage lønnesirup og brunt "
	    "sukker som varte året ut."
	    "<br />"
	    "<br />"
	    "En ny årstid betyr en ny type arbeid. "
	    "Laura forsøkte å gjøre dette attraktivt ved "
	    "å fortelle om alle gode tingene som arbeidet resulterte til. "
	    "Om våren fikk kua en kalv, "
	    "og på denne måten kunne de skaffe seg både melk, smør og ost." 
	    "Skulle de lage ost, tok de løypemagen til kalven "
	    "og kokte denne i melk "
	    "for å få separere dravlen og mysen. 'Ma' tok ut dravlen" 
	    "og tok vare på mysen. "
	    "Hun, Mary og Laura puttet dravlen i såkalt "
	    "ostering ('cheese hoop') "
	    "og setter et brett og en vekt for å få ekstra "
	    "mye myse til å renne ut av dravlen."
	    "Laura og Ma lot ringen ('hoop') være på "
	    "hele den neste natta,"
	    "for så å ta ut den nye osten,"
	    "legge et slags klede/tøy tett rundt den og deretter "
	    "smøre inn smør over hele osten."
	    "Til slutt legger de osten i papir og tar vare på "
	    "osten til senere bruk."
	    "<br />"
	    "Da de lagde smør, brukte Mary og 'Ma' en smørkjerne "
	    "for å kjerne kremen inntil det ligger"
	    "klumper med smør i kjerna. Var det én ting Laura likte," 
	    "var det å drikke den ferske"
	    "kjernemelka etter at Ma hadde skylt og saltet den."
	    "<br />"
	    "<br />"
	    "Den sommeren og høsten plantet de igjen "
	    "både hager og åkere og "
	    "lagret mat til den neste vinteren."
	    "Lauras 'Pa' byttet hardt kroppsarbeid med "
	    "andre farmere i området "
	    "slik at avlingene hans kan høstes raskere "
	    "når den tiden kommer."
	    "I tillegg til gårdsarbeidet var jakt en viktig "
	    "del av det å bidra til selve familielivet. "
	    "Når Pa gikk på jakt, kom han stort sett "
	    "hjem med et hjortedyr som han røyket "
	    "for å ta vare på den til den kommende vinteren."
	    "En dag la han merke til at det var et tre med en bikube, "
	    "og den dagen la han avsted med"
	    "vaskebalje og melkespann for å få tak i selve honningen."
	    "<br />"
	    "Når kveldsmørket senket seg sent om høsten og vinteren, "
	    "fortalte Laura at alle koste seg"
	    "og hørte på faren som spilte med fela hans."
	    "<a href='javascript:openLittleHouseWayside();'>"
	    "  <img src='images/lauraingallswilder/little_house_wayside_replica.jpg' height='480' width='640' /></a>"
	    "<div id='imgtxt'>"
	    "  En eksakt kopi av Laura Ingalls Wilders hjem nær Pepin," 
	    "  Wisconsin, stedet der handlingen i "
	    "  'Little House in the Big Woods' fant sted." 
	    "  Det som en gang i tiden var en tett skog"
	    "  er nå blitt til et åpent landskap."
	    "</div>"
	    "<br />"
	    "<br />"
	    "<b>Merknad</b>"
	    "<br />"
	    "I 'Little House in the Big Woods' utgir Laura" 
	    "seg for å være 6 år gammel."
	    "Sannheten er at hun bare er 3 år gammel. "
	    "Handlingen som finner sted i denne boka,"
	    "finner sted først <b>etter</b> handlingen i "
	    "<a href='books.php?book=Little+House+on+the+Prairie'>"
	    "  Little House on the Prairie</a>. "
	    "Laura og Mary begynte på skolen i Pepins, ikke i"
	    "<a href='books.php?book=On+the+Banks+of+Plum+Creek'>"
	    "  Walnut Grove, Minnesota</a>, "
	    "men dette inkluderte hun ikke i boka.\");"))
	{
	  exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if(mysql_query(conn, "INSERT IGNORE INTO tbl_books VALUES(2, \"Farmer Boy\", \"Ikke oversatt til norsk\", 1933, 2004,\"Eliza Jane Wilder, Almanzo Wilder, m. fl\", \"Ingen gjestekarakterer\", \"Mr. Paddoc m fl.\", 372, \"'Farmer Boy' er en barnebok som er skrevet av"
	   "<a href='characters/laura_ingalls_wilder.html'>"
	   "  Laura Ingalls Wilder</a>."
	   "Boka ble publisert i 1933, og selv om det er den andre boka"
	   "av i alt 9 bøkeri 'Little House'-bokserien, leses denne"
	   "som regel som den 3. boka, etter"
	   "<a href='books.php?book=Little+House+in+the+Big+Woods'>"
	   "  'Little House in the Big Woods'</a> og"
	   "<a href='books.php?book=Little+House+on+the+Prairie'>"
	   "  'Little House on the Prairie'</a>."
	   "<br />"
	   "<br />"
	   "Boka er basert på Almanzo Wilder, Lauras ektemann, sin barndom,"
	   "i nærheten av Malone, New York (merk: Gården han vokste opp i"
	   "lå nermere byen Burke, selv om det er Malone som nevnes)."
	   "Boka begynner en skoledagsmorgen, like før Almanzos 9."
	   "fødselsdag. Noen eldre gutter som går på den samme skolen"
	   "planlegger å gjøre livet surt for læreren."
	   "Almanzos far får vite om det, og da læreren kommer på"
	   "besøk, får læreren et verktøy han kan bruke for å forsvare seg"
	   "mot bråkmakerne. Som en følge av dette, mislykkes bråkmakerne og"
	   "de jages til slutt på dør."
	   "<br />"
	   "<br />"
	   "Almanzo viser at han er en gutt som jobber hardt for å"
	   "vise både foreldrene og søsknene at han, på tross av"
	   "at han er liten av vekst og ung av alder, er i stand til å"
	   "ha større ansvar i og rundt gården. Han er en som er veldig"
	   "glad i hester, og jobber mye i låvene som er satt opp i gården."
	   "Han bruker mye tid på å lære både hester og okser som"
	   "'Ptro' ('Whoa!') og hoppla ('giddap'), i tillegg til"
	   "kommandoer som får dyrene til å gå til høyre og venstre."
	   "Almanzos virkelig store barndomsdrøm er at faren hans en vakker"
	   "dag vi stole nok på ham til at han gir Almanzo en egen hest."
	   "<br /> "
	   "Boka avsluttes med at Almanzos drøm går i oppfyllelse:"
	   "En dag da Almanzo og faren drar til byen, møter de på"
	   "en hjulmaker som heter Mr. Paddoc."
	   "Han bestemmer seg for å spørre Almanzo om han vil"
	   "bli en lærling i hjulmakeryrket. "
	   "Siden Almanzos bror Royal allerede har sagt"
	   "han vil jobbe som en butikkinnehaver, håper Almanzos foreldre"
	   "at han skal bli en bonde. "
	   "Vel hjemme spør faren om han vil godta"
	   "hjulmakerens tilbud. Overaskelsen er stor for både faren og"
	   "hjulmakeren når Almanzo svarer med å spørre om han kan få"
	   "et hingstføll isteden. Faren sier at hvis det er dét han ville,"
	   "skulle han få hesten Starlight."
	   "<br />\");"))
	{
	  exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if(mysql_query(conn, "INSERT IGNORE INTO tbl_books VALUES(3, \"Little House on the Prairie\", \"Det vesle huset på prærien (del 1) og Det vesle huset i indianernes land (del 2)\", 1935, 2004, \"Caroline Ingalls<br />Carrie Ingalls<br />Charles Ingalls<br />Laura Ingalls<br />Mary Ingalls\",\" Mr. Scott<br />Mrs. Scott<br />Mr. Edwards\", \"Dr. Tan\", 335,\"'Little House on the Prairie' er den mest berømte av de 9" 
	   "romanene i 'Little House'-serien. "
	    "Dette regnes som den 3. boken i serien, etter "
	    "<a href='books.php?book=Little+House+in+the+Big+Woods'>"
	    "  'Little House in the Big Woods'</a> og "
	    "<a href='books.php?book=Farmer+Boy'>'Farmer Boy'</a>."
	    "<br />"
	    "<br />"
	    "<b>Selve fortellingen</b>"
	    "<br />"
	    "<br />"
	    "<u>Avreise fra Wisconsin</u>"
	    "<br />"
	    "<br />"
	    "Fortellingen begynner rundt den tiden da Pa bestemmer " 
	    "seg for å selge gården "
	    "og 'Go see the west,' som han sa - til det indianske territoriet "
	    ", og tanter, onkler, søskenbarn og besteforeldre "
	    "som tar farvel med Mary, Laura, Carrie (se kommentar nederst "
	    "på siden), hunden Jack "
	    "(en bulldog), Ma og Pa. "
	    "Under reisen som begynte sent om vinteren krysset de " 
	    "Mississippi og slo leir på den andre "
	    "siden av elva - virkelig i grevens tid. "
	    "Natta etter begynte isen på Mississippi å "
	    "sprekke og smelte. "
	    "<br /> "
	    "Det var en lang tur og det hendte rett som det var at " 
	    "Pa måtte grave ut vogna "
	    "av søle og lignende ting. En dag de satt fast i søla og " 
	    "ventet på at en flom i en bekk "
	    "de skulle krysse, skulle gå ned, byttet Pa ut hans 2 " 
	    "'gamle' hester med 2 mustanger "
	    "som Laura og Mary kaller for Patty og Pet. " 
	    "<br /> "
	    "Turen fortsatte og noen uker senere kom de frem til den siste " 
	    "elva de skulle krysse; "
	    "Verdigris River. I likhet med mange andre bekker og elver de " 
	    "krysset, var denne her også i flom, "
	    "men ikke verre enn at de skulle klare å krysse den - trodde de. " 
	    "Da de var midt ute på vannet, "
	    "begynte det å stige og hestene måtte ta til å svømme med Pa "
	    "(som selv så vidt klarte å holde hodet over vann) sin hjelp. " 
	    "Laura maste om at de skulle "
	    "la Jack sitte på i vogna, men Pa sa nei, og Jack ble skylt med " 
	    "strømmen. "
	    "Pa som hadde lovet Laura at han ikke ville gjøre noe sånt mot " 
	    "hunden, selv ikke om han fikk "
	    "en million dollar for å gjøre det, lurte på hvordan de skulle " 
	    "klare seg uten en så god "
	    "vakthund. Den kvelden hørte de det de trodde var ulvelyder og " 
	    "akkurat idet Pa skulle "
	    "skyte mot det stedet lyden kom fra, dukket "
	    "Jack til alles store overraskelse, og Lauras "
	    "store glede, opp igjen. "
	    "<br />"
	    "<br />"
	    "<u>Ankomst</u>"
	    "<br />"
	    "<br />"
	    "Nå var de kommet frem til det indianske territoriet og "
	    "Pa begynte å lete etter et "
	    "sted hvor han kunne begynne å bygge huset. " 
	    "De slo seg til slutt ned i området rundt "
	    "Independence, Kansas, og det gikk ikke lenge før de første "
	    "tømrene var på plass og selve fundamentet for huset var lagt. " 
	    "Pa dro ofte ned til elva "
	    "og fant tømmer han kunne bruke til å bygge opp huset."
	    "Mens faren bygde opp huset, møtte de på Mr. Edwards, eller "
	    "'villkatten fra Tennessee,' som "
	    "han kalte seg. Han skulle bli Ingalls-familiens beste venn "
	    "under oppholdet og han hjalp Pa med "
	    "å bygge huset etter at Ma hadde skadet seg, mot at Pa hjalp " 
	    "Edwards med hans hus senere. "
	    "Deretter forteller Laura at Pa lagde en brønn med hjelp fra " 
	    "en annen nabo - familien Scott. "
	    "Endelig var familien klar til å flytte inn i det nye huset. "
	    "<br />"
	    "<br />"
	    "I motsetning til "
	    "<a href='books.php?book=Little+House+in+the+Big+Woods'> "
	    "  'Little House in the Big Woods'</a> "
	    "var det flere farer og snarer som lurte. "
	    "En dag som Pa var dratt på jakt, hadde familien "
	    "indianerbesøk; Laura fortalte at indianerene trodde " 
	    "at huset tilhørte indianerne og de behandlet "
	    "huset og det som var inne i det, som om det var deres eget "
	    "og tok med seg både det ene og det andre. "
	    "Pa sa at 'så lenge enden er god, er allting godt' " 
	    "og at de ikke måtte bli fiender med indianerne. "
	    "<br />"
	    "<br />"
	    "<u>Malaria</u> "
	    "<br />"
	    "<br />"
	    "Senere i oppholdet fortalte Laura at familien ble slått " 
	    "ut av sykdom - alle på én gang. "
	    "En sensommerdag fortalte Laura at hun var varm og kald " 
	    "om hverandre og at hun hadde smerter så "
	    "og si overalt. Det samme hadde Mary, og Pa var heller "
	    "ikke i toppform. De hadde fått noe "
	    "de på den tiden kalte 'Fever 'n' ague' "
	    "(feber med kraftig kulde og risting), som i dag " 
	    "kalles malaria. For å illustrere det hele: "
	    "Laura fortalte at Mary gråt etter vann, men at "
	    "både Ma og Pa var for syke til at de kunne reise seg opp, " 
	    "gå noen få meter over gulvet "
	    "til et spann som var fylt med vann fra brønnen, " 
	    "så de ba Laura om å gjøre det. "
	    "Laura selv måtte ha 2 forsøk på å komme seg opp av senga, " 
	    "og da hun kom seg opp den andre "
	    "gangen, klarte hun så vidt med god hjelp fra hunden " 
	    "Jack å krabbe over gulvet, stikke en dyp "
	    "skje ned i spannet som var fylt med vann, kråle seg " 
	    "'over det enorme gulvet,' som hun sa og gi Mary "
	    "det vannet hun trengte. "
	    "Mens de var syke, tok familien Scott seg av dem. Mr. " 
	    "Scott bemerket at "
	    "de så mer ut som om de var døde enn levende. "
	    "Noen dager senere, da en farget lege hadde gitt dem "
	    "den medisinen de trengte, var alt tilbake til det normale. "
	    "På den tiden visste man ikke at 'fever 'n' ague' var malaria, " 
	    "og man kunne få det av mygg, "
	    "så rådet de som var syke (alle naboene var også syke; "
	    "kun Mr og Mrs Scott var friske nok til å hjelpe de andre) fikk, " 
	    "var å holde seg borte fra dårlige vannmeloner! "
	    "<br />"
	    "<br />"
	    "<u>Jul</u>"
	    "<br />"
	    "<br />"
	    "Nå var vinteren komme til det indianske territoriet, " 
	    "men snøen uteble. Pa hadde gjort "
	    "avtale med Mr. Edwards om at han skulle tilbringe " 
	    "julen hos dem, men natta mellom "
	    "julaften og 1. juledag hadde det begynt å regne, " 
	    "så ingen av dem trodde Mr. Edwards ville "
	    "komme for å spise julemiddag med dem. "
	    "Overrakselsen var derfor stor da en iskald og "
	    "skjelvende Mr. Edwards kom, etter å ha vært i "
	    "Independence og 'møtt julenissen' og tatt med "
	    "seg gaver til Mary, Laura og Carrie. Laura fortalte at " 
	    "hun og Mary hadde fått hver sine kopper, "
	    "én godteribit og en hel penny hver seg. "
	    "<br />"
	    "<br />"
	    "<u>Præriebrann og indianske krigsrop</u>"
	    "<br />"
	    "<br />"
	    "Våren var kommet og Pa hadde vært en tur i Independence og " 
	    "skaffet seg en plog "
	    "han kunne bruke til å pløye jorda og for alvor starte " 
	    "gårdsvirksomhet. En dag "
	    "han var ute og jobbet i jorda kom det en sky " 
	    "av røyk bortover prærien. Noen "
	    "dramatiske minutter senere hadde flammene nådd elva "
	    "de bodde ved og dødd ut - flammene "
	    "hadde bare så vidt bommet på huset deres. "
	    "<br />"
	    "Kort tid etter skulle de oppleve et av familiens hittil " 
	    "værste mareritt. "
	    "Indianere tilhørende ulike stammer som holdt til i nærheten " 
	    "hadde begynt å rope og skrike "
	    "noe fryktelig til hverandre. Skrikinga opphørte om dagen, " 
	    "men var høyere for hver natt som gikk. "
	    "I boka skriver Laura at "
	    "'Når man våker, er marerittet over, " 
	    "men dette marerittet fortsatte "
	    "selv om jeg var våken.' "
	    "Skrikinga foregikk i flere dager. " 
	    "Kort tid senere møtte Pa "
	    "høvdingen av Osage-stammen, Soldat du Chêne, og " 
	    "han fortalte at ropene gikk ut på en "
	    "diskusjon mellom indianerstammene - alle stammene, " 
	    "bortsett fra Osage-stammen ville ta "
	    "livet av de hvite nybyggerne som kom dit, "
	    "men at Soldat du Chêne fikk satt en stopper for det i tide. "
	    "<br />"
	    "<br />"
	    "<u>Avslutningen av boka</u>"
	    "<br />"
	    "<br />"
	    "Etter at de voldsomme krigsropene var over dro de ulike " 
	    "indianerstammene hvert til sitt, "
	    "og livet fortsatte som normalt igjen. "
	    "En dag så familien en endeløs rekke av indianere "
	    "som red vestover forbi huset de bodde i. "
	    "Men gleden over å kunne få leve i fred var kortvarig. "
	    "En morgen hadde Pa fått et brev som sa at det indianske " 
	    "territoriet ikke var åpent for "
	    "at de hvite kunne slå seg ned der - de bodde 5 km på " 
	    "feil side av grensa, og at hvis "
	    "de ikke flyttet derfra, ville man sende soldater som " 
	    "skulle sørge for at de hvite kom seg ut. "
	    "Pa hadde bestemt seg for å dra frivillig, " 
	    "som den eneste i 'nabolaget'. "
	    "<br />"
	    "<br />"
	    "<b>Merknader</b>"
	    "<br />"
	    "<br />"
	    "Mye av det som skjer i romanen, er hendelser som faktisk " 
	    "skjedde mens de bodde der. "
	    "Boka er basert på det som Ma, Pa og storesøstra Mary har " 
	    "fortalt henne opp gjennom årene - "
	    "da de bodde i Kansas var Laura bare 2-3 1/2 år gammel " 
	    "og dermed for ung til å huske det selv. "
	    "Av den grunn gjorde Laura mer historisk research rundt " 
	    "hendelsene i denne romanen enn de andre "
	    "for å få det til å få detaljene til å være så korrekte " 
	    "som mulig. I boka gir hun seg ut for å være "
	    "6-7 år gammel, siden hun i den første boka ga seg ut " 
	    "for å være 4-5 år gammel (da var de allerede "
	    "komme tilbake til Wisconsin), dette var fordi hun ville " 
	    "at hun ville ha denne boka kronologisk "
	    "etter den første. Dette er også en forklaring på hvorfor " 
	    "Carrie var med i boka helt ifra starten av. "
	    "Egentlig ble Carrie født i Kansas kort tid før de måtte dra " 
	    "derfra. Fra og med den neste boka, "
	    "<a href='books.php?book=On+the+Banks+of+Plum+Creek'> "
	    "  'On the Banks of Plum Creek'</a>, "
	    "stemmer den oppgitte alderen med den virkelige alderen. "
	    "<br />"
	    "En siste ting som er verdt å nevne er at kort tid etter "
	    "at Carrie ble født, gjennomførte amerikanske myndigheter "
	    "en folkeopptelling. Charles ble fortalt at han ikke ville "
	    "få registrert noen eiendeler fordi han bodde på indianernes "
	    "territorium. Kort tid etter fikk Charles et brev fra en "
	    "svenske som hadde kjøpt gården i 'The Big Woods' som "
	    "sa at han gjerne ville selge gården. Charles bestemte "
	    "seg da for å ta familien med seg tilbake til Wisconsin. "
	    "Perioden etter tilbakekomsten til Wisconsin ble beskrevet "
	    "av Laura i boka "
	    "<a href='books.php?book=Little+House+in+the+Big+Woods'>"
	    "  'Little House in the Big Woods'</a>.\");"))
	{
	  exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if(mysql_query(conn, "INSERT IGNORE INTO tbl_books VALUES(4, \"On the Banks of Plum Creek\", \"Det vesle huset i haugen (del 1) og Det vesle huset ved elvebredden (del 2)\", 1937, 2004, \"Caroline Ingalls<br />Carrie Ingalls<br />Charles Ingalls<br />Laura Ingalls<br />Mary Ingalls\", \"Nellie Oleson, Willie Oleson, Mr. Oleson, Mrs. Oleson, Eva Beadle ('Miss Beadle')\", \"Mr. Nelson, Anna Nelson, Mrs. Nelson, Mr. Hanson, Reverend Robert Alden ('Reverend Alden'), Christy Kennedy, Sandy Kennedy, Nettie Kennedy, Cassie Kennedy, Donald Kennedy, Mr. Beadle, Mr. Fitch, Mr. Tower, Mrs. Tower\", 339, \"'On the Banks of Plum Creek' "
	   "handler om den tiden da Laura og familien "
	   "hennes bodde utenfor Walnut Grove, Minnesota. "
	   "<br />"
	   "Boka begynner med at Pa sine hester stoppet " 
	   "ved en bekk som heter "
	   "Plum Creek, hvor de møter Mr. Hanson, en nordmann som hadde " 
	   "tenkt å flytte vestover. "
	   "Deretter selger Pa hestene de kjøpte på vei til "
	   "<a href='books.php?book=Little+House+on+the+Prairie'>Kansas</a> og skaffer "
	   "seg et par okser som han bruker til å pløye jorda med. "
	   "<br />"
	   "Laura som nå var 7 år gammel, var ei aktiv jente. " 
	   "En søndag hadde "
	   "Pa tatt med familien til et svømmehull ikke så langt ifra "
	   "jordhytta ('dugout') de bodde i for å bade. Pa sa at ingen av "
	   "jentene fikk lov til å bade der uten at " 
	   "noen av foreldrene var med. "
	   "En dag Laura var ute og lekte, fant hun det forgodt " 
	   "å klatre opp på  en høyslette som lå på stien " 
	   "som leder bort til dette svømmehullet. "
	   "Hun hadde bestemt seg for å ikke gå lenger "
	   "enn til høysletta, men "
	   "da hun kom opp til toppen fikk hun se dette 'hullet', og huden "
	   "føltes tørr og tørst. Hun begynte å skli ned fra høysletta for å "
	   "gå hjem og ta seg noe å drikke. "
	   "Ikke lenge etter snudde hun og gikk "
	   "tilbake mot svømmehullet, til tross for at Pa sa nei. " 
	   "Etter å ha "
	   "møtt på det som viste seg å være en grevling " 
	   "og lekt litt med denne, "
	   "bestemte hun seg til slutt for å gå tilbake til jordhytta. "
	   "Den kvelden la hun seg med dårlig samvittighet. Hun visste at "
	   "Pa og Ma stolte på henne, og at hun var på vei til å gjøre noe "
	   "hun ikke fikk lov til. "
	   "Hun fikk det bare verre og verre inni seg "
	   "selv. Til slutt holdt hun ikke ut lenger og gikk til slutt ut "
	   "til foreldrene hennes, "
	   "som bemerket at hun så ut som et spøkelse. "
	   "Hun fortalte Pa det hun hadde gjort " 
	   "og sa at han måtte straffe henne "
	   "på den måten han følte var rettferdig. Denne historien endte opp "
	   "med at hun måtte tilbringe den neste dagen inne sammen med Ma, "
	   "og hun fikk ikke lov til å gå ut av hennes synsfelt " 
	   "hele den neste "
	   "dagen, for som faren sa, man må følge med på personer man ikke "
	   "kan stole på, og hvis hun holdt det, skulle hun få en ny sjanse "
	   "på å være den jenta de kunne stole på. "
	   "<br /> "
	   "Den aller første jula de feiret i " 
	   "Minnesota feiret de ved å gi Pa "
	   "et par nye hester. "
	   "<br /> "
	   "<br /> "
	   "Et nytt år begynte. Om våren sådde " 
	   "Pa korn som skulle brukes til "
	   "å nedbetale regninga for å bygge et nytt hus. "
	   "I motsetning til de forrige stedene de var, hvor Pa bygde huset "
	   "med tømmer han skaffet selv, kjøper han det "
	   "han trenger for å bygge "
	   "huset, og nedbetalinga av huset skal skje " 
	   "gjennom å selge avlingene "
	   "han høster inn. "
	   "<br /> "
	   "<br /> "
	   "<u>Skole</u> "
	   "<br /> "
	   "<br /> "
	   "I løpet av året hadde Pa bygd et moderne trehus. "
	   "Og siden de bare bodde 4 kilometer fra byen Walnut Grove, "
	   "hadde Ma og Pa bestemt at Laura og søstera " 
	   "Mary skulle begynne på "
	   "skolen - det var hovedgrunnen til at de "
	   "valge nettopp denne byen. "
	   "Så avsted bar det. Etter å ha sagt at de " 
	   "andre elevene på skolen  "
	   "hørtes ut som en gjeng med præriehøns på grunn av lydnivået "
	   "møtte hun på ei jente med navn Nellie Oleson som kalte dem "
	   "bondejenter. Dette var starten på det som skulle bli et "
	   "finedeskap mellom Laura og Nellie. Lærerinna, Miss Eva Beadle "
	   "sa at de måtte skaffe seg ei tavle " 
	   "for å kunne lære seg å skrive. "
	   "Dagen etter hadde de fått 10 cent av Pa for å kjøpe denne tavla, "
	   "men da Mr. Oleson sa at de også måtte ha en 'griffel', "
	   "sa Nellie: 'Jeg tror ikke bondejentene har nok til å kunne "
	   "kjøpe en griffel' "
	   "<br /> "
	   "<br /> "
	   "<u>Gresshoppere</u> "
	   "<br /> "
	   "<br /> "
	   "Nå var det bare ei uke igjen til avlingene skulle høstes." 
	   "Da skjedde katastrofen. "
	   "Sommeren som var over, hadde vært en av de tørreste sommerene "
	   "noensinne, og nå hadde millioner av gresshoppere kommet østover "
	   "fra Rocky Mountains. Laura skrev at da de kom, var det som om " 
	   "en storm bygde seg opp; de kom som en sky som " 
	   "dekket for sollyset. "
	   "Det gikk ikke lange tiden før familien hørte "
	   "lyden av millioner av "
	   "tyggelyder - gresshoppene spiste opp alt " 
	   "som var av levende ting; "
	   "korn, bær, frukt, gress, alt som var. Pa forsøkte å bruke røyk "
	   "for å 'jage' dem vekk, men ingenting hjalp. Og enda værre - " 
	   "gresshoppene hadde lagt egg, hvilket betydde at det heller "
	   "ikke ville bli noen avlinger det neste året heller, og huset "
	   "måtte fortsatt nedbetales. Måten Pa løste det på, var ifølge "
	   "Laura å <i>spassere</i> inntil 300 engelske miles - ca 450 km "
	   "østover til fots, hvor gresshopperne " 
	   "ikke hadde gjort noen skade. "
	   "<br /> "
	   "<br /> "
	   "<u>Snøstormer</u> "
	   "<br /> "
	   "<br /> "
	   "Det siste dramatiske som skjer i boka er at det en hard vinter "
	   "kommer en rekke med snøstormer. "
	   "Bare noen dager før den site jula Laura skrev om i denne boka, "
	   "dro Pa en tur til byen, da det var den første klare dagen etter "
	   "en 3-dagers snøstorm. Pa fikk gjort det han skulle " 
	   "i byen og la ut "
	   "på veien hjem da han så en sky i nordvest. "
	   "Han gikk fortere og fortere nordover mot hjemmet deres til han " 
	   "til slutt nesten var i full spurt for å rekke hjem før "
	   "den neste snøstormen kom, men forgjeves. Han var ikke kommet noe "
	   "lenger enn halvveis da stormen inntraff. Han fortsatte bare å gå "
	   "for han visste at han ville fryse i hjel hvis han stoppet, selv "
	   "om han ikke kunne se armene sine foran seg. Han fortalte at han "
	   "gikk, gikk og gikk litt til, til han kjente at bakken under ham "
	   "ga etter. Etter et fall på 3-4 meter var han i ly for stormen. " 
	   "3 dager senere var storemn over, og etter å ha spist opp "
	   "julegavene til Laura og søstrene Mary og Carrie og en håndfull "
	   "med østers kunne han gå det som viste seg å være maks 100 meter, "
	   "hjem til familien. Det var julaften den dagen han kom hjem og "
	   "da de i senere bøker snakket om denne julen, snakket de bare "
	   "om 'the dreadful Christmas when Pa was gone'. De hadde helt "
	   "glemt at det var jul da han kom. "
	   "<br /> "
	   "<br /> "
	   "<b>Merknader</b> "
	   "<br /> "
	   "<br /> "
	   "1) I boka forteller Laura at hun begynner på skolen for "
	   "første gang. Dette stemmer ikke, da hun allerede har "
	   "gått på <i>The Barry Corner School</i> under oppholdet "
	   "i Wisconsin. "
	   "<br /> <br /> "
	   "2) Nellie Oleson er en karakter som er basert på 3 jenter. "
	   "I denne boka er karakteren basert på ei jente som het "
	   "Nellie Owens. De 2 andre 'Nelliene' er Genevieve Masters og "
	   "Stella Gilbert. Disse personene møter leserne i "
	   "<a href='books.php?book=Little+Town+on+the+Prairie'> "
	   "  'Little Town on the Prairie'</a> og  "
	   "<a href='books.php?book=These+Happy+Golden+Years'> "
	   "  'These Happy Golden Years' "
	   "</a><br /> <br />"
	   "3) Familien Oleson het i virkeligheten Owens; "
	   "Mr. Oleson het William Oleson, "
	   "Mrs. Oleson het Margareth Oleson, "
	   "Willie Oleson het i virkeligheten Willie Owens, og som nevnt "
	   "ovenfor het Nellie Oleson i dette tilfellet Nellie Owens. "
	   "4) I boka møter lesrne på hunden Jack. Sannheten er at "
	   "Jack ikke ble med da familien Ingalls dro fra Wisconsin til "
	   "Minnesota. Leserne likte ham så godt at Laura inkluderte "
	   "ham i boka.\");"))
	{
	  exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if(mysql_query(conn, "INSERT IGNORE INTO tbl_books VALUES(5, \"By the Shores of Silver Lake\", \"Det vesle huset langt mot vest\", 1939, 2004, \"Caroline Ingalls<br />Carrie Ingalls<br />Charles Ingalls<br />Laura Ingalls<br />Mary Ingalls\",\"Mr. Boast, Mrs. Boast, Docia Ingalls ('Aunt Docia'), 'Uncle Hi', Lena (Lauras kusine), Jean (Lauras fetter)\", \"Reverend Robert Alden ('Reverend Alden'), Almanzo Wilder, Royal Wilder, Mr. Nelson, Mr. Edwards\", 290,\"'By the Shores of Silver Lake' er den 5. boka i "
	   "'Little House'-bokserien av Laura Ingalls Wilder. "
	   "Handlingen finner sted et par år etter handlingen "
	   "i <a href='books.php?book=On+the+Banks+of+Plum+Creek'> "
	   "  'On the Banks of Plum Creek'</a>. " 
	   "<br /> "
	   "Boka begynner med familien som får skarlagensfeber. "
	   "Alle bortsett fra Laura og Charles blir syke; verst "
	   "gikk det utover Mary som mistet synet som en følge "
	   "av et hjernslag som igjen var en følge av denne "
	   "sykdommen. Samtidig kommer en tante fra 'the Big Woods' "
	   "ut for å spørre Charles om han vil jobbe for jernbanen "
	   "noen mil lenger vestover. Etter å ha diskutert dette med "
	   "Caroline, Lauras 'Ma', ble de enige om at Charles skulle "
	   "pakke kofferten og dra vestover, "
	   "og Laura, Carrie, Mary, Caroline "
	   "og den nyfødte yngstesøstera Grace skulle komme et par måneder "
	   "senere; når Mary var blitt frisk nok til at hun kunne dra. "
	   "Huden Jack, som vi har føtt følge hele veien fra 'the Big Woods' "
	   "(men som egentlig ble værende i Wisconsin " 
	   "da de dro til Minnesota), "
	   "dør i det første kapittelet i boka. "
	   "<br />"
	   "<br />"
	   "<b>Reisen vestover</b>"
	   "<br />"
	   "<br />"
	   "For Laura og familien ble reisen vestover " 
	   "til det som skulle vise "
	   "seg å bli deres 'permanente' bolig, todelt. Først skulle de "
	   "reise med tog til nabobyen Tracy hvor faren skulle 'plukke' "
	   "dem opp og frakte dem videre vestover med hest og vogn. "
	   "Dette var første gang Laura og familien hennes hadde reist med "
	   "et tog, og hun hadde ofte hørt om tog som ble ødelagte og folk "
	   "ombord som omkom. Dessuten hadde lokomotivene en toppfart på "
	   "30 miles, ca 50 kilometer i timen, hvilket var den samme "
	   "farten man hadde med hest og vogn per <i>dag</i>. "
	   "<br />"
	   "<br />"
	   "Dagen etter kom de frem til campingstedet der " 
	   "familiefaren jobbet. "
	   "Familiefaren jobbet i en butikk ved stedet der jernbanen ble "
	   "bygd og hadde ansvaret for å utbetale lønningene til de ansatte, "
	   "hvilket ikke alltid var like problemløst. "
	   "Den første lønninga ble utbetalt for 14. dagers arbeid "
	   "og ikke for en hel måned, hvilket ikke ble godt mottatt. "
	   "<br />"
	   "<br />"
	   "<b>Vinter og vår</b>"
	   "<br />"
	   "<br />"
	   "<table border='0'>"
	   "  <tr>"
	   "    <td valign='top' id='main'>"
		" Vinteren kom og jernbanefolkene jobbet seg ferdig. "
		 "Nå var det på tide å finne ly for kulda, " 
		 "og da flyttet de inn i "
		 "'The surveyor's house' - bygninginspektørens hus. " 
		 "Her bodde de gjennom den første vinteren i " 
		 "Dakota Territory. "
		 "Mange flyttet vestover og måtte " 
		 "overnatte i det samme huset "
		 "så familien så seg etterhvert nødt til " 
		 "å ta betaling for å la "
		 "folk få sove i huset. "
		 "Dette var også en fin måte å spare penger "
		 "slik at de kunne få sendt Mary på en skole for blinde. "
		 "<br />"
	       "</td>"
	       "<td valign='top'>"
		" <a href='javascript:openSurveyor();'>"
		 "  <img src='images/lauraingallswilder/surveyors_house.jpg' height=480 width=640 />"
		 "</a>"
		 "<div id='imgtxt'>"
		 "  The Surveyor's house hvor Laura og familien " 
		 "  hennes tilbrakte "
		 "  den første vinteren i De Smet. I dag ligger dette huset "
		 "  i den nordøstlige delen av senteret i De Smet. "
		 "</div> "
	       "</td> "
	     "</tr> "
	   "</table> "
	   "Mens dette foregikk, "
	   "dro Pa vest til Huron for å skaffe seg tomta "
	   "et gårdsbruk han hadde funnet. "
	   "<br />"
	   "<br />"
	   "Vinteren ble til vår, og snart var rushet "
	   "med de som flyttet "
	   "vestover over for denne gang. "
	   "Nå begynte Pa å bygge en bygning "
	   "i det som nå var blitt til byen "
	   "<a href='towns/de_smet.html'>De Smet</a>. "
	   "Dette måtte han gjøre fordi landmålerne "
	   "som opprinnelig brukte dette "
	   "huset, var i ferd med å komme tilbake. "
	   "<br />"
	   "Boka avsluttes med at Pa får panikk når han får høre at "
	   "noen nybyggere var blitt skutt og drept av en som stjal "
	   "den myrdedes eiendom (en såkalt 'claim jumper'). "
	   "Av frykt for at deres eiendom også skulle stjeles, "
	   "hastebygger Pa et lite hus på eiedommen hans, og bare "
	   "et par dager etter at nyheten om mordet hadde spredt seg, "
	   "flyttet familien ut til deres nye, lille hus ved Silver Lake.\");"))
	{
	  exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if(mysql_query(conn, "INSERT IGNORE INTO tbl_books VALUES(6, \"The Long Winter\", \"Det lille huset og den lange vinteren\",1940, 2004, \"Caroline Ingalls<br />Carrie Ingalls<br />Charles Ingalls<br />Laura Ingalls<br />Mary Ingalls\", \"Almanzo Wilder, Royal Wilder, Cap Garland\", \"Mr. Edwards, Mr. Fuller, Mr. Harthord, Mr. Boast, Mr. Bradley, Mr. Foster, Mary Power, Minnie Johnson, Arthur Johnson, Ben Woodworth, m.m.\", 334, \"'The Long Winter' "
	       "(norsk: 'Det lille huset og den lange vinteren'), "
	       "eller 'The Hard Winter', som var Lauras opprinnelige navn "
	       "(hun forandret på tittelen etter oppfordring fra forlaget.) "
	       "er den 6. boka i serien om 'Little House'. " 
	       "Fortellingen begynner "
	       "noen måneder etter at familien flyttet til det " 
	       "nye hjemmet sitt "
	       "utenfor De Smet, Sør-Dakota, som du kan lese om i "
	       "<a href='books.php?book=By+the+Shores+of+Silver+Lake'> "
	       "'By the Shores of Silver Lake' "
	       "</a>. I korte trekk handler denne boka om den hardeste "
	       "vinteren i hele Dakota-territorets historie "
	       "(Dakota-territoriet, eller Dakota Territory omfattet "
	       "i sin tid Nord-Dakota og "
	       "Sør-Dakota før de ble 'selvstendige' "
	       "delstater i 1890). "
	       "<br />"
	       "<br />"
	       "I de første kapitlene forteller Laura at hun og faren hennes "
	       "høyet, da faren hennes, Charles, forteller henne at det vil "
	       "bli en lang og hard vinter fordi bisamrottene bygde seg hus "
	       "med tykke vegger, hvilket ifølge Charles er et klassisk tegn "
	       "på en hard vinter, og dette året hadde de bygd de tykkeste "
	       "veggene han noensinne hadde sett. "
	       "<br />"
	       "I oktober samme år kom den første snøstormen tidligere enn "
	       "vanlig, og på grunn av dårlig isolasjon "
	       "bestemmer Charles seg "
	       "for at de skal flytte til byen før " 
	       "vinteren virkelig slo til. "
	       "I byen De Smet noen dager senere møtte Charles på en gammel "
	       "indianer som kom med en advarsel til dem: "
	       "<br />"
	       "Han holdt 7 fingre i luften for å advare om at hver 7. "
	       "vinter er av det litt kraftigere slaget. Når denne "
	       "7-års perioden ble gjentatt 3 ganger, ville vinteren bli "
	       "ekstra hard. På nytt holdt han 7 "
	       "fingre i luften; nå fortalte "
	       "han hvor mange måneder den 21. vinteren ville vare, "
	       "og denne kommende vinteren ville være vinter nr 21. "
	       "<br />"
	       "<br />"
	       "I dagene etter opplevde familien en periode med en "
	       "'Indian Summer' - en periode med varmt sommervær. "
	       "Charles på sin side hadde en følelse av at naturen "
	       "'planla' å slippe løs voldsomme krefter og fikk til "
	       "slutt overbevist kona Caroline om å flytte inn til byen. "
	       "<br />"
	       "<br />"
	       "<table border='0'>"
		" <tr>"
		     "<td valign='top' id='main'>"
		     "<b>Vinteren begynner</b>"
		     "<br />"
		     "<br />"
		     "En ettermiddag, noen dager "
		     "etter at de flyttet til byen "
		     "var Laura og lillesøstera Carrie på skolen da en storm "
		     "bygde seg opp. Læreren var nettopp kommet "
		     "østfra og hadde, "
		     "i motsetning til Laura og familien hennes, " 
		     "aldri opplevd en "
		     "kraftig snøstorm før. Hun ga elevene tidlig fri, "
		     "men før "
		     "hun nesten fikk sagt takk for i dag, " 
		     "slo stormen til med "
		     "tett snødrev og kraftig vind. " 
		     "Så og si alle elevene måtte "
		     "bare gjette på hvor de var hen og gå i rekke, " 
		     "tett innpå hverandre, "
		     "fordi ingen kunne se noen verdens ting. " 
		     "Man diskuterte og kranglet "
		     "om hvilken retning man skulle gå i, " 
		     "men noe motvillige ble man "
		     "til slutt enige og tuslet videre, " 
		     "inntil en av elevene "
		     "bokstavelig talt gikk på veggen. "
		     "Det viste seg at de var kommet "
		     "inn i byens ytterste kvartal; "
		     "hadde man gått noen få meter på "
		     "den andre veien som ble foreslått," 
		     "hadde man etter all sannsynlighet "
		     "gått seg vill og i verste fall ikke overlevd. "
		     "Dette var den siste "
		     "dagen på lenge som det ble arrangert skole. "
		     "<br />"
		     "Dager etter bestemmer Charles og andre menn, " 
		     "blant annet Mr. "
		     "Edwards (fra Det lille huset på prærien) " 
		     "seg for å brøyte "
		     "jernbanen mellom De Smet i Dakota og " 
		     "Tracy i Minnesota, fordi "
		     "innbyggerne i De Smet og andre byer lenger "
		     "vestover var avhengig "
		     "av matvarer og andre ting som måtte sendes " 
		     "vestover med tog. "
		   "</td>"
		   "<td valign='top' width='291'>"
		     "<a href='javascript:openTrainStuck();'>"
		       "<img src='images/lauraingallswilder/train_stuck_in_snow.jpg' height='396' width='291'></a>"
		     "<div id='imgtxt'>"
		      " Et tog som har kjørt seg fast i snøen i Minnesota, "
		       "vinteren 1880 "
		     "</div>"
		   "</td>"
		 "</tr>"
	       "</table>"
	       "Dette skulle vise seg å være en jobb som var forgjeves. " 
	       "Bare noen dager etter at de ble ferdige " 
	       "kom det en ny snøstorm. " 
	       "Slik fortsatte "
	       "det, og etterhvert ble lagrene mindre og " 
	       "mindre og priesene høyere "
	       "og høyere, både for mat, parafin og kull "
	       "som man brukte for å fyre med og å få varme. "
	       "Den siste gangen toget kommer i løpet av denne vinteren, " 
	       "er rett før jul. "
	       "<br />"
	       "<br />"
	       "Januar gikk uten at innbyggerne i De Smet fikk noen "
	       "former for matvarer og andre varer de trengte, "
	       "fordi fordi jernbaneoperatørene hadde bestemt " 
	       "at ingen tog skulle "
	       "passere vestover før vinteren var over. " 
	       "2- og 3-dagers snøstormer "
	       "kom tett i tett, mange ganger var det bare "
	       "én dag uten de kraftige "
	       "vindene. Ingalls-familien og de andre som bodde " 
	       "i byen levde på det "
	       "som var igjen av brunt brød og poteter. En dag sa Laura: "
	       "<br />"
	       "En dag i februar gikk det opp for henne hvor lite "
	       "hvete de hadde igjen. "
	       "Like før hadde Laura klaget på hvor lei hun var av " 
	       "å spise brunt brød uten noen ting på. " 
	       "Da så hun en pose i et hjørne på kjøkkenet hvor " 
	       "Ma hadde lagret hveten i og hvor tom den var. " 
	       "Laura spurte deretter om ikke " 
	       "Pa kunne kjøpe mer hvete. "
	       "Da sa Ma at det ikke var mer hvete igjen i byen. " 
	       "Laura spurte så om familien kom til å sulte, "
	       "men da sa Ma at om det var nødvendig, ville Pa slakte kua " 
	       "Ellen og en kvigekalv de hadde - til " 
	       "Lauras store fortvilelse. "
	       "<br />"
	       "<br />"
	       "Den dagen var Charles ('Pa' i sitatet ovenfor) ute og lagde "
	       "høyballer som de fyrte opp for å beholde varmen i huset. "
	       "På ettermiddagen, rett før kveldsmaten var klar, " 
	       "hadde han nyheter: "
	       "Et rykte hadde spredt seg i byen om at en bonde som bodde "
	       "ca 3 norske mil sør for byen, "
	       "hadde et lager med korn som innbyggerne i De Smet "
	       "sårt trengte for å unngå å sulte. "
	       "Alt de hadde igjen var brød til frokost og 6 poteter. "
	       "<br />"
	       "<br />"
	       "En dag bestemte Almanzo Wilder at noe måtte gjøres. "
	       "Han og Lauras klassekamerat Cap Garland trosset " 
	       "farene ved å forlate "
	       "byen og dra til den aktuelle gården for å sjekke om " 
	       "ryktene var sanne, "
	       "hvilket de også var. "
	       "Problemet var bare at han som eide gården, "
	       "ikke ville selge kornet. Almanzo og Cap ga sto også på sitt, "
	       "og fikk forhandlet seg fram til en pris for kornet; "
	       "1,25 dollar per bushel (ca 35 liter). "
	       "De kom tilbake til byen om kvelden; " 
	       "akkurat i det øyeblikket en ny "
	       "snøstorm slo til. "
	       "Dagen etter, da hveten skulle selges, " 
	       "ble man etter mye klabb og "
	       "babb (mr. Bushel, han som var 'ansvarlig' " 
	       "for å selge korn i byen "
	       "ville selge hveten for 3 dollar per bushel; "
	       "de som ville kjøpe hveten mente at det var urettferdig dyrt) "
	       "enige om at man skulle selge hveten etter rasjon, "
	       "etter hver families behov. De som var helt tom for hvete, "
	       "som f. eks. familien Ingalls, kunne kjøpe mye, mens Almonzo "
	       "og broren Royal ikke kjøpte noe fordi de hadde en del igjen. "
	       "<br />"
	       "<br />"
	       "Mars var over og april begynte, uten at stormene hadde noen " 
	       "planer om å gi seg; de var verre enn noen gang tidligere. "
	       "Mot slutten av april sa Charles at de ville ha nok høy til "
	       "å holde varmen i huset; takket være Laura og at Charles selv "
	       "ikke ville klart å lage nok høy til å vare vinteren igjennom "
	       "hvis han hadde gjort det alene. "
	       "<br />"
	       "<br />"
	       "<b>'Jul i mai'</b>"
	       "<br />"
	       "<br />"
	       "Natta etter lå Laura lys våken og hørte på vinden. " 
	       "Om kvelden snakket de om at stormene måtte gi seg " 
	       "og at stormene ikke kunne ta dem. "
	       "Vinden hun hørte blåste også kraftig, men hadde likvel "
	       "ikke det samme brølet som når snøstormene raste. " 
	       "Midt på natten raste hun opp og sa til Charles " 
	       "at Chinook-vinden blåste; "
	       "at vinteren var over, snøstormene hadde gitt opp, "
	       "og at våren endelig var kommet. "
	       "Mai var her og det første toget "
	       "siden jul skulle endelig komme. Dagen da det toget kom "
	       "samlet Ingalls-familien og familien Boast " 
	       "seg og spiste julemiddag; "
	       "våren var kommet og det ville de feire med " 
	       "en skikkelig julemiddag. "
	       "<br />"
	       "<br />"
	       "<b>'Forskjeller' mellom boka og virkeligheten</b>"
	       "<br />"
	       "<br />"
	       "<i>'The Long Winter'</i> handler om perioden fra høsten "
	       "1880 til våren 1881, en årstid med så mange kraftige "
	       "snøtstormer ('blizzards') at denne vinteren gikk inn i "
	       "historebøkene som 'snøvinteren'. Korrekte detaljer i Lauras "
	       "bok inkluderer navnene til de ulike innbyggerne, lengden "
	       "på vinteren, jernbanen som måtte stenges og " 
	       "nesten-hungersnøden som kom som en " 
	       "konsekvens av at jernbanen "
	       "ble stengt (som sitatet ovenfor viser), "
	       "den unormalt kalde kulden, den fryktelige faren "
	       "for å bli tatt av en kraftig snøstorm (de som ble tatt av "
	       "en slik storm, frøs som regel ihjel) og det motet som "
	       "Almanzo Wilder og Cap Garland viste da de satte sine egne "
	       "liv på spill da de dro ut på den åpne prærien "
	       "for å se etter hvete ingen var helt sikre på at eksisterte. "
	       "<br />"
	       "<br />"
	       "Den 'fiksjonelle' delen er det kapitlet " 
	       "hvor indianeren advarer "
	       "mot vinteren som er i vente, og denne " 
	       "'evigvarende 'prosesjonen'' "
	       "av snøstormer som i gjennomsnitt varte i " 
	       "23 dager med 2 til 2,5 "
	       "dagers mellomrom i perioden fra oktober til april. " 
	       "Historiske bevis skal ha det til at det var " 
	       "uvanlig mange stormer "
	       "den vinteren, men at Lauras ca 35 snøstormer var litt "
	       "overdramatisert. Dessuten viser research som forfattere bak "
	       "diverse biografier om Laura har gjort, at Almonzo Wilder og "
	       "Cap Garland ikke dro 20 miles (ca 3 norske mil), "
	       "men 12 miles (ca 2 norske mil). Den siste forskjellen mellom "
	       "boka og virkeligheten er Almanzos alder som i boka var satt "
	       "til å være 6 år, men i virkeligheten var Almonzo " 
	       "10 år eldre enn Laura. Bortsett fra disse "
	       "små forskjellene regnes 'The Long Winter' "
	       "som et nøyaktig portrett av den legendariske vinteren i "
	       "Dakota Territory.\");"))
	{
	  exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if(mysql_query(conn, "INSERT IGNORE INTO tbl_books VALUES(7, \"Little Town on the Prairie\", \"Ikke oversatt til norsk\", 1941, 2004, \"Caroline Ingalls<br />Carrie Ingalls<br />Charles Ingalls<br />Laura Ingalls<br />Mary Ingalls\", \"Mary Power, Ida Brown, Minne Johnson, Nellie Oleson, Mamie Beardsley\", \"Almanzo Wilder ('Young Mr. Wilder'), Eliza Jane Wilder ('Miss Wilder'), Reverend Brown, Charley, Arthur Johnson, Ben Woodworth, Clarence, Alfred, Mr. Clancy, Mrs. Clancy, Mr. Boast, Mr. Barker, Mr. Owen, Mr. Clewett, Mr. Hopp, Mrs. Tinkham, Mr. Tinkham, Mr. Foster, Mr. Bradley, Mr. Brewster, Mrs. Whiting, Mrs. White, Mrs. Boast, Mrs. Beardsley, Mrs. Jarley, Mrs. Woodworth\", 307, \"'Little Town on the Prairie' er den 7. " 
	   "boka i serien om 'Little House'. "
	   "Boka ble publisert for første gang i 1941, "
	   "og handlingen finner sted i perioden fra "
	   "sommeren 1881 til julaften 1882. "
	   "<br />"
	   "<br />"
	   "I boka leser vi om familiens forhåpninger om "
	   "å så sendt Mary som ble blind, på en skole for de "
	   "blinde i Vinton, Iowa. For å hjelpe familien med "
	   "å få råd til det tar Laura seg en jobb i byen "
	   "De Smet i dagens Sør-Dakota som går ut på å sy "
	   "klær. Hun misliker jobben, men klager likevel ikke; "
	   "for hver uke hun jobbet, tjente hun $1,50. "
	   "Til sammen ble det $9 før vårrushet var over og "
	   "hun ikke hadde mer å gjøre. Hjemme planter Charles "
	   "en avling som senere blir spist opp og ødelagt "
	   "av noen svarttroster. Selv om han får skutt mange "
	   "av dem, mister han likevel avlingen og Laura tror "
	   "at dette fører til at det ikke blir noe skole på "
	   "Mary likevel. Det er da Charles bestemmer seg for å "
	   "selge kvigekalven, og med de pengene han får fra "
	   "dette salget setter han, Caroline (Lauras 'Ma') og "
	   "Mary seg på toget i retning Iowa og skolen for de "
	   "blinde. " 
	   "<br />"
	   "Savnet etter Mary er stort, så for at hun og hennes "
	   "2 yngre søstre, Carrie og Grace skal få noe annet "
	   "å tenke på, setter de ignang med høstrengjøringa "
	   "på gården. Dette skulle vise seg å være en "
	   "utmattende uke, men de klarte såvidt å bli ferdige  "
	   "i tide. "
	   "<br />"
	   "Vinteren kom, og med den "
	   "<a href='books.php?book=The+Long+Winter'>"
	   "  forrige vinteren friskt i minnet"
	   "</a> "
	   ", bestemmer Charles seg for å ta med familien til "
	   "byen i tilfelle dette området skulla ha en annen "
	   "lunefull vinter på lur. Når skolen starter opp "
	   "igjen møter Laura på sine 'gamle' venninner "
	   "Minnie Johnson og Mary Power, og ei ny jente som "
	   "heter Ida Brown. En uønsket overraskelse får hun "
	   "når hun får se at en av uvennene hennes fra "
	   "Walnut Grove, 'Nellie Oleson', også var flyttet "
	   "til De Smet. Enda verre blir det når 'Nellie' "
	   "får deres nye lærer, Miss Eliza Jane Wilder "
	   "til å mislike Ingalls-jentene. "
	   "<br />"
	   "Det utviklet seg til å bli 'store' konflikter mellom "
	   "Eliza Jane og Carrie og Laura. En høstdag ble Carrie "
	   "sittende og vippe på stolen fordi hun ikke rakk helt "
	   "ned til gulvet. Eliza Jane sa at Carrie gjerne måtte "
	   "fortsette, men gjøre det litt høyere. Hun fortsatte "
	   "å mobbe Carrie; Laura fikk nok, gikk bort til "
	   "Carries pult og vippet den så hardt og så fort "
	   "at det ble umulig for de andre studentene å  "
	   "konsentrere seg. Til slutt ga læreren på mange måter "
	   "etter og sendte Carrie og Laura hjem for resten av dagen "
	   "('excuse'). Det var bare én type straff som var værre "
	   "og det var å bli utvist ('expelled'). Ingen av elevene "
	   "trodde det, men dagen etter dukket Carrie og Laura opp "
	   "igjen. De andre studentene hadde også fått nok, "
	   "og sammen gjorde de alt de kunne for å gjøre "
	   "lærertilværelsen værst mulig. Dette var ikke Lauras "
	   "vilje, men nå var konflikten mellom Eliza Jane og "
	   "elevene gått så langt at skolestyret ble satt på saken "
	   "og de erklærte sin fulle støtte til Eliza Jane. "
	   "Eliza Jane underviste på skolen i De Smet i 2 "
	   "måneder, og etter dette kom hun ikke tilbake igjen. "
	   "<br />"
	   "<br />"
	   "Vinteren som kom var en 'virvel med lystighet' med "
	   "samfunnsmøter, fester og kirkefester. "
	   "For Laura var dette positive ting, men egentlig "
	   "var hun deperimert; hun savnet Mary og som en "
	   "følge av det mistet hun all interesse i å studere; "
	   "fram til den påfølgende sommeren neglegerte hun "
	   "alt som het studier og skolearbeid, men da sommeren "
	   "kom brukte hun sommertiden til å studere så mye hun kunne. "
	   "Da den neste vinteren kom, ble hun med Almanzo Wilder "
	   "på kirkemøter og på en skoleutstilling. "
	   "På lille julaften hadde alle elevene på skolen i De Smet "
	   "invitert foreldre og kjente til en skoleutstilling i byen. "
	   "Alle elevne fikk hver sin oppgave som de måtte løse "
	   "i de ulike fagene; først kom geografi, deretter gramatikk "
	   "og setningsanalyse (de hadde ikke noen tavler, så elevene "
	   "analyserte oppgavesetningen i hodet). Deretter var det "
	   "hoderegning; aritmetikk* var ikke Lauras favorittfag. "
	   "Oppgaven Laura måtte løse i hodet var: 347264/16 - "
	   "'Divider 347264 med 16'. Sikker på å mislykkes som hun "
	   "var, gikk hun gjennom hele oppgaven del for del og "
	   "til hennes store forbauselse, kom hun frem til riktig "
	   "svar: 21704. Da det var over, var det de unge, blant "
	   "annet Carrie som skulle opp på scenen for å fremføre " 
	   "ulike dikt de hadde øvd på. Deretter skulle "
	   "Laura og Ida presentere den amerikanske historien fra " 
	   "Christopher Columbus og frem til denne dagen i 1882. "
	   "<br />"
	   "Boka avsluttes på julaften 1882. Den dagen fikk familien "
	   "et overraskende besøk fra Mr. Brewster. Han var kommet "
	   "fordi en skole som han hadde startet ca 2 norske mil "
	   "sør for De Smet, trengte en lærer, og selv om Laura "
	   "<i>egentlig</i> ikke var gammel nok, "
	   "mente han at hun var den best kvalifiserte, "
	   "basert på denne skoleutstillingen som fant sted "
	   "på lille julaften. Laura skrev i boka at hjertet "
	   "hennes sank ganske mye - 'så langt hjemmefra "
	   "sammen med fremmede?' Hun kviknet litt til da hun "
	   "fikk høre lønna; $40 for 2 måneders arbeid. "
	   "Mr. Brewster sa at hun ikke trengte å bekymre seg "
	   "for at hun var 2 måneder yngre enn det tillatte; "
	   "hun trengte ikke å si hvor gammel hun var hvis "
	   "ingen spurte henne. Laura takker ja til jobben "
	   "og Mr. Brewster gikk og hentet fylkeskolesjefen "
	   "Mr. Williams. Han fortalte at han også hadde " 
	   "hørt på henne på skoleutstillingen og at han " 
	   "var så imponert at "
	   "han ikke trengte å ta en skikkelig prøve på henne, "
	   "men siden penn og papir allerede lå klart, "
	   "gjennomgikk de noe av pensumet som måtte til "
	   "for å kunnne få et lærersertifikat. "
	   "Hun gjennomgikk aritmetriske* oppgaver, hun stavet, "
	   "besvarte geografispørsmål, leste Marc Antonys høytidelige "
	   "tale om Cæsars død og analyserte én setning før "
	   "Mr. Williams bestemte seg. Laura hadde bestått "
	   "prøven og noen minutter etter leste hun gjennom "
	   "et 3. grads lærersertifikat. Hun var nå autorisert "
	   "til å undervise i lesing, ortografi**, skriving, "
	   "aritmetikk*, geografi, engelsk gramatikk og historie. "
	   "Boka avsluttes ved at Laura sier at Mary nå kan "
	   "få alt det hun trenger og at hun kan komme hjem "
	   "på ferie neste sommer. "
	   "<br />"
	   "<br />"
	   "Hvordan denne jobben gikk og hva som skjer videre i "
	   "Lauras liv kan du lese mer om i "
	   "<a href='These+Happy+Golden+Years'>"
	   "  'These Happy Golden Years'"
	   "</a>"
	   "<br />"
	   "<br />"
	   "<b>Merknader</b>"
	   "<br />"
	   "<br />"
	   "I boka snakker Laura om 'Nellie Oleson'. Det er verdt "
	   "å merke seg at 'Nellie Oleson' er et bilde på 3 ulike "
	   "personer - i denne boka er det snakk om ei som het "
	   "Genevieve Masters - ei jente hun traff på mens Laura "
	   "bodde i Walnut Grove for andre gang (etter å ha tilbragt "
	   "et år i Burr Oak, Iowa). En annen merknad er at Laura "
	   "jobbet 12 timer om dagen for å tjene nok penger til at "
	   "Mary kunne kjøpe det hun trengte før skolen for de blinde "
	   "startet - de folkevalgte i Dakota-territoriet betalte "
	   "skolepengene for de som var blinde og som skulle "
	   "begynne på Iowa School for the Blind i Vinton, Iowa, "
	   "hvis han/hun var innbygger i Dakota Territory. "
	   "I kapittelet 'Unexpected in December' skriver Laura om en "
	   "person som heter Lew Brewster (vi møter på ham i den neste boka "
	   "som heter"
	   "<a href='These+Happy+Golden+Years'>"
	   "  'These Happy Golden Years'</a>. "
	   "I virkeligheten het han Louis Bouchie."
	   "<br />"
	   "<br />"
	   "<b>Ordforklaringer</b>"
	   "<br />"
	   "<br />"
	   "<i>Aritmetikk</i> = læren om tallene og deres egenskaper; "
	   "læren om tallregningsmetoder (brøkregning, potensering, "
	   "rotutdragning og logaritmeregning)"
	   "<br />"
	   "<i>Ortografi</i> = rettskrivning\");"))
	{
	  exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if(mysql_query(conn, "INSERT IGNORE INTO tbl_books VALUES(8, \"These Happy Golden Years\", \"Ikke oversatt til norsk\", 1943, 2004, \"Caroline Ingalls<br />Carrie Ingalls<br />Charles Ingalls<br />Laura Ingalls\", \"Mr. Brewster, Mrs. Brewster, Mary Power, Ida Brown, Minnie Johnson, Nellie Oleson, Mary Amelia Ingalls, Almanzo Wilder\", \"Mr. Boast, Mr. Clewett, Mr. Fuller, Mr. McKee, Mr. Oleson, Mr. Owen, Mr. Wilkin, Mr. Williams, Mrs. Boast, Mrs. Brown, Mrs. McKee, Mrs. Power, Chad Brewster, Ruby Brewster, Tommy Brewster, Charles Harrison, Martha Harrison, Tom Ingalls ('Uncle Tom'), Florence Wilkins\", 289,\"'These Happy Golden Years' er den 8. " 
	  "og siste boka som Laura selv ga ut "
	  "i serien om 'Little House'. Boka starter opp bare "
	  "et par uker etter at "
	  "<a href='books.php?book=Little+Town+on+the+Prairie'> "
	  "  'Little Town on the Prairie'"
	  "</a> "
	  "sluttet. Fortellingen starter med at Pa kjører en usikker Laura "
	  "ut til nybyggerstedet Brewster, ca 2 norske mil sør for byen "
	  "De Smet, Dakota Territory. Laura er usikker både på det å "
	  "være hjemmefra og det med å begynne på en ny jobb, men Pa "
	  "trøster henne med å si at så lenge hun tenker før hun snakker, "
	  "er det ingenting som vil gå galt. Pa sa også at det var viktig "
	  "at hun tenkte litt over det han sa, fordi hun hadde en tendens "
	  "til å handle eller snakke før hun tenkte. Dessuten var hun bar e"
	  "15 år gammel - og gikk på skolen selv. Laura hadde bestemt seg "
	  "for å fullføre jobben; hun ville tjene de $40 hun var blitt "
	  "lovet hvis hun fullførte jobben, fordi det ville hjelpe "
	  "storesøstera Mary som gikk på en skole for de blinde i Iowa. "
	  "<br />"
	  "<br />"
	  "Etter å ha lest hva hun skrev om den første jobben, "
	  "kan man ikke si at hun trivdes. Brewster-familien var "
	  "en ytterst ulykkelig familie som hadde 1 gutt. "
	  "Huset de bodde i besto av 2 rom; Én stue og ett soverom, "
	  "så Laura tilbragte nettene på en sofa. Det var mye krangel "
	  "i familien, og måten krangelen foregikk på gjorde at Laura "
	  "ønsket seg vekk derfra så fort som mulig. "
	  "Ei spesiell natt skilte seg ut på en negativ måte fra de andre. "
	  "Laura våknet opp midt på natta av at " 
	  "Mrs. Brewster ropte at mannen "
	  "sparket henne , og til sin forskrekkelse "
	  "så hun Mrs. Brewster holde en kniv mot mannen. Mr. Brewster sa "
	  "at han ikke hadde sparket henne, men at han kom til å gjøre det "
	  "hvis hun ikke gikk tilbake på kjøkkenet "
	  "og la tilbake slaktekniven ('butcher knife'). " 
	  "<br />"
	  "Skolen gikk heller ikke så mye bedre. Noen av studentene "
	  "var eldre enn henne, og de gjorde alt de kunne for å sette "
	  "henne på en skikkelig prøve. Etterhvert fikk hun kontroll "
	  "på elevene (som blant annet stakk kniver i håret til hverandre) "
	  "og ble en mye mer selvsikker lærer, og selv om hun hadde sine "
	  "tvil, fullførte hun jobben og tjente disse $40. "
	  "<br />"
	  "<br />"
	  "Når den første uka gikk mot slutten hadde Laura et stille ønske "
	  "om at Pa skulle hente henne slik at hun i "
	  "det minste kunne være hjemme "
	  "om helgene. Men til Lauras store overraskelse og lettelse, "
	  "var det Almanzo Wilder som hentet henne. Laura og Almanzo "
	  "ble kjent med hverandre i perioden som ble omtalt under "
	  "'Lttle Town on the Prairie'. Almanzo var " 
	  "allerede blitt glad i henne, "
	  "og han visste at hun hadde hjemlengsel " 
	  "og ønsket å lette på denne "
	  "ved å ta henne med hjem til familien hennes i De Smet hver helg, "
	  "også når temperaturen krøp til under -40°, en temperatur "
	  "hvor det var galskap å begi seg ut på en tur som denne og "
	  "tilbake til familien Brewster på søndag. "
	  "<br />"
	  "<br />"
	  "Etter at disse 2 månedene var forbi og hennes første jobb "
	  "som lærer var over, fortsatte forholdet mellom Laura "
	  "og Almanzo å utvikle seg. Turer med hest og slede om vinteren "
	  "ble til turer med hest og vogn om våren, og én dag "
	  "imponerte Laura Almanzo ved å hjelpe til med å roe ned "
	  "hans mildt sagt temperamentsfulle og voldsomme hester. "
	  "Opptil flere ganger sa foreldrene til Laura at han "
	  "nesten prøvde å 'brekke nakken hennes' - noen ganger "
	  "måtte hun hoppe på og av vogna mens den var i bevegelse "
	  "fordi Almanzo ikke klarte å få hestene til å stå stille "
	  "lenge nok til at hun kunne komme seg av og på på en "
	  "'normal' måte. "
	  "<br />"
	  "'Nellie Oleson' dukker også opp i denne boka. En søndag "
	  "som Almanzo skulle ta med seg Laura på en tur med hest og vogn "
	  "stoppet han og tok med seg 'Nellie' - til Lauras store "
	  "overraskelse. Laura får hestene inn i en vill galopp "
	  "som skremmer henne så mye at hun mister viljen til å "
	  "bli med på flere turer, og på skolen fortsetter "
	  "fiendeskapet mellom 'Nellie' og Laura og de andre jentene. "
	  "<br />"
	  "<br />"
	  "Når sommeren nærmer seg får familien besøk av Ma sin bror, "
	  "onkel Tom som hadde vært på et mislykket gullrush. "
	  "Laura blir nå med en sydamen Mrs McKee og hennes datter "
	  "for å 'holde på' huset McKees familie hadde bygd, for å "
	  "følge loven som krevde at tomta de kjøpte fra regjeringa "
	  "skulle være bebodd i minst 6 måneder i året. "
	  "Når den første sommeren i boka endelig kommer, kommer "
	  "også Mary hjem på en ferietur fra skolen. "
	  "Gleden var stor over Marys hjemkomst, og savnet var på "
	  "nytt stort etter at hun dro tilbake. "
	  "<br />"
	  "<br />"
	  "I løpet av høsten vokste økonomien til Lauras familie "
	  "såpass at Pa kunne selge kua. For hengene han fikk for den "
	  "kjøpte han en symaskin til Caroline (Lauras 'Ma'). "
	  "Laura på sin side tok en ny jobb som lærer og sydame, "
	  "og for pengene hun tjente kjøpte Pa et orgel som Mary "
	  "kunne spille på neste gang hun kom hjem fra skolen "
	  "(på skolen for de blinde lærte Mary å spille på et orgel). "
	  "Lauras skuffelse var stor da Mary skrev at hun ville "
	  "tilbringe sommeren hjemme hos foreldrene til Blanche. "
	  "Det eneste som var positivt denne uka, var at Almanzo "
	  "kom for å ta henne med på en tur med hest og vogn. "
	  "<br />"
	  "<br />"
	  "Senere i boka inviterer Almanzo Laura på en sangskole "
	  "som fant sted sommeren etter. Etter sangskolens siste dag "
	  "spør Laura om hun ville godta ringen hans, og Laura sa "
	  "at det kom an på hva slags ring det var. Søndagen etter "
	  "kom han med ringen - fridde - og fikk ja. "
	  "<br />"
	  "<br />"
	  "Mary kom hjem denne sommeren, til Lauras store glede, "
	  "og stor var Marys overraskelse da hun fikk 'se' orgelet "
	  "som ventet på henne. Laura gledet seg over å være sammen "
	  "med henne hver dag igjen. Ma ble derfor overrasket da " 
	  "Laura sa at hun skulle ta seg en ny jobb i byen. "
	  "Laura argumenterte med at hun kunne være sammen med "
	  "Mary om ettermiddagene."
	  "<br />"
	  "<br />"
	  "Månedene gikk og Almanzo sa "
	  "at han og broren hans måtte dra til Minnesota "
	  "denne vinteren pga noen problemer med familien. "
	  "Laura regnet med at dette ville bli ei jul uten "
	  "Almonzo, men til hennes store overraskelse dukket "
	  "han opp og tilbragte jula sammen med Laura og familien. "
	  "<br />"
	  "I løpet av den påfølgende våren tok "
	  "Laura sin siste lærereksamen. "
	  "Lauras lærer hadde "
	  "ønsket at hun takket nei til lærertilbudet; "
	  "hadde hun gjort det, ville hun hatt muligheten "
	  "til å kunne ta den avsluttende eksamen og dermed "
	  "hatt muligheten for en høyere utdannelse. Tiden gikk "
	  "og Laura fullførte det som skulle bli hennes siste "
	  "jobb som lærer. Nå som sommeren på nytt var kommet, "
	  "fikk de også vite at Dakota Territory også kunne ha "
	  "noen lunefulle krefter om sommeren, da en kraftig "
	  "sommerstorm raste gjennom De Smet og andre byer i området. "
	  "Når denne var over, og Mary var dratt tilbake til "
	  "skolen i Iowa (hun tilbragte denne sommeren sammen "
	  "med Laura), var det på tide å planlegge bryllupet. "
	  "Almanzo hadde 'dårlige' nyheter - Almanzos søster "
	  "Eliza Jane som var Lauras lærer og Almanzos mor "
	  "ønsket et stort kirkebryllup som verken Almonzo, "
	  "Laura eller noen av Lauras foreldre ville hatt "
	  "råd til. Så det ble til at Laura og Almanzo "
	  "dro alene til Reverend* Brown og med Ida Brown "
	  "(ei venninne fra skolen der Laura var elev) og "
	  "hennes kjæreste som vitner, giftet de seg. "
	  "Når denne seremonien var over, dro de tilbake "
	  "til foreldrene for en bryllupsmiddag. Laura fortalte "
	  "at Ma hadde laget en av hennes mange, deilige "
	  "middager, men at både maten og kakene etter "
	  "smakte tørt og smakløst fordi hun innså at hun "
	  "ikke skulle bo sammen med foreldrene hennes igjen. "
	  "Til slutt forteller Laura hvordan det nye huset "
	  "hun skulle bo, var. Alt som var der, var deres. "
	  "Boka avsluttes med at Almanzo sier at det er en "
	  "nydelig natt. Laura svarte med å si at det er "
	  "en nydelig verden. I minnet hadde Laura "
	  "stemmen til Charles som sang "
	  "(her angitt med hele teksten; i avslutninga "
	  "av boka gjengir hun bare 'Golden years are passing by, "
	  "these happy golden years'). Sangen det refereres til "
	  "handler om å se på og prøve å huske positive ting "
	  "du har opplevd når du er lei deg: "
	  "<br />"
	  "<br />"
	  "<b>Golden Years are Passing By</b>"
	  "<br />"
	  "<br />"
	  "Golden years are passing by,"
	  "<br />"
	  "Happy, happy golden years,"
	  "<br />"
	  "Passing on the wings of time,"
	  "<br />"
	  "These happy golden years."
	  "<br />"
	  "Call them back as they go by,"
	  "<br />"
	  "Sweet their memories are,"
	  "<br />"
	  "Oh, improve them as they fly," 
	  "<br />"
	  "These happy golden years."
	  "<br />"
	  "<br />"
	  "Chorus:"
	  "<br />"
	  "Golden years, golden years"
	  "<br />"
	  "Happy golden years"
	  "<br />"
	  "Oh, improve them as they fly"
	  "<br />"
	  "These Happy Golden Years"
	  "<br />"
	  "<br />"
	  "Golden years are passing by,"
	  "<br />"
	  "Precious precious golden years"
	  "<br />"
	  "let no idle hour be spent"
	  "<br />"
	  "With sorrow, grief and tears"
	  "<br />"
	  "Ah! The good we all may do"
	  "<br />"
	  "As the moments pass"
	  "<br />"
	  "To your nobler self be true"
	  "<br />"
	  "Reward will come at last"
	  "<br />"
	  "<br />"
	  "Chorus"
	  "<br />"
	  "<br />"
	  "Golden years are passing by"
	  "<br />"
	  "Fleeting, fleeting swiftly on"
	  "<br />"
	  "Life is but a passing hour"
	  "<br />"
	  "Before we know 'tis gone"
	  "<br />"
	  "Soon the parting time will come"
	  "<br />"
	  "Day by day it nears"
	  "<br />"
	  "Have you done your duty well"
	  "<br />"
	  "These happy golden years?"
	  "<br />"
	  "<br />"
	  "<i>Sangen ovenfor er skrevet av Will L. Thompson</i>"
	  "<br />"
	  "<br />"
	  "<b>Historisk bakgrunn</b>"
	  "<br />"
	  "<br />"
	  "Ifølge Wikipedia var Lew Brewsters egentlige navn Louis Bouchie. "
	  "Navnene til Bouchie og Nellie Oleson var de eneste navnene "
	  "Laura endret på fordi dette var folk laura opplevde " 
	  "som uhyggelige "
	  "og Laura ønsket ikke å henge dem ut i bøkene sine. "
	  "<br />"
	  "Ser man på dagens kart over Sør-Daktoa ligger byen Carthage "
	  "på det stedet Laura beskrev som nybyggerstedet Brewster. "
	  "I dag vet man ikke om Carthage har vokst ut av dette "
	  "nybyggerstedet, eller om det 'kom til' senere. "
	  "<br />'Nellie Oleson' er i denne boka et bilde på 2 personer: "
	  "Genevieve Masters (som hun gikk sammen med på skolen) " 
	  "og Stella Gilbert (hun som ble så skremt av hestene) "
	  "<br />"
	  "Bokas tittel er hentet fra linje nr 2 i sangteksten ovenfor."
	  "<br />"
	  "<br />"
	  "<b>Ordforklaring</b>"
	  "<br />"
	  "<br />"
	  "Reverend = Pastor\");"))
	{
	  exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if(mysql_query(conn, "INSERT IGNORE INTO tbl_books VALUES(9, \"The First Four Years\", \"Ikke oversatt til norsk\", 1972, 2004, \"Almanzo Wilder ('Manly'), Laura Ingalls Wilder, Rose Wilder\", \"Charles Ingalls, Caroline Ingalls\", \"Mr. Boast, Mr. Bowers, Mr. Brown, Mr. Larsen, Mr. Mathews, Mr. Sheldon, Mr. Webb, Mr. Whitehead, Mrs. Boast, Mrs. Power, Peter Ingalls ('Cousin Peter')\", 134, \"'The First Four Years' er den siste 'Little House'-boka som er "
	   "skrevet av "
	   "Laura Ingalls Wilder. Boka forteller om de "
	   "4 første årene etter at "
	   "Laura giftet seg med Almanzo. "
	   "Dette skulle vise seg å være 4 tøffe år for dem; "
	   "alt tenkelige som kunne gå galt, "
	   "gikk galt: tornadoer, husbrann, fødselen av en "
	   "sønn som døde noen dager etter og alvorlig sykdom. "
	   "<br />"
	   "<br />"
	   "Verdt å merke seg er at denne boka ble publisert slik "
	   "Laura skrev den (i motsetning "
	   "til de andre 8 bøkene som er blitt redigert av dattera Rose). "
	   "Dessuten tar denne boka "
	   "opp temaer hun selv ikke ville skrive om i "
	   "de andre bøkene fordi Laura mente at "
	   "flere av disse temaene (særlig brann, katastrofer og død), "
	   "så derfor er man usikre "
	   "på om denne boka <i>egentlig</i> var ment som en 9. "
	   "bok i serien, eller som en "
	   "enkeltstående bok for voksne lesere. "
	   "Boka står riktignok oppført som den "
	   "9. boka i serien. "
	   "<br />"
	   "<br />"
	   "Boka begynner der "
	    "<a href='books.php?book=These+Happy+Golden+Years'>'These Happy Golden Years'</a> "
 	   "sluttet -- "
	   "med bryllupet mellom Laura "
	   "og Almanzo. Laura gir klart uttrykk for at hun "
	   "<b>ikke</b> vil være noen gårdskone, "
	   "men Almanzo får etterhvert overtalt " 
	   "henne til å prøve det i 3 år. "
	   "Det første året går forholdsvis problemfritt. "
	   "<br />"
	   "<br />"
	   "Det andre året begynner med at Laura og Almanzo "
	   "flytter inn i et nytt hjem. "
	   "Dette skjedde den 25. august 1886, "
	   "ett år etter bryllupet. I desember føder Laura "
	   "dattera Rose i en alder av 19 år. "
	   "Her beskriver hun hvordan "
	   "fødselen var, med smertefulle rier. "
	   "Noe senere gjorde Mr Boast en 'tilnærming' av "
	   "det sjeldne slaget. Siden Mr. og Mrs. "
	   "Boast ikke kunne få barn selv, ba han Laura "
	   "om å bytte barnet med Boast-familiens beste hest! "
	   "<br />"
	   "<br />"
	   "Det 3. året begynner med det Laura trodde var en forkjøelse, "
	   "men som heller viste "
	   "seg å være stygt tilfelle av difteri. "
	   "Almanzo hjalp til med å ta seg av henne så godt "
	   "han kunne, men det var før han selv ble syk av den "
	   "samme sykdommen. Lauras tilfelle "
	   "var av det farlige slaget, Almanzo var ikke så hardt angrepet, "
	   "men hardt nok til at "
	   "han fikk beskjed om å holde senga. Det rådet fulgte han ikke, "
	   "og dette førte til at "
	   "han ble 'lettere paralysert' pga det legene i De Smet kalte for "
	   "'overanstrengelse for kort tid etter difteriet'. "
	   "<br />"
	   "<br />"
	   "Det 3. året gikk forbi og det fjerde begynte. "
	   "I tillegg til problemene som var nevnt "
	   "ovenfor, slo avlingene feil, gjerne pga for mye tørke. "
	   "Likevel klarte Almanzo å få "
	   "Laura til å fortsette med gårdsarbeidet i ett år til. "
	   "Dette året dreide seg mest "
	   "om præriebranner. Den 5. august fødte Laura en sønn. " 
	   "Men gleden var kortvarig; "
	   "3 uker etter fødselen fikk den nyfødte sønnen kramper "
	   "og døde innen doktoren rakk "
	   "å komme frem. I tillegg, bare noen dager etter dette "
	   "tok kjøkkenet "
	   "(og etterhvert resten av huset) fyr under matlaging "
	   "og brant helt ned.\");"))
	{
	  exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	mysql_close(conn);
}	
void insertSeasons()
{
  char errorString[100] = "MySQL error: ";
  MYSQL *conn;
  char *server = "localhost";
  char *userName = user;
  char *passwd = password;
  char *database = "little_house";
  conn = mysql_init(NULL);
  if(conn == NULL)
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  if(!mysql_real_connect(conn, server, userName, password, database, 0, NULL,0))
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_season values(0,\"Pilot\",\"The pilot movie\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_season values(1,\"Season 1\",\"The first season (1974-1975): The year was 1877, the rush for land was on, and among the many who sought a new life in the new land were the Ingalls; Charles, his young wife; Caroline, and their three daughters; Mary, Laura and Carrie. Packing their few belongings into a wagon, they said goodbye to friends and relatives and joined the trek westward that would lead them to their new home in Plum Creek, on the plains of Minnesota. The Ingalls, pursuing the American dream, come to realise that they will have to fight for every inch of soil they turn...for every foot of ground they plant. Fight against desease, nature, local prejudices, and the rigours of a hostile evironment. The episodic adventures of the INgalls family are based on the rememberances of the late Laura Ingalls Wilder, whose 'Little House' books paint a realistic picture of pioneer life on the western fringes of the country over 100 years ago.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_season values(2,\"Season 2\",\"The second season (1975-1976): Charles must work at several jobs to pay off their debts the entire family pitches in -- Laura makes a new friend and helps him get over his grief -- Charles promises a dying widow the he will care for her three children -- Walnut Grove sees the opening of its first bank -- Mary becomes the pride and joy of the town. The sensitive subject of drug abuse is addressed in the second to last episode entitled 'Soldier's return'.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_season values(3,\"Season 3\",\"The third season (1976-1977): Mary and John fall deeply in love and must take serious decisions about their future -- Laura demonstrates tremendeous courage when Charles is critically wounded on a hunting trip -- Carrie wanders off and narrowly avoids tragedy when she is rescued from a mine shaft -- A child, initially rejected by his grandfather because his father was an Indian, earns his grandfather's respect -- Important lessons are learned when a young child comes to stay with the Ingalls -- With their crops destroyed, Charles decides to take his family to seek their fortune in the gold mines with disturbing results...\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_season values(4,\"Season 4\",\"The fourth season (1977-1978): A trip to Chicago makes Charles and Mary appreciate their home -- Laura and Mary witness the drowning of a friend -- Andy and Laura become crime investigators -- Outlaw, Jesse James, and his brother hide out in Walnut Grove -- Nellie falls in love and makes wedding plans -- Laura finds a mysterious message that leads her to an abandoned baby -- Charles interits some money from his relative -- Caroline becomes pregnant with their fourth child -- The Ingalls are devestated by the news that Mary is going blind\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_season values(5,\"Season 5\",\"The fifth season (1978-1979): The Ingalls move to Winoka to be near Mary. They manage a hotel and meet Albert for the first time -- After several months away, Charles and the family return to their home by Plum Creek and set to work restoring Walnut Grove -- Mrs. Oleson takes an interest in journalism -- Mary has second thoughts about marrying Adam -- Nellie Oleson is asked to tutor a boy and reveals her 'secret' for achieving good grades -- Albert becomes an apprentice and learns an important lesson about loyalty and friendship -- Charles is asked to help save a marriage -- Laura and Albert run away from home to help their terminally ill friend Dhillon achieve his life-long dream\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_season values(6,\"Season 6\",\"The sixth season (1979-1980): Almanzo Wilder comes to Walnut Grove with his sister Eliza-Jane, the new schoolteacher -- The Ingalls decide to adopt Albert but run into resistance from the boy's father -- Nels Oleson is reunited with his enstranged sister when the sircus comes to town -- A faith healer convinces the citizens of Walnut Grove to trust him, with tragic results -- Caroline's father discovers a talent as a stortyteller while grieving after the loss of his wife -- Laura and Mary are held captive by escaped convicts until Charles, impersonating as a doctor disarms the criminals -- Albert and a friend accidentally set fire to the blind school -- Almanzo asks Charles for Laura's hand in marriage, but is not overjoyed when he gets his answer.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_season values(7,\"Season 7\",\"The seventh season (1804-1981): The season starts with Laura and Almanzo's much-anticipated wedding. The Garveys move to Sleepy Eye to run a business -- Laura suspects Almanzo of having an affair with her friend -- Almanzo and Mr. Ingalls expand their business to Sleepy Eye -- Adam's sight returns. He and Mary move back to Walnut Grove and set up a law practise -- Mrs. Oleson leads the women in favour of a referendum concering fair property rights for married women -- Mr. Percival and Mrs. Oleson disagree very strongly on the subject of their grandchild's upbringing -- Mrs. Oleson takes over as teacher after Laura quits -- Albert falls in love with Sylvia and faces many difficult challenges -- Cassandra and James become orphans after thei parents are killed in an accident. Charles considers making them part of his family.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_season values(8,\"Season 8\",\"The eighth season (1981-1982): Nellie and Persival must move to New York and the Oleson's adopt Nancy. Dr Ledoux moves to Walnut Grove and prove, beyond a doubt, that he deserves the community's respect. Charles and Nels become conserned when the children of the town are influneced by a daredevil to attempt dangerous stunts. Mr. Edwards loses his son and enlists the aid of Charles to investigate the real circumstances behind his death. The Ingalls and the Wilders share cherished memories when they are snowed in at Christmas. Charles and Caroline risk losing James and Cassandra wehn an cuncle fills in for custody of the children. Laura and Almanzo's budding marriage faces serious difficulties following Almanzo's terrible stroke. When James is shot lapses into a coma, Charles turns to his faith in order to save his adopted son.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_season values(9,\"Season 9\",\"The nineth season (1982-1983): The Ingalls leave Walnut Grove and the Carters move into their old house -- Royal is terminally ill, and Jenny tries to drown herself after his death -- Herriet makes Nels run for mayor and tries to rename the town to Olesonville -- A man facing financial ruin loses his mind and shoots his wife and daughter -- The Wilders befirend a wild boy who escaped from a traveling sideshow. Mr. Edwards fights the sideshow owner for custody of the boy -- Nellie returns to Walnut Grove and Nancy runs away since she's no longer the center of attention -- Jenny must learn to walk and talk again after nearly drowning -- Mr. Edwards is held for ransom -- Laura faces a dilemma when she wins a book-writing contest -- Albert returns from the city and goes through morphine withdrawal -- Laura blames Doc for the loss of her newborn baby -- Mr. Edwards makes friends with an orangutan -- Willie gets engaged, upsetting his mother\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_season values(10,\"Season 10\",\"The tenth season (1983-1984): 3 movies that were shot to conclude the television series: 'Look Back to Yesterday', 'Bless All the Dear Children' and 'The Last Farewell'\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
}
void insertEpisodes()
{
  char errorString[100] = "MySQL error: ";
  MYSQL *conn;
  char *server = "localhost";
  char *userName = user;
  char *passwd = password;
  char *database = "little_house";
  conn = mysql_init(NULL);
  if(conn == NULL)
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  if(!mysql_real_connect(conn, server, userName, password, database, 0, NULL,0))
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(0,\"Pilot\",\"The Ingalls family moves from 'the big woods' to the plains of Kansas where they face a lot of exciting adventures.\",0,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(1,\"A Harvest of Friends\",\"The Ingalls move to the banks of Plum Creek, near Walnut Grove, Minnesota. <br />To acquire the deed to his farm, Charles takes several jobs. Eventually, the multiple duties and stress become too much, and an exhausted Charles becomes injured during a picnic with his family, breaking his ribs after falling out of a tree from which he was trying to get a kite. When a feed dealer takes advantage of him to take his oxen, he and his young children, Mary and Laura, try to meet the deadline. This sends several of Walnut Grove's businessmen into action to help their new friend. In the end, Laura reminisces about her father claiming to reap a harvest he did not expect, hence the title of this episode.\",1,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(2,\"Country Girls\",\"Mary and Laura begin school at Walnut Grove School. While Caroline must deal with the snippy Harriet Oleson, the rich part-owner of the Mercantile, Laura must deal with her spoiled daughter, Nellie. As one problem winds into another, Laura finds a difficulty greater than dealing with Nellie. A looming essay for parents' day causes worry for little Laura who wants to give a beautiful essay, but is unable to write the words on paper. When she finds that she can only write a few words she makes up a speech about her ma which has a great effect on the Ingalls. It is her speech that truly shows the closeness of the Ingalls family.\",1,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(3,\"100 Mile Walk\",\"A hailstorm leaves the Ingalls' crops in ruin. To recoup the money, Charles and some friendly neighbors, including a light-hearted Irishman, work in a dangerous dynamiting job. The Irishman, who is employed as a powder-monkey brings both cheer and eventually tragedy to Charles. Caroline, meanwhile, rounds up the farmers' wives to salvage what's left of the crops, despite the pessimism that threatens their effort.\",1,\"This is a reference to the hundred mile walk in the book 'On the Banks of Plum Creek'. In the books, however, it was locustst that ruined the crop and invariably led them to move on, unlike the television series where they stay in Walnut Grove.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(4,\"Mr. Edwards' Homecoming\",\"While in Mankato, Charles encounters a drunken Mr. Edwards in the midst of a bar fight, and brings him to Walnut Grove. To rehabilitate him, Charles gets him a job at Hansen's Mill while Caroline tries to set him up with widow Grace Snyder. While Mr. Edwards vies for Grace's attention, his personal grudge with God seems to doom their potential relationship.\",1,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(5,\"The Love of Johnny Johnson\",\"Laura's crush on a much older student, Johnny Johnson, is unrequited. His interest in Mary results in sibling rivalry between the two, even though Mary is not interested in him. Eventually Charles explains to Laura that someday she, like Mary, will have many beaus vying for her.\",1,\"In 'On the Banks of Plum Creek' Johnny Johnson is the name of the Norwegian, barefoot, cattle-herd who works near their first home in Plum Creek.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(6,\"If I Should Wake Before I die\",\"After the death of her dear friend, Miss Amy feels lonely for her family. While talking to the Ingalls girls at her funeral, Laura declares it is not fair for loved ones to ignore a birthday and always show up for a funeral. Miss Amy decides to stage her own death and enlists the help of Doctor Hiram Baker and Charles Ingalls.\",1,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(7,\"Town Party, Country Party\",\"While at a party at Nellie Oleson's, Laura hurts her ankle and becomes friends with Olga, a friendly girl with a birth defect causing one leg to be shorter than the other. The Ingalls decide to throw their own party and while Charles helps Olga despite her father's lack of support, Laura exacts her own special revenge on Nellie Oleson.\",1,\"In 'On the Banks of Plum Creek', a chapter by the same name shows a very imilar story, with the exclusion of Olga. In the story, Laura uses an old crab to scare Nellie into the deep end and become the victim of several leeches.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(8,\"Ma's Holiday\",\"The girls and Charles decide to surprise Caroline with a romantic holiday. When Grace Snyder can't make it, Mr. Edwards volunteers for the job. Later on, he finds the Ingalls girls, especially Carrie, to be more than he can handle. Meanwhile, Caroline can't stop thinking about the children and worrying for their safety.\",1,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(9,\"School Mom\",\"When Miss Beadle is injured and ordered to rest by Doc Baker, Caroline takes over as substitute teacher of Walnut Grove School. During her tenure, an uneducated youth named Abel McKay enrolled. Abel is relentlessly teased because he is illiterate. Eventually, the harassment and Mrs. Oleson's meddling become too much, and Caroline orders the school closed. Caroline then takes it upon herself to teach Abel to read.\",1,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(10,\"The Raccoon\",\"When Mary accidentally breaks Laura's glass doll, she brings home a raccoon to cheer Laura up. Laura keeps him and prides herself on teaching him tricks and his docile behavior. To her dismay, food aggression and the many kids at school cause her pet raccoon, Jasper, to bite her on the forearm and run away. Afraid of losing her pet for good, she makes Mary promise to keep it a secret, but when the chickens are disturbed by a rabid raccoon, Mary must break the bad news to her father.\",1,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(11,\"The Voice of Tinker Jones\",\"Reverend Alden stirs a hornets nest in Walnut Grove when he pleads for a church bell. Mrs. Oleson offers to donate a large bell as well as a plaque commemorating her generosity. While half of the residents refuse to accept the donation, arguing that the plaque would be sacrilegious, the other half frown upon the others' apparent ingratitude. The blame invariably falls on Reverend Alden and he is convinced he must leave. With the help of a friendly mute, Tinker Jones, the children decide to band together and forge the bell on their own (sacrificing their own metal toys), before it's too late.\",1,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(12,\"The Award\",\"Mary is entranced by the award for an extra credit exam, being a beautiful dictionary. Her studying and carelessness causes a fire to start in the barn. Worried and furious, Caroline forbids her to take the exam. Having second thoughts, she decides to try to hold Mary to the punishment to establish her credibility while Mary decides to take the test anyway and win her Ma's love back by winning the award. Mary also get's a job at Olsen's store to pay for a new history book to replace the one that she borrowed from Miss Beadle, which was destroyed in the fire. In the end, Caroline sees exactly the paper she expected to see from Mary and the truth is finally made clear. Caroline then tells Mary that she was too harsh on her and that she had been wrong to tell her she couldn't take the exam.\",1,\"Because of a conflict between Michael Landon and Ed Friendly, Michael Landon does not appear in this episode\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(13,\"The Lord Is My Shepheard\",\"The Ingalls family is delighted by the birth of a new baby boy, Charles Fredrick Ingalls. Unfortunately, Laura becomes jealous, and refuses to pray for her new brother's good health. Mercifully, Laura's prayer is answered when the young boy dies soon afterward and Laura is crushed with guilt, following a sermon by Reverend Alden about miracles, she decides to run away and pray for a miracle. Deciding that her late brother meant more to her father than herself, she pledges herself to God on a mountain offering to take his place in heaven so that the baby may come back to life. With the help of a heaven-sent stranger, she realizes how much she really means to her father.\",1,\"Originally aired as a two-hour episode. In syndication, it is seen as a two-part episode.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(14,\"Christmas at Plum Creek\",\"When Christmas comes around, all the Ingalls are caught up in the secrecy and excitement. Charles and Mary take secret jobs to obtain a gift for their loved ones. Laura meanwhile is left out of the fun when she can't find anything to give or any way to raise money. While she succeeds in making the Christmas a memorable experience for everybody by selling her beloved horse Bunny to Nels Oleson so she can buy Ma a stove. Carrie remembers the true meaning of Christmas.\",1,\"This is the first episode in a multi-part story arc involving a horse named 'Bunny', which will figure in third season episodes.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(15,\"Family Quarrel\",\"Nels Oleson has had it up to here with his wife's snobbish, meddlesome behavior, particularly toward the Ingalls family. Mrs. Oleson doesn't take kindly to her husband's old-school beliefs either. The two get into a huge argument and decide to separate. This sends the Ingalls and the Olesons' other friends to intervene and convince them to settle their differences.\",1,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(16,\"Doctor's Lady\",\"When Mrs. Oleson's niece, Kate comes to visit, Doctor Baker falls for her and proceeds to court her. Unfortunately doubt lingering in his mind about his age causes his hopes for a happy relationship to fade. He must wrestle between his love for Kate, and his fear concerning his age to make a difficult decision. His decision is made even harder when Kate refuses to see that the age different between them is a problem.\",1,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(17,\"Circus Man\",\"A medicine man adorned with bravado and sleight of hand stays with the Ingalls and advertises his miracle powder. After residents start to prefer his powders over Doc Baker's medical treatment, the Ingalls send him packing. However, when Jack (the Ingalls' family dog), is injured by a wagon, he returns to bring Laura the hope she needs, and eventually confesses the truth.\",1,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(18,\"Plague\",\"A typhus outbreak sweeps Walnut Grove, and several people become critically ill. The church is set up as a makeshift hospital-morgue while Charles, Doc Baker and Rev. Alden, all quarantined with the illness, search for the source of the plague. During the search Charles is devastated to see his dear friend Mr. Edwards sick with the typhus. However, Edwards holds the key to the source.	\",1,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(19,\"Child of Pain\",\"When Miss Beadle discovers that a kindly boy in her class has taken another beating from his alcoholic father, the town council decides to take action. The Ingalls take in the boy and they decide to help rehabilitate his father. Despite many of the members lack of faith in his redemption and Charles' own doubts, he stays with the boy's father to break him from his dangerous habit.\",1,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(20,\"Money Crop\",\"A university-educated farmer named Joesph Coulter convinces the farmers to buy new hybrid corn. As he returns with the crop, Coulter's horses bolt which caused his wagon to veer down a steep hill, trapped the farmer beneath, and exposed the precious seed to hungry crows. The residents of Walnut Grove fear that they may have been cheated, and take their frustrations out on his wife with harsh accusations. Charles is convinced something is wrong and hurries to look for him.\",1,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(21,\"Survival\",\"While returning from a family trip, the Ingalls receive a twofold warning from a mean-hearted official. He warns them that a blizzard is coming, and that a dangerous Indian fugitive is on the loose. He surprises the Ingalls by claiming his crime was his birth into the Indian race. Later, the family must take shelter in an abandoned cabin. Charles nearly freezes to death but is rescued by the Indian fugitive, Jack Lame Horse. However, when the same ruthless Marshall shows up, Charles is forced to show his gratitude by saving the fugitive's life.\",1,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(22,\"To See the World\",\"After Johnny Johnson has an argument with his father, he decides to leave 'to see the world.' Mr. Edwards accompanies him while on his way to purchase an expensive hunting rifle. However, when Johnny refuses to be swayed, Mr. Edwards relies on his money, and the charms of a young woman to send the young boy home.\",1,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(23,\"Founder's Day\",\"Founder's Day comes to Walnut Grove, and everybody is looking forward to the exciting competitions. While Laura and Mary try to outdo the Olesons, Charles is challenged to a logging contest by an ancient lumberjack. While Charles wants to gain respect from the stubborn old man, his opponent hopes to prove that he is still the 'Bull of the Woods' despite the constant urging of his wife. The excitement reaches a boiling point with the final competition, the logging contest, and Charles proves himself in quite an unexpected way.\",1,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(24,\"The Richest Man in Walnut Grove\",\"Hanson's Mill closes when a major customer declares bankruptcy, leaving Lars unable to pay Charles two months of back pay. The Ingalls have a large tab at the Mercantile, forcing the family into a spirit of cooperation and sacrifice to pay off the bill. On the day Charles presents the funds due, Nels remarks how mightily impressed he is by the Ingalls' resolve.\",2,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(25,\"Four Eyes\",\"The beginning chapter in a story arc concerning Mary's failing eyesight, which will soon render her blind. The tip off of her vision problems comes with her flagging grades. Mary is excited to receive a pair of brand new glasses but her excitement fades when other students relentlessly tease her even after Miss Beadle points out her own pair of glasses. Mary decides to 'lose' her glasses until Miss Beadle unwittingly shows her that she does not need to worry about her glasses making her look unattractive.\",2,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(26,\"Haunted House\",\"When Nellie dares Laura to enter a rickety old house, Laura instead discovers a kindly old widower living there. She learns that he is waiting for his beloved wife, a deceased actress, to return home. Laura excitedly volunteers her help in fixing up the place until a trip to Mankato shows that his wife is dead and not coming back. Laura then must help him overcome his denial and sorrow, when she tells him that his wife is dead.\",2,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(27,\"In the Big Inning\",\"It's Walnut Grove vs. Sleepy Eye in the annual baseball battle. Star pitcher Mumford appears to be an ace up Walnut Grove's sleeve, until his wife discovers the townspeople are betting heavily on the game's outcome. To put a stop to the madness, she benches him, leaving Caroline to persuade Mrs. Mumford to allow him to play. The troubles of the Walnut Grove team are not over however, between arguments of the rightful name of the team, to Sleepy Eye's Green Stockings' win-at-any-cost attitude, the battle for the game is fought in quite an unorthodox manner.\",2,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(28,\"The Campout\",\"Mrs. Oleson invites herself along on the Ingalls' campout after she concludes that Laura and Mary will have the upper hand collecting leaves for a science project. The Ingalls and Olesons seem to mix like water and oil throughout the trip. After learning a 'scratching' good lesson about poison ivy, Laura and Nellie become trapped in a raging current when Laura learns that Nellie can't swim so she has to put her rivalry aside to save Nellie and herself. However, once out of the water, Nellie says that Laura pushed her into the river, which was not the case.\",2,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(29,\"The Spring Dance\",\"Laura wants to go to the annual Spring Dance with Henry Henderson, while Grace Snyder hopes Mr. Edwards will ask her out. But both men, young and old, are too shy to ask the girls. Caroline decides to teach them a technique she used on Charles to make him jealous. While the two girls shamelessly deceive their beaus, Charles reminds Caroline about the exact circumstances that occurred when she tried it on him.\",2,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(30,\"Remember Me\",\"Part 1: A widowed mother named Julia Sanderson learns she has a terminal illness, and has no close relatives willing to care for her three children, John Jr., Carl and Alicia. Charles promises Mrs. Sanderson the children will find a new home. Meanwhile, the relationship between Mr. Edwards and Grace Snyder begins to really blossom. Part 2: Charles has a difficult time finding someone who will adopt all three Sanderson children. At one point, Mrs. Oleson's aunt hopes to adopt Alicia only, while John Jr. and Carl are considered to be potential farming hands to another. While the kids try to show their bravery, Alicia breaks down in tears not wanting to leave her brothers and current guardian Grace Snyder. At the very last minute Mr. Edwards makes a decision that will change his life and the lives of the three orphaned children. Mr Edwards marries Grace Snyder and adopts all three of the Sanderson children.\",2,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(31,\"Ebenezer Sprague\",\"Charles wants to seed a new field and decides to obtain a loan from the new banker, Ebenezer Sprague. The cold-hearted gentleman refuses to trust Charles and his family until Laura unwittingly befriends him at the fishing hole. Their friendship and its abrupt end shows the banker that no man should worry about making any true friends.\",2,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(32,\"At the End of the Rainbow\",\"While fishing in a stream, Laura and her friend Jonah find pyrite and mistake it for gold. Laura spends her days gathering the 'gold dust', and begins fantasizing about her family being very, very rich - and the Olesons being dirt poor. The secrecy starts to lead to squabbling and hasty action from the nosy Oleson children. In the end, the truth becomes a disappointment to the two excited children.\",2,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(33,\"The Gift\",\"The children of Walnut Grove pool their money to buy Rev. Alden a new Bible, and entrust Mary with the cash. However, Mary and Laura decide to invest their money in medicines that, upon their sale, could easily double their money and thus allow them to buy one really great gift for their beloved minister. After much scheming to follow through with their project, they realize that miracle medicines are really not truly needed, and they must tell the truth to the sympathetic Reverend.\",2,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(34,\"His Father's Son\",\"Mr. Edwards and John Jr. feel estranged from each other, and an upset Mr. Edwards tries to make his son join him in his way of life. Mr. Edwards also offers to take him on a hunting trip to his son's dismay. John Jr. writes a heartfelt letter which Mr. Edwards apparently disregards leaving his son with no choice but to go with him. During the trip a frightening encounter helps Mr. Edwards understand his son, and John discovers that his father does care for him, but he couldn't read the note he wrote for him.\",2,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(35,\"The Talking Machine\",\"Laura and Nellie vie for the affections of a new schoolboy named Jason, who is very adept with new contraptions. While Laura accompanies Jason in all his experiments, Nellie tries to use a brand new 'Talking Machine' to gain his affection. When Nellie is unable to get Jason to choose her over Laura, she decides to get even with Laura in a dreadful embarrassing scheme.\",2,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(36,\"The Pride of Walnut Grove\",\"Mary enters a statewide math competition, but Charles can't afford to pay the travel expenses necessary for her to compete. The entire town council foots the bill, with great pride in her. This causes Mary to worry she will let them down. Her return to Walnut Grove shows her that the town is proud of her whether or not she comes first. Although this does not happen, she does get very close, finishing in second place.\",2,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(37,\"A Matter of Faith\",\"Charles and the girls go on a camping trip, and Caroline will join them later. Caroline then scratches herself on a piece of baling wire, and the minor scratch soon turns into a serious infection. Just when she is about to succumb to her illness, Caroline opens her Bible to a passage where she decides to perform a painful procedure, which impresses even Doc Baker.\",2,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(38,\"The Runaway Caboose\",\"At a train station, Mary, Laura, and Carl wander into a caboose. Without warning, the caboose begins to move, and it soon is on a crash course with an oncoming train. Charles and Mr. Edwards go on a race against time to try to warn the locomotive operator and manage to stop the runaway caboose successfully.\",2,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(39,\"Troublemaker\",\"Miss Beadle is relieved of her duties as schoolmarm when several of the older students' misbehavior becomes too much. In her place is Hannibal Applewood, a strict disciplinarian whom students call 'Mr. Crabapple' in disdain. Acting on a false tip from Mrs. Oleson, Mr. Applewood quickly singles out Laura as the class troublemaker, unfairly punishing her for infractions, and even expelling her when test papers become damaged. As things get out of control, Charles decides to step in and figure out just how Mr. Applewood obtained his lengthy resume.\",2,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(40,\"The Long Road Home\",\"During a recession, Charles and Mr. Edwards take a job handling highly explosive liquid dynamite along a rough and dangerously winding road. Also on the same job is an experienced Negro with a tolerant attitude and a prejudiced young man who refuses to accept his partner. Through rough detours, bandits, and prejudice, Charles and Mr. Edwards must work hard on the long road home.\",2,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(41,\"For My Lady\",\"To buy Caroline a new set of china, Charles secretly takes a woodworking job for an attractive young widow. The problem is, Mrs. Oleson plants a suggestion in Mary's mind that there's more going on than woodworking behind closed doors. Laura and Mary soon decide they need to try to 'win Pa back' with plans of their own.\",2,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(42,\"Centennial\",\"Walnut Grove prepares to celebrate the nation's centennial, but the party is threatened with cancellation when their taxes go up. A Russian immigrant, Yuli Pyatakov, gives an impassioned speech about what it's like to live in America, and that he loves his new land despite its faults. The townsfolk are inspired to resume the celebration.\",2,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(43,\"Soldier's Return\",\"EMrs. Whipple's son, Granville, returns to Walnut Grove to resume his career as a music teacher. He becomes close to Mary Ingalls who offers to copy music in exchange for lessons. His new life takes a turn for the worse when a young boy, whose father he abandoned, reminds him of his past with the help of a haunting bugle. He relapses into morphine addiction, which contributes to his eventual suicide.\",2,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(44,\"Going Home\",\"The Ingalls' crops and farm lie in ruin, thanks to a devastating tornado that sweeps through Hero Township. A despondent Charles sees no opportunity ahead, so he decides to move his family back home to Wisconsin and sells his farm. Meanwhile, Mary and John worry about their blossoming relationship which leads to Mary's first kiss and talking about marriage. A crushed Laura prays for Charles to have strength, a prayer that is answered in the form of the previous owners of the farm, who want to buy back their old farm.\",2,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(45,\"The Collection\",\"When Rev. Alden falls ill while collecting, ex-convict Caleb Hodgekiss offers to collect the money himself. However, Hodgekiss is actually scheming to keep the money for himself, until he sees how the money is intended to be used.\",3,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(46,\"Bunny\",\"Nellie goes for a ride on Bunny, Laura's beloved horse, and begins to mistreat it. The horse goes wild and throws Nellie off. Nellie is shaken up but not seriously hurt; however, Nellie decides to pretend that she has been paralyzed in the accident. Laura believes it and, in remorse, decides to help Nellie. However, Mrs. Oleson decides that the only way things can be made right is by shooting Bunny. One day when visiting the Olesons, Laura finds out that Nellie is just fine, and schemes to expose the fake paralysis by pushing Nellie headfirst into the pond. In the end Nellie throws a tantrum.\",3,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(47,\"The Race\",\"Picking up where the previous episode left off, it's a race between Nellie and Laura, and their respective horses. Laura's entry, Bunny, is the favorite, but Mrs. Oleson, over Nels' objections, decides to buy an expensive thoroughbred for Nellie.\",3,\"In production order, this episode preceded its predecessor ('Bunny'), and on the Lionsgate/NBC DVD set, this episode is placed before 'Bunny', reversing the story order. However, one can see the episode separately on DVD in its proper order so as to make the story coherent to the viewer.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(48,\"Little Girl Lost\",\"Carrie proves to be a pest when accompanying her older sisters Mary and Laura on a butterfly gathering trip for school. However, the girls soon regret being annoyed when Carrie falls down an old mine shaft. A drunken old miner finds an opportunity to redeem himself when he assists the cause to rescue Carrie before the crumbling mine collapses.\",3,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(49,\"The Monster of Walnut Grove\",\"A comedy of misunderstandings results when Laura sees what she thinks is Nels beheading his wife during an argument (Mrs. Oleson left town the following morning to go see her family, and Nels had accidentally beheaded a mannequin). Laura reports what she had seen to Nellie and Willie, who play along to have a little fun at their nemesis's expense.\",3,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(50,\"Journey in the Spring\",\"Part 1: Charles' mother passes away after a long illness, and he travels back to Wisconsin to handle the funeral arrangements. His father, Landsford Ingalls (special guest star Arthur Hill), becomes very despondent and, after an argument with Charles, tries to kill himself by setting his house on fire. Charles saves Landsford and talks him into coming to Walnut Grove to sort out his emotions. While staying with his son's family, Landsford begins to form a special relationship with Laura. Part2: Landsford's relationship with his granddaughter, Laura, continues to grow, but falls into jeopardy when Bunny the horse is injured. Landsford tells Laura he will try to nurse the horse back to health, but Charles sees the horse is too badly hurt and must destroy it. Laura is angry when Landsford realizes his son did the right thing and shouldn't have made a promise he couldn't have kept. Landsford wants to leave, causing Laura to go all-out in staying for as long as he wants.\",3,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(51,\"Fred\",\"Laura goes to work for a farmer to earn some extra money, but chooses the farmer's billy goat instead. The goat, whose name is Fred, quickly wreaks havoc on Walnut Grove, doing everything from eating the Ingalls' crops to butting Rev. Alden in the back. Charles soon makes Laura get rid of the goat.\",3,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(52,\"The Bully Boys\",\"The Gallinder family, two 40-ish brothers and a teenager, come to Walnut Grove and quickly cause trouble. Rev. Alden pleads with the townspeople to be patient with the newcomers, but it soon becomes clear the Gallinders want to do nothing but cause trouble. They run up bills at the Mercantile and Hanson's Mill (with no intention of paying off either tab), while the boy causes trouble at school, eventually punching both Laura and Mary. Things get uglier when the men attempt to rape Caroline (while she was on the way to the Mercantile to deliver eggs). When Charles goes to confront the Gallinders, he is beaten. Rev. Alden realizes the Gallinders are nothing but thugs and invites them to church - to order them out of town.\",3,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(53,\"The Hunters (70 minutes)\",\"Charles is badly wounded on a hunting trip when Laura knocks over a gun and it discharges. Laura desperately searches for help, and convinces a blind man and his son to help them. When the son leaves Charles alone in the cabin, Laura and the blind man are forced to work together to find their way out of the woods and get a doctor.\",3,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(54,\"Blizzard\",\"In the series' second Christmas episode (originally aired after Christmas), Miss Beadle dismisses school early on Christmas Eve, unaware that the light, uneventful snowfall is about to quickly become a monster blizzard. The children become stranded halfway home, leading the fathers of Hero Township to brave the worsening weather conditions to find them and lead them back to the schoolhouse. But the blizzard claims a victim...\",3,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(55,\"I'll Ride The Wind\",\"The love between Mary and John Jr. continues to blossom, and marriage may soon be on the horizon. But Mary is worried that she could be standing in the way between John and his dreams of becoming a writer.\",3,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(56,\"Quarantine\",\"Mr. Edwards returns from a nearby town with a case of mountain fever, and passes it on to Alicia. Alicia becomes very sick and Mr. Edwards quarantines himself as he tries desperately to help his daughter. Laura, bringing some raspberries to the back door, hears Alicia's cries and tries to help her. However, Mr. Edwards walks in and she must deal with an angry Mr. Edwards. After Laura 'catches the fever', she goes to Mr. Edwards and Alicia to help them and to keep her family from catching it. At the end, Alicia recovers and Laura turns out to have poison ivy instead.\",3,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(57,\"Little Women\",\"The school plans to put on a series of plays based on books. Laura, Mary, and their friend, Ginny, decide to do a play on 'Little Women.' The Ingalls girls must deal with Nellie, who schemes to get the lead role, and Ginny's desire to play matchmaker for her single mother.\",3,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(58,\"Injuin Kid\",\"Laura becomes friends with Joseph Stokes, the son of a Sioux Indian who moves to Walnut Grove. Joseph's grandfather virtually disowns him because he comes from a mixed marriage, his Native American father and white mother, and is not shy about sharing his bigotry. Things are no better at school, as Joseph is harassed by a bully. Eventually, Laura helps Joseph stand up to the bully.\",3,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(59,\"To Live with Fear\",\"Part 1: Mary is severely injured when a horse kicks her in the barn. When her condition deteriorates, it becomes clear she needs an expensive surgery to save her life. Charles and Mr. Edwards are forced to take dynamiting jobs for the railroad to fund the surgery. Part 2: Mary needs more surgery, something that weighs heavily on Charles' mind as he feverishly works to earn enough money for his daughter's surgery. Eventually, a fatigued Charles causes an accident that traps him and a co-worker inside. Mr. Edwards leads a harried but courageous effort to save the two men's lives.\",3,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(60,\"The Wisdom of Solomon\",\"A young black boy named Solomon, the son of former slaves, runs away to Walnut Grove, and soon takes refuge at the Ingalls. Charles is able to get the truth from Solomon: He is tired of everyone treating him 'different' because he is black. Charles tells him he has much to be proud of and convinces him to return home, but not until after Solomon teaches the people of Walnut Grove a few lessons of his own.\",3,\"Rarely shown on (American) television\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(61,\"The Music Box\",\"Laura makes friends with Anna, a girl who stutters and has made few friends as a result. Later, Nellie starts a club and invites Laura to join but not Anna. While at the Mercantile, Laura steals a music box. Nellie catches her in the act but decides to keep silent about the incident on the condition that Laura break off her friendship with Anna. Later, Nellie inducts Anna into the club, but only to humiliate her. Laura goes along with the teasing, but Mary soon gets Laura to confess everything that's happened. In the end, Charles makes Laura admit to Nels that she stole the music box. Nels is disappointed but praises Laura for coming clean and feels that she had been 'punished enough', which is nothing compared to the punishment Nellie is about to face. Laura also must make amends with Anna, who is terribly hurt by the earlier shenanigans at the Olesons'.\",3,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(62,\"The Election\",\"A three-way race for class president ensues, with Nellie and Mary battling the slow-witted Elmer Dobkins for the honor. Plenty of shenanigans ensue: Elmer's nomination was just a joke, while Mary and Nellie each host parties to try to win votes. After two boys play a cruel joke on Elmer, his father makes him withdraw from the election until Mary (who withdraws herself) pleads with Elmer saying that many lessons have been learned. In the end, Willie, of all people, winds up casting the deciding vote and votes for Elmer, stating that Elmer won't let Nellie pick on him.\",3,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(63,\"Gold Country\",\"When their crops are destroyed by heavy rain, the Ingalls and Edwards families head west to pan for gold. However, the temptations of being rich soon turns everyone against each other. Laura and Carl visit with an ex-miner who has seen the ill effects of gold mining. In the end, Charles and Mr. Edwards realize each of them is already rich (because they have their families) and decide to go home.\",3,\"1) Originally aired as a two-hour episode. In syndication, it is seen as a two-part episode. 2) Last appearance of Victor French until a guest shot in the sixth season, and his full-time return late in the eighth season. 3) Final appearance of Brian Part as Carl Edwards. Carl is seen again in 'A Promise to Keep' but is played by a different actor in that episode.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	//season 4
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(64,\"Castoffs\",\"Caroline orders Laura to care for her dog, Jack, before going to town to greet a newcomer, Kezia Horn, who lives in a house without walls. Laura becomes frustrated at Jack and gives up trying to take the foxtails out of his ears. Mary, Laura, Nellie, and Willie go to visit Kezia and find out what a unique yet kind person she is. When Laura arrives home, she finds old Jack dead in the barn. In tears, she and her family bury him in the meadow. Later, Charles brings home a stray dog (Bandit) that followed him home from Mankato, but Laura refuses to bond with the dog. Kezia speaks to Laura about how the dog only wants to love her, and how she also wants to love others but hasn't been accepted. Guilt-ridden Laura runs to find the dog and bonds with him. Reverend Alden speaks with Kezia, who decides to leave Walnut Grove because no one is accepting of her, and it's up to Laura to get everyone to change their minds before it is too late.\",4,\"First appearances of Merlin Olsen and Hersha Paraday as Jonathan and Alice Garvey\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(65,\"Times of Change\",\"Charles takes Mary to Chicago, where he is attending the Grange Convention. There, Mary meets up with John Jr., who has started a job as a cub reporter for a newspaper. However, former lovebirds John and Mary soon find their lives headed in separate directions, especially for John Jr. who has a new girlfriend.\",4,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(66,\"My Ellen\",\"When Laura and Mary go skinny-dipping with their friend, Ellen Taylor, some boys come by to get a glimpse. The girls hide underwater until they go away. Laura and Mary come back up, but Ellen becomes trapped under the surface and drowns. Ellen's grief-stricken mother blames Laura for the tragedy, then rebuffs efforts by several people to cheer her up. Later, when Laura turns up missing, Mrs. Taylor had trapped Laura in the basement, thinking she is Ellen, suspicion falls on Busby, a mentally challenged man whom Charles had warned his daughters to stay away from. While the hunt is on for Busby, Laura must rely on her wits to escape Mrs. Taylor's clutches and help her come to terms with Ellen's death.\",4,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(67,\"The Handyman\",\"After Caroline complains about the small size of her kitchen, Charles decides to build an addition onto the house. However, he must leave to take a rush delivery to Mankato. Caroline hires a handsome young handyman named Chris Nelson to complete the job. Chris stays with the Ingalls family and unwittingly becomes head of the household in Charles' absence, prompting Carrie to mistakenly call the man 'Uncle Chris.' Mary soon becomes convinced that her Ma and Chris are becoming romantically involved, and she freely expresses her opinions. Nellie and Mrs. Oleson don't help matters when they share Mary's suspicions. Eventually, Mary confronts Chris with her suspicions and tells him he must leave, only to find out later it was a misunderstanding. Charles later returns and finishes the kitchen.\",4,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(68,\"The Wolves\",\"<a href='../../characters/laura_ingalls_wilder.html'>Laura</a> and her new friend, Andy Garvey, find an injured mother wolf trying to tend to her pack of baby pups. Andy takes the wolf and her babies home to care for them, but decides to move them to the Ingalls' barn when he learns Larabee wants to shoot them. Things turn deadly when a pack of rabid dogs advance on the barn, trapping Andy, Laura, Mary, Carrie, and Bandit inside, leaving them to rely on Jonathan, and even more so, Bandit and the mother wolf, to save them from being mauled.\",4,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(69,\"The Creeper of Walnut Grove\",\"Laura and Andy become detectives to solve a series of burglaries in Walnut Grove. After an incident at the Oleson's, Charles becomes very angry with his daughter. However, things get worse when Laura sets some traps to catch the culprit, but winds up catching Charles instead (at one point, causing him to be doused with green paint). It is soon revealed that a boy named Timothy Ferrel was the creeper all along.\",4,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(70,\"To Run and Hide\",\"When Dr. Baker is unable to save a terminally ill patient, he chalks it up to incompetence and resigns as Walnut Grove's doctor. While he tries his hand out at farming, a new doctor, Dr. Logan, accepts a call to replace Dr. Baker. However, he is ill-tempered and has no compassion for his clients, prompting Charles to go all-out to convince Dr. Baker that he is a good doctor and that the people of Hero Township need him.\",4,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(71,\"The Aftermath\",\"Outlaws Frank and Jesse James bring their trail of treachery to Walnut Grove. They stake out the town and take aliases while trying to blend into the background, even hiring Mary to do their work. However, their cover is soon blown when a posse arrives to arrest the James brothers, causing them to take Mary hostage.\",4,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(72,\"The High Cost of Being Right\",\"When the Garveys' barn burns down, Alice takes a job at the post office. Johnathan believes that it's a man's job to support a family, and is outraged and decides to leave the family. When the judge comes and the divorce is about to be filed, Jonathan changes his mind\",4,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(73,\"The Fighter (70 minutes)\",\"Boxer Joe Kagan's career costs him everything, including his family. Ultimately, he faces his greatest challenge - his own grown son.\",4,\"This episode introduces Moses Gunn in the title role of Joe Kagan.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(74,\"Meet Me at the Fair\",\"The Oleson and Ingalls families travel to a fair in Mankato, where Mary hopes to spend time with a boyfriend. Instead she is propositioned by her boyfriend's boss. Meanwhile Nels and Charles enter a donkey riding contest, and Laura has a hard time staying with Carrie. Eventually, Carrie falls asleep inside a hot-air balloon that accidentally gets set off.\",4,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(75,\"Here Come the Brides\",\"When Adam Simms and his son Luke move to town, Adam instantly takes a liking to Miss Beadle, while Luke and Nellie fall in love. After Nellie talks to Miss Beadle, she and Luke run away to have a very short-lived marriage. In the end, Adam and Eva get married themselves. This episode features one of the first looks at the softer side of Nellie's personality.\",4,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(76,\"Freedom Flight\",\"An Indian tribe comes to Walnut Grove asking for help for their sick chief. Charles and Doc Baker agree to help, angering several racist citizens, who are convinced the Indians mean to attack them. Charles is kept busy nursing the tribe leader back to health and warding off an imminent war.\",4,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(77,\"The Rivals\",\"Charles and Jonathan compete against another team to win a freighting contract that would take them away from their families for long stretches of time. Laura, who is in love with a boy named Jimmy Hill, must compete with somebody else for him. In the end, Charles and Jonathan decide not to accept the new job, and Laura eventually wins Jimmy over, resulting in her first kiss.\",4,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(78,\"Whisper Country\",\"Mary gets her first teaching job in the backwoods community of Willow Prairie, but is met with stern, purely hateful opposition by the settlement's leader: an elderly woman who has driven away previous teachers and has thwarted all attempts to establish a school and uses the Bible in a hateful way to back her beliefs. The father of a student she stays with, a loyal follower to the woman, is just as bad. The woman's adamant beliefs against common things such as reading and cleaning with soap and water are the cover for her own shameful secret: She cannot read. Mary is driven from the community, but after Charles gives her a pep talk, she is able to expose Mrs. Peal. Afterward, she learns to accept and embrace education.\",4,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(79,\"I Remember, I Remember\",\"While waiting for Charles (who is stuck in the rain with a broken wagon wheel on her anniversary), Caroline tells the children the story of how she and Charles met.\",4,\"In this episode Matthew Laborteaux portrays young Charles, in the next season he would return, but as orphan child Albert.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(80,\"Be My Friend (70 minutes)\",\"When Laura finds a bottle with a note inside that reads, 'Be my friend,' she convinces Charles to help her look for the person, but they find a baby. They then look for the child's parents.\",4,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(81,\"The Inheritance\",\"When Charles receives news that he is the heir to a late relative, Mrs. Oleson becomes oddly friendly. The Ingalls, sure they've inherited a fortune, go on a wild spending spree to upgrade their farm and equipment. Then, Charles gets the inheritance and finds out he's inherited Confederate money. Mrs. Oleson immediately decides to foreclose on the Ingalls farm, putting the Ingalls' friendships to the test.\",4,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(82,\"The Stranger\",\"Nels' cousin sends his 12-year-old son, Peter, to Walnut Grove after the boy's behavior grows unmanageable. However, Mrs. Oleson babies the son, prompting a frustrated Nels to turn to Charles for assistance in rehabilitating Peter, which leads to a reconciling between Peter and his father.\",4,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(83,\"A Most Precious Gift\",\"Charles has always wanted a son, and has another chance to get one when Caroline announces she's pregnant. But Caroline fears how Charles will react if the baby is a girl. Eventually, it's all for naught, as Charles loves his baby Grace just the same.\",4,\"The Ingalls' youngest biological child, Grace, is born.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(84,\"I'll Be Waving As You Drive Away\",\"Part 1: Just as Mary falls in love with newcomer Seth Barton, her eyesight begins to worsen. Charles takes her to an optometrist, but the news is not good: Mary's vision cannot be saved, and she will soon go blind. In denial, Charles does not tell his daughter until the day before she wakes up and finds to her horror she is completely blind. Mary becomes very bitter over her predicament and having to rely on others for basic needs. Part 2: Mary is sent to a blind school in Iowa, where she meets her husband-to-be, Adam Kendall. Mary refuses to accept Adam's help at first, but he eventually helps her learn to deal with her blindness. When Adam encourages Mary before her return to Walnut Grove, he says a key line that serves as the title of this episode. Meanwhile, the town of Walnut Grove faces bankruptcy as its citizens prepare to move out.\",4,\"The following note applies to part 2 of the episode: This marks the first appearance of Linwood Boomer as Adam Kendall, and the final appearance of Charlotte Stewart as Miss Beadle-Simms.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	//season 5:
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(85,\"As Long As We're Together\",\"Part 1: Picking up where the previous season left off, the Ingalls, Olesons and Garveys settle in the town of Winoka, where they are met by a cruel local businessman, Miles Standish. This episode marks the introduction of Matthew Laborteaux as Albert, the lovable orphan who is eventually taken in by the Ingalls family. Part 2: The former Walnut Grove residents continue to adjust to life in the city of Winoka. Charles and Caroline are managing The Dakota Hotel; Nels, Harriet and Jonathan Garvey are working in the saloon and Alice Garvey begins teaching school for the poor children of Winoka in a stable since the only other school in town is an expensive private academy.\",5,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(86,\"The Winoka Warriors\",\"Charles convinces Albert to attend the livery school. With Garvey as coach, Albert and the livery school's football team challenge the undefeated private academy's football team. Both sides attempt to unbalance the game in their own favor, however, when it seems all is lost for the livery school, help comes from an unexpected place...in the form of one of Adam's blind students.\",5,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(87,\"The Man Inside\",\"Laura makes friends with a shy classmate, but winds up jeopardizing the friendship when she makes fun of an obese man, not knowing he is the girl's father. Hearing that his daughter is ashamed of him, the man gets a job and lives at the blind school, while telling his family that he got a job that would take him away from the area. The man's double life is exposed once he's seriously injured at the school.\",5,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(88,\"There's No Place Like Home (45+70 minutes)\",\"Part 1: A gambling man named Toby Noe (Ray Bolger) loses all his winnings, indirectly leading to the decision for some of Winoka's residents to return home to Walnut Grove. Part 2: The Ingalls and friends return home to Walnut Grove, only to find the town in disrepair, and a disgruntled and disabled Lars Hanson, who had been crippled by a stroke. It is up to the townspeople to rebuild Walnut Grove and to rekindle the spirit of both the town and Mr. Hanson.\",5,\"This episode marked the final appearance of Karl Swenson as Lars Hanson; Swenson died a short time after this episode was filmed.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(89,\"Fagin\",\"Charles buys Albert a calf for the upcoming county fair which Albert names Fagin. Laura grows jealous when Charles starts giving more attention to Albert. When Nellie teases Laura about having Albert as a brother, Laura punches Nellie in the eye. After Albert overhears Charles and Caroline talking about Laura's jealousy, Albert runs away, leaving Laura to take care of Fagin for the fair.\",5,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(90,\"Harriet's Happenings\",\"Mrs. Oleson's cousin, Sterling Murdoch, comes to Walnut Grove to start the town's first newspaper, The Pen and the Plow. Mrs. Oleson writes a column for the fledgling newspaper, and soon writes scandalous stories about the residents of Hero Township. When she learns that a German student Erich Schiller beat Nellie in the school spelling bee, Mrs. Oleson claims that the lad's German immigrant parents are illiterate. Charles confronts Murdoch about his newspaper, but his complaints fall on deaf ears. Laura and Albert temporarily get back at Mrs. Oleson, but she responds by writing a story suggesting Charles fathered Albert outside his marriage. Charles has enough and exposes the work of Murdoch and Mrs. Oleson in church on Sunday, clearing up the lie about the Schiller family (they could read German), then chastises the rest of the town for reading the newspaper.\",5,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(91,\"The Wedding\",\"Adam proposes to Mary, and she accepts. Charles and Caroline travel to Winoka for the wedding. Mary begins to have doubts about getting married, once Charles and Caroline talk about being grandparents and how hard it was to keep track of Mary when she was little. Mary is worried about how she and Adam will possibly be able to raise a baby, since they are both blind.\",5,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(92,\"Men Will Be Boys\",\"When Albert and Andy boast they can become self-sufficient, Charles and Jonathan decide to take them on a camping trip to put that claim to rest. But Albert and Andy prove their worth, and their fathers wind up, well, not so well off.\",5,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(93,\"The Cheaters\",\"The Walnut Grove School children take a series of routine tests to prepare them for the next grade, but after Andy Garvey shows failing grades, his parents enlist Nellie Oleson to help him with his studies, but Nellie shows him an even better way to succeed: by cheating. Meanwhile, Charles gives Albert a different lesson in cheating...cheating within the heart, as he is trying to fail in school to be more popular.\",5,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(94,\"Blind Journey\",\"Part 1: It is discovered that the late Mr. Hanson has willed his (now decrepit) house to the town of Walnut Grove. The town council then elects to turn it into the new blind school, as the proprietor of the blind school in Winoka has informed Mary and Adam that the rent has been raised to an amount they can no longer pay. Charles then recruits Joe Kagan to accompany him to Winoka to lead the children back to Walnut Grove. To their shock and dismay, they discover that Mrs. Oleson has paid a large sum of money to name the new blind school after herself and traveled to Winoka to help lead the blind children to Walnut Grove in order to impress someone named Mrs. Terhune. Part 2: In Winoka, Mrs. Oleson is disappointed to discover that Mrs. Terhune is not an elite society lady from St. Louis, but rather Hester Sue Terhune (Ketty Lester in her first appearance), the African American caretaker of the blind school that has merged with the one run by the Kendalls. During the journey back to Walnut Grove, Mrs. Oleson must overcome her racism and Adam must overcome his fear of water. Upon return to Walnut Grove, Nels is shocked to see that his wife has overcome her racism (for now).\",5,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(95,\"The Godsister (70 minutes)\",\"Carrie becomes heartsick for her Pa when Charles and Jonathan take jobs on a telephone crew and must be away for weeks. When nobody has time for her, Carrie creates an imaginary friend named Alyssa, and the two have wonderful adventures together.\",5,\"Lindsey and Sidney Greenbush appear on-screen together in the roles of Carrie Ingalls and her imaginary friend, Alyssa.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(96,\"The Craftsman\",\"Albert takes a job as apprentice for a Jewish coffin maker, who is the target of deep prejudice in the community.\",5,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(97,\"Blind Man's Bluff\",\"Laura's schoolmate and friend, Jordan, has dreams of one day working for a circus but is troubled by his quarreling parents. After an accident causes temporary blindness, Jordan pretends to remain blind in an effort to bring his parents closer together and avoid their upcoming divorce. Laura discovers Jordan's deception and struggles about whether she should tell everyone the truth.\",5,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(98,\"Dance with Me (70 minutes)\",\"Ray Bolger (The Wizard of Oz fame) returns as the happy-go-lucky-who-turned-bankrupt Toby Noe. He is staying with the Ingalls family and eating them out of house and home when the spirited spinster Amanda Cooper catches his eye. Toby sets out to win her heart but she is determined to keep him at arm's length. Meanwhile, Laura has a crush on schoolmate Jason and, with Albert's council, tries to get him to notice her.\",5,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(99,\"The Sound of Children\",\"Mary and Adam discover they are having a baby. Adam's father visits Walnut Grove upon learning the news and convinces Adam and Mary to move to New York so that Adam can attend law school and eventually become a partner in his father's law firm. Mary suffers a miscarriage and Adam realizes that the troubles between he and his father were not imagined after all.\",5,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(100,\"The Lake Kezia Monster\",\"Mrs. Oleson attempts to evict Kezia (Hermione Baddeley) from her house by the lake. She, Willie, and Nellie move in and force Kezia to serve as their maid, but Laura, Albert, and Andy Garvey hatch a plan to drive the Olesons away. They get Kezia to concoct a story about a monster that inhabits the lake, and then dress up as the monster. The plan works, the Olesons run away screaming, and Kezia keeps her house.\",5,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(101,\"Barn Burner\",\"Farmer Judd Larabee objects to setting a standard price for wheat, particularly since black farmers would be paid the same rate as white farmers. Jonathan Garvey has enough of Larabee's racism and confronts him in front of his family. Tensions escalate when a vengeful Larabee pays a visit to the Garveys and assaults Andy, who is the only one home. Then, the Garvey's barn burns down and Larabee is fingered as the suspect. Andy knows the truth, but will his testimony be complete enough before Larabee's fate is sealed?\",5,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(102,\"The Enchanted Cottage\",\"Mary begins to see light again and the entire family hopes she will soon recover her sight. She and Charles travel to visit the eye doctor for tests and a professional assessment. Meanwhile, Adam struggles with the possibility of Mary regaining her vision and what that means for their future. An excited Laura recruits Albert to help her fix up the Mr. Edward's old shack for Mary's return. Nels Oleson donates his unsold paint to Laura's project. However, the work is for naught as doctors discover Mary's blindness is permanent (her heat sensitivity is the reason for her condition). Charles teaches Mary that feeling sorry for oneself is not the answer, a lesson she passes on to Laura upon her return to Walnut Grove.\",5,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(103,\"Someone Please Love Me\",\"During a horse-buying trip to Sleepy Eye, Charles meets up with Brett Harper, one of the state's best horse breeders. However, Harper's alcoholism has taken a deep toll on the family and is coming apart because of the lack of a strong head of the household. Charles temporarily takes the role as the family man while he tries to sober Harper up, but his touch may have worked too well: Harper's wife and children like Charles better than drunken Brett (who had become that way after his son had died). Charles manages to convince his family that Brett is a good person, but needs to be sober to be so.\",5,\"An episode of Bonanza, titles 'A Dream to Dream' had a story with a similar theme to this episode.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(104,\"Mortal Mission\",\"Numerous Walnut Grove townsfolk become seriously ill after eating anthrax-laced mutton, turning the Blind School into a makeshift hospital and morgue. Charles and Jonathan, among the few who hadn't gotten sick, race against time to rush supplies and medicine to the Blind School, but have to encounter a few obstacles along the way. Namely, the brothers who sold the meat even though they knew it was spoiled; and a deluded farmer who believes the medicine will help him become rich.\",5,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(105,\"The Odyssey\",\"Laura and Albert's friend, Dylan, has one dream - to one day see the ocean. When the boy discovers he is terminally ill, he sets out to realize his dream and Laura and Albert join him. As the trio begins the journey to San Francisco, they come across a few stumbling blocks and are soon found by a worried Charles. The children convince Charles to help Dylan obtain his dream of seeing the ocean before he dies. The group meets William Randolph Hearst, famous American newspaper magnate, along the way.\",5,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(106,\"Back to School\",\"Part 1: A new school year begins with a brand-new teacher, and Laura meets Almanzo Wilder, who would become her husband. Nellie and her mother also has their eye on the handsome young farmer and believe that Nellie's new restaurant and hotel will attract his attention. Nellie proves to be less than competent at hospitality when she inadvertently serves Almanzo cinnamon chicken with cayenne (added onto by Laura). Part 2: Laura is punished when Caroline discovers the secret to the ill-fated chicken dinner Nellie served Almanzo in Part I. Later, Nellie deliberately gives aspiring teacher Laura some incorrect material for an exam, and Laura fails miserably. The two engage in a memorable catfight, and both of them land in the mud. When Almanzo takes Laura back to his place to clean up, Charles finds her wearing his robe and assumes the worst.\",6,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(107,\"The Family Tree\",\"The school's latest project is to create a 'family tree' documenting the history of their families, which causes Albert to remember his own dark past. Ultimately, he has become attached to the Ingalls that he wants them to adopt him. But first, they must face Albert's real father.\",6,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(108,\"The Third Miracle\",\"Adam wins a teaching award and must travel to Minneapolis to receive it. En route, Mary, Adam, and another woman and are involved in a serious stagecoach accident. Mary is the only one who is able to look for help. While she is climbing the hillside, her old glasses fall out of her pocket. The glasses inadvertently start a fire that acts as a signal for Charles, who's searching for her. Meanwhile, Laura and Albert get Mrs. Oleson and Nellie to pick up some honey from a honeycomb, not telling them they're actually getting a hornets' nest.\",6,\"Leslie Landon appears in this episode as the other woman in the stagecoach. She also appears in Season 8's 'A Wiser Heart' and will later play the role of Miss Plum in Season 9 ('A New Beginning').\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(109,\"Annabelle\",\"When the circus comes to town, Nels tries to make amends with his estranged rotund sister, Annabelle.\",6,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(110,\"The Preacher Takes a Wife\",\"Rev. Alden falls in love with a member of his congregation and marries her, but almost comes at a cost when Mrs Oleson attempts to tear their relationship apart, causing the Reverend to render himself ill with the flu.\",6,\"This would be the only episode showing Alden's married life as his wife would not appear in another series episode, leaving that plot hole ambiguous. However, she is mentioned in a later story ('The Faith Healer').\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(111,\"The Halloween Dream\",\"Before going to a Halloween party, Albert and Laura take a nap and have a dream where they are mistaken for Indians and taken to a tribe's camp.\",6,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(112,\"The Return of Mr. Edwards\",\"Mr. Edwards has become very wealthy owning a logging empire. When Alicia brings him lunch, she is nearly crushed by a falling tree. Edwards saves her from certain injury, but his leg is crushed. He soon becomes resigned to life as a cripple, prompting Grace to write to her old friends, the Ingalls, to help. However, neither Charles nor Laura can seem to get Edwards to snap out of his depression, which is taking its toll on the family. On two occasions, Charles has to stop Edwards from trying to commit suicide. Only when Charles pretends to have been injured in a gun accident does Edwards snap out of his deep depression. It isn't long before Edwards is back to his old, irascible self.\",6,\"1)  This is Victor French's first appearance on the show in 2 years (due to his commitment to his previous series, Carter Country, however he would not appear on the show again until the eighth season. 2)This is Bonnie Bartlett's final appearance as Grace Snyder Edwards. The character appears on 'A Promise to Keep', but is played by different actress\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(113,\"The King is Dead\",\"A professional wrestling promoter tries to convince Jonathan to become a championship wrestler.\",6,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(114,\"Little House Years (TV-movie)\",\"In this three-hour special, the cast reminisce their past years in Walnut Grove (via clips from previous episodes).\",6,\"1) Originally shown as a three-hour TV movie, depicting memorable episodes from the series. In syndication, it is shown as a three-part episode. 2) This episode is not numbered as it was originally shown independently from the series.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(115,\"The Faith Healer\",\"A traveling minister, Jacob Danforth, comes to Walnut Grove on a 'healing' crusade. But after a member of his congregation suddenly dies, some citizens begin to question the minister's motives, leading to a conclusion where Charles finally exposes the truth and Danforth's followers finally turn on him.\",6,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(116,\"Author, Author\",\"Caroline's mother and stepfather come for a visit, but on the trip her mother passes away. Caroline's stepfather is then distraught until he is convinced to write an autobiography. Meanwhile, Mary gives birth to the Ingalls' first grandchild, Adam Charles Holbrook Kendall.\",6,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(117,\"Crossed Connections\",\"The newly invented telephone comes to Walnut Grove. The switchboard is housed in Nellie's Restaurant and Harriet is tasked with being the system's operator. She listens in on a phone conversation from Alice Garvey about her past, which has an adverse effect on the entire Garvey family.\",6,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(118,\"The Angry Heart\",\"A teenage boy comes to Walnut Grove to live with his grandparents, when his mother can no longer tolerate his increasingly ill-tempered behavior. When the elderly couple become afraid of the boy, Charles offers to help reform him. It seems to be working, until Charles gives the boy a gift for his hard work, a blue shirt, that he rips up, not knowing that it triggered the boy's horrible memories of abuse. However, he comes to realize the importance of needing someone in his life, and makes peace with his grandparents.\",6,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(119,\"The Werewolf of Walnut Grove\",\"A bully terrorizes Miss Wilder, the schoolteacher, and his fellow classmates, especially Albert. The resourceful Albert tries to get revenge against the bully by creating a papier-mâché werewolf costume, and nearly succeeds until Carrie unwittingly exposes the effort. The children then decide they've had enough of being pushed around and gang up on the bully.\",6,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(120,\"Whatever Happened to the Class of '56?\",\"Charles and Caroline travel to their class reunion, and find that many of their classmates have become financially successful. But are they really happy in their lives?\",6,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(121,\"Darkness is My Friend\",\"While spending the night at the Blind School, Laura and Mary are held hostage by a trio of escaped felons. When one of them becomes ill from a gunshot wound, the leader sends Laura to get a doctor, warning her that the consequences will be deadly if she says anything about the hostage situation. When she can't find Dr. Baker, the terrified Laura goes to her Pa and tells him about what's going on. Charles poses as Dr. Baker, but soon finds himself in a dangerous predicament when the real Dr. Baker shows up. But Charles manages to get the upper hand.\",6,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(122,\"Silent Promises\",\"Laura, eager to appear more mature, offers to teach a deaf boy sign language. As their teachings go on, he develops feelings for Laura.\",6,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(123,\"May We Make Them Proud\",\"In an episode that marks the turning point for both the characters and the series in general, Albert and a friend, Clay, inadvertently cause a fire at the School for the Blind, killing Alice Garvey and Mary's infant son. After Albert unwittingly causes Mary to snap out of her trance, he runs away to his old home in Olney only to find a grave that says J. QUINN on it (which means that after The Family Tree Albert's biological father somehow died). Soon Albert must come face-to-face with what he has done. It is unknown how Albert's biological father died.\",6,\"1) Originally shown as a two-hour episode. In syndication, it is seen as a two-part episode. 2) Final appearance of Hersha Parady as Alice Garvey. Her character dies in the fire at the blind school.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(124,\"Wilder and Wilder\",\"As the second half of the series begins, Almanzo's wandering brother, Perley Day, comes to stay, and Charles hopes Laura's feelings will shift to him, unaware that he is a troublemaker.\",6,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(125,\"Second Spring\",\"Nels has had enough of his henpecked family life and begins selling his wares on the road. Along the way, he stops in a small town and meets a beautiful woman named Molly. The two begin a wonderful friendship and they learn they have real feelings for each other. Nels finds himself fighting temptation and infidelity, particularly after Charles accidentally catches his friend kissing a woman that is not his wife. Eventually, Nels admits to Molly he is married and the two cannot see each other anymore, then goes home to make amends with his wife.\",6,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(126,\"Sweet Sixteen\",\"The school district's superintendent comes to Walnut Grove looking for someone who can replace a teacher who has fallen and broken her leg. Eliza Jane recommends Laura who passes her teacher's exam and is given the position. She must now travel to another town where her first job will be, but runs into a triangle of misunderstanding between herself, Almanzo, and another student.\",6,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(127,\"He Loves Me, He Loves Me Not\",\"Part 1: Almanzo proposes to Laura who accepts, but their age difference is called into question by Charles, who tells Almanzo to wait two years for him and Laura to be married. An angry Almanzo states that he will not wait and two years seem like forever, and leaves Walnut Grove but Laura refuses to go with him. Meanwhile, in an effort to improve business at Nellie's failing restaurant, the Olseons hire Percival Dalton to help straighten out things. However, Percival doesn't seem to be making much progress because of Nellie's refusal to learn the hospitality business. Only when Percival tells her that he has feelings for her (because of her feisty demeanor) does she begin to cooperate. Meanwhile, Adam learns that he did not get his expected inheritance from his newly deceased father; Adam learns his father spent nearly all of his money, and as a result, most of the assets were used to pay off heavy debts. That puts an end to construction of the new blind school. Laura, however, finds an old courthouse building in Sleepy Eye for rent. Part 2: Laura goes to Sleepy Eye to help Mary and Adam get the new blind school ready. She finds that Almanzo has been working in town but he is still angry about her decision not to go against her father's wishes. When he finds out that Laura is having trouble raising the rent deposit for the blind school, he takes a second job. Unfortunately, while he's working one day, Laura sees him with a saloon girl and believes that he has a new girlfriend. Shortly thereafter, Almanzo becomes gravely ill with pneumonia. Charles finds out and tells Laura what he's been doing for the blind school and his illness. She goes to care for him, and after the matter concerning that 'other woman' is cleared up, the two make up. After his recovery, Charles agrees to allow Laura and Almanzo to wait one year before they get married, rather than having to wait two years. Meanwhile, with Percival's help, Nellie becomes nice, and the transformation is hard for the Ingalls to believe. Eventually, Nellie admits she has feelings (real feelings) for Percival, but says nothing until he announces it's time for him to leave. Mrs. Oleson tries to comfort her daughter, but Nels tells her that, if she wants him that bad, she needs to make her feelings known. It turns out that her proposal was just what Percival was waiting for, and the two marry.\",6,\"This note applies to part 1: First appearances of Steve Tracy as Percival Dalton and Dub Taylor as Houston Lamb.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(128,\"Laura Ingalls Wilder\",\"Part 1: Picking up six months after the previous season finale, Almanzo decides to purchase land for a new farm but will need the earnings from his first crop to pay off the mortgage. When the holder of the mortgage refuses to let him use water from an adjacent creek he loses everything. Meanwhile, Eliza Jane falls in love with Harve Miller, a friend of Almanzo's who has come to live in Walnut Grove. Laura begins teaching at Walnut Grove School and dreams of career but this meets up with Almanzo's strong objections, since he wants her to be a traditional housewife. Nellie finds out that she is pregnant. Part 2: The relationship of Eliza Jane and Harve blossoms, but it never reaches its potential since Eliza is unable to express her true feelings of love for Harve. Things begin to fall apart when Harve reveals he is in love with someone else although Eliza pretends that they are still involved. After Almanzo loses his crop and postpones their wedding, Laura offers to take a teaching position in another town to help earn money for a new farm. Laura breaks the engagement when Almanzo refuses her help. In the end, Eliza Jane decides to leave, but not before convincing her little brother to let his wife-to-be teach at the school. Almanzo agrees, and the two are wed at the Blind School in Sleepy Eye.\",7,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(129,\"A New Beginning\",\"Trying to start a new life after Alice's death, Jonathan moves to Sleepy Eye to start his own freight business. Andy expresses to Jonathan his resentment toward Mary and Adam, blaming them for his mother's death. His fledgling business quickly becomes the target of robbers, and it isn't long before Jonathan, wanting to stop it, becomes a deputy sheriff. He catches the ringleader, but the matter quickly becomes personal when Andy is beaten by the leader's underlings\",7,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(130,\"Fight Team Fight!\",\"One-time football star Pete Ellerbee comes to Walnut Grove to coach the town's football team. Albert decides to join, as he can learn valuable skills such as teamwork, responsibility, and doing your best. But those aren't Ellerbee's goals. His goal is but one, to win, since it proves manhood and pride. Soon, football isn't so much fun in Walnut Grove, when Ellerbee's desire to push the boys beyond their abilities endangers their safety and well-being.\",7,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(131,\"The Silent Cry\",\"Houston, the cantankerous caretaker of the Blind School, gets a turn in the spotlight when two orphaned boys are threatened with separation. A tiny boy named Josh is mute, making him unappealing to any potential families; but his older brother Michael has plenty to offer. Houston realizes that both brothers have value and wants to adopt them, but the adoption agency says no. When a young couple wants to adopt Michael but not Josh, both brothers become very upset and run away, leaving Houston to frantically search for the two.\",7,\"An episode of Bonanza, titled 'The Sound of Sadness', had a story with a similar theme to this episode.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(132,\"Portrait of Love\",\"Stars a young Madeleine Stowe as a talented painter, Annie Crane, who had lost her sight in early childhood. An English art exhibitor was so impressed with Annie's work, even before he found out she was blind, that her art is publicized. Her birth mother realizes who she is and wants to contact her, but Annie is embittered because she felt abandoned, but is reconciled when she learns why.\",7,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(133,\"Divorce, Walnut Grove Style\",\"Laura believes that Almanzo is having an affair with a former girlfriend.\",7,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(134,\"Dearest Albert, I'll Miss You\",\"As a school project, Albert becomes pen pals with a girl elsewhere in the state. However, both of them fabricate stories about themselves in attempts to be more attractive to the other.\",7,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(135,\"The In-Laws\",\"Charles and Almanzo, at the suggestion of Jonathan Garvey, decide to start a freight business to Sleepy Eye. When Almanzo suggests that there might be a better way to get to Sleepy Eye, the two decide to have a race to see who is right.\",7,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(136,\"To See the Light\",\"Part 1: After being caught in an explosion, Adam regains his sight, which worries Mary, who thinks he won't want to be saddled with a blind wife now that he's free to move about without help. Part 2: Having regained his sight, Adam resumes his aspirations of becoming a lawyer. While taking his entrance exam, he is assaulted by hoodlums and falls ill, causing him to miss the final exam. But Mary and Charles talk the schoolmaster into granting Adam permission to finish the test and Adam wins a scholarship to law school.\",7,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(137,\"Oleson Versus Oleson\",\"A town referendum is scheduled, wherein an affirmative vote will allow women to have equal property ownership rights. The men of Hero Township all oppose this effort, including Nels, Charles, and Almanzo. However, those three men agree to the concept of equal rights for women, but have their reasons for not supporting the referendum. When Caroline finds out, she rounds up the women and leads a successful effort to get the men to see the errors of their ways.\",7,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(138,\"Come, Let Us Reason Together\",\"Percival's real name is revealed as Isaac Cohen. Percival's parents visit Walnut Grove. Percival's father, Benjamin, is a hot-tempered man who lives by his Jewish faith, while Nellie's mother Harriet is a full-fledged Christian. Nels brokers peace between Benjamin and Harriet with the deal that a boy would be raised Jewish and a girl would be raised Christian. When Nellie gives birth, she unexpectedly has twins, and names them Benjamin and Jennifer. Nellie and Percival agree to raise their son as a Jew and their daughter as a Christian.\",7,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(139,\"The Nephews\",\"Almanzo's brother Royal visits Walnut Grove and leaves his two naughty children in Almanzo and Laura's care while Royal and his wife enjoy a vacation. Overwhelmed by the boys' constant misbehavior, Almanzo and Laura finally decide to beat them at their own game.\",7,\"This is the first appearance of Royal Wilder, and here played by Woody Eney. The episode also implies that Royal's wife is pregnant with daughter Jenny, whom we will meet two seasons later in ...A New Beginning.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(140,\"Make a Joyful Noise\",\"Joe Kagen moves to Sleepy Eye to assist at the blind school. While there he begins to develop feeling for Hester Sue. She however is planning to marry an undertaker.\",7,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(141,\"Goodbye, Mrs. Wilder\",\"Laura finally loses her patience with Mrs. Oleson's meddling and 'suggestions' for the school. So, Laura resigns and lets Mrs. Oleson run the school, a task she gleefully accepts. She implements French lessons and art appreciation into the curriculum, and makes the children wear uniforms to school. Albert leads a class rebellion against Mrs. Oleson's nonsense, but Laura admonishes him for taking matters into his own hands. Meanwhile, Nels, who supports the more traditional curriculum, says nothing, since he knows he can't get through to his wife, so he allows the visiting regional superintendent of schools to do the talking for him.\",7,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(142,\"Sylvia\",\"Part 1: A 15-year-old girl, Sylvia Webb, is sexually assaulted by an unknown person, only identifiable by a festival clown mask, and she becomes pregnant. Albert and Sylvia fall in love, much to the objections of Sylvia's overprotective father. Mrs. Oleson, at the switchboard, overhears a conversation between Doc Baker and Mr. Webb telling her that Sylvia is pregnant, and she tells the entire town that Albert got her pregnant. Part 2: Sylvia and her father plan to move out of Walnut Grove to escape Albert, whom most of the town believes is the father of Sylvia's unborn baby. But Sylvia and Albert, reunited, have plans to get married and raise her child as their own. Caroline (who earlier had confronted Mrs. Oleson about spreading lies about Albert being the baby's father) counsels Albert about whether he is ready to get married. Later, after Sylvia's father calls her a whore, she runs away. Mr. Webb barges into the Ingalls' house, where Albert affirms that he did not get Sylvia pregnant. Albert gets a job with the town's blacksmith, Irv Hartwig. But he unwittingly discloses Sylvia's whereabouts to the blacksmith, which leads to a final and deadly confrontation in which the rapist's identity is exposed, which costs Sylvia her life.\",7,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(143,\"Blind Justice\",\"Adam becomes a lawyer, but after a promised job at a law firm falls through, he and Mary decide to return to Walnut Grove so Adam can open a law firm of his own. He takes on as his first client a man accused of swindling the citizens of Walnut Grove in a railroad land deal.\",7,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(144,\"I Do, Again\",\"Laura finds out that she is pregnant. Caroline, who also believes that she is pregnant, finds out from Doc Baker that she is experiencing early menopause and can never have more children. Charles, heartbroken upon learning that he will never have another natural son, decides to take Caroline on a second honeymoon, and then they renew their wedding vows.\",7,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(145,\"The Lost Ones\",\"Part 1: Charles and Albert go on a delivery run and meet up and travel with the Cooper family, parents Alvin and Sarah, 11-year-old James and 8-year-old Cassandra, for company. The Coopers are on their way to join Alvin's Uncle Jed on a gold claim. When they encounter a steep hill, Charles and Alvin agree to take the hill one at a time, with James and Cassandra staying with the Ingalls wagon. However, Alvin loses control of the wagon and it overturns, killing him and Sarah instantly. The children witness the accident. Charles takes traumatized James and Cassandra to their Uncle Jed at his gold claim, but he is old and poor and unable to take custody of them. Charles takes the children to Walnut Grove while he searches for a foster family who will accept the children, knowing he cannot financially support any more children in his already crowded home. Part 2: Rev. Alden announces he has found a family, the Tompkins, to take in orphaned James and Cassandra, unaware the father is mean and is merely interested in extra farmhands. At one point, James is unjustly accused of stealing from Mr. Tompkins and is given a whipping. Eventually, the abuse takes its toll, and James and Cassandra run away. The Tompkins tell the Ingalls the children are missing but, when Mr. Tompkins declines to help Charles in the search, it becomes clear he's more interested in getting the children home to teach them a lesson rather than for their safety. In the end, James and Cassandra decide they would be much happier living with the Ingalls, a responsibility that Charles and Caroline realize they must accept.\",7,\"These notes apply to part 1: 1) Jason Bateman and Missy Francis join the cast as orphans James and Cassandra Cooper. 2) Final appearance of the Garveys (Merlin Olsen and Patrick Laborteaux).\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	//Season 8:
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(146,\"The Reincarnation of Nellie\",\"Part 1: Nellie and Percival move to New York City to take over Percival's father's store upon his death. Adam and Mary also move there so Adam can work at his father's law firm. Mrs. Oleson becomes very depressed, and to cheer her up, Nels agrees to go to an orphanage to find a little girl to adopt. Trouble is, Harriet wants someone who is just like Nellie, and soon the Olesons have adopted a brat named Nancy. She quickly causes trouble in Walnut Grove, and it soon becomes obvious she is capable of doing and saying things that are far worse than what Nellie ever did. Part 2: Nancy tricks her new brother, Willie, into locking a classroom rival, Belinda Stevens, in an ice shed, so she could play the lead role in an upcoming musical. Laura later learns that a sob story that Nancy had told the class, that she had been abandoned by her mother, was untrue; Nancy's mother died while giving birth, and she had been forced to move from orphanage to orphanage because of her increasingly uncontrollable behavior. Eventually, Laura, with some help from Belinda, trick Nancy into being the 'queen of the dunk tank' at Walnut Grove's upcoming town festival.\",8,\"This note applies to part 1: First appearance of Allison Balson as Nancy Oleson.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(147,\"Grvin' Pains\",\"James becomes very insecure about living in Albert's shadow, and annoys him by emulating him. After he is caught stealing a razor blade from the Mercantile (after having broken Albert's original blade), James decides to run away. Albert searches for his brother and, in a bit of reverse psychology, tells him he's running away too. During a severe thunderstorm, the two take refuge in a large house, where the two bond.\",8,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(148,\"Dark Sage\",\"Doc Baker hires a university-trained doctor named Caleb Ledoux. However, Dr. Ledoux is black and, with the exception of the Ingalls, finds very little work because of his skin color. Even Doc Baker is prejudiced and gives his new assistant menial tasks. Later, when Doc Baker is unavailable for a call, Dr. Ledoux is called on to save a pregnant mother having complications during childbirth. He saves her life by performing an emergency cesarean section, and Doc Baker realizes the doctor had training he does not possess. An angry Dr. Ledoux threatens to leave, but only upon Doc Baker's impassioned plea does he decide to stay. The residents of Walnut Grove decide to welcome Dr. Ledoux.\",8,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(149,\"A Wiser Heart\",\"Laura attends a writing seminar in Arizona, but things don't go very smoothly, thanks to a less than honorable professor\",8,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(150,\"Gambini The Great\",\"Albert, Willie, and the other schoolchildren are taken in by the stunts of an aging daredevil, and try to replicate them. Only after a tragedy occurs when the daredevil is unable to perform one of his stunts do they learn a lesson about hero worship.\",8,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(151,\"The Legend of Black Jake\",\"Nels is kidnapped by a pair of bumbling criminals who demand a $100 ransom. However, tightwad Mrs. Oleson refuses to pay the ransom, leaving Nels to plot his own revenge.\",8,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(152,\"Chicago\",\"Charles visits grief-stricken Mr. Edwards in Chicago after John Jr. died in an apparent street accident. However, suspicions quickly arise over the circumstances of John Jr.'s death once his boss reveals he was investigating business corruption and was about to go public with his findings. It soon becomes clear that John Jr. was murdered, and it is up to Charles and Edwards to uncover the truth.\",8,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(153,\"For the Love of Nancy\",\"An overweight boy named Elmer is mercilessly teased by his new classmates, but quickly catches Nancy's eye. Of course, Nancy has plenty of cruel tricks up her sleeve, as she uses Elmer to get her way.\",8,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(154,\"Wave of the Future\",\"Mrs. Oleson, believing business to be slow at Nellie's Restaurant, is drawn into the world of restaurant franchising. Nellie's restaurant is renamed Mrs. Sullivan's and, directed by the franchising agent with whom Harriet has signed a contract, the business is restructured to make it more profitable. Unfortunately, the business becomes so busy that Caroline, Hester-Sue and Mrs. Oleson have no time or energy for anything else, leading Charles and Nels to respond by opening their own restaurant as part of a plan to release Mrs. Oleson from her contract. The new restaurant's success, plus the demands of the franchiser, conspire to do in Mrs. Oleson's restaurant, and it isn't long before it reverts back to Nellie's.\",8,\"The character at the end of the story making a 'business proposition' to Harriet is clearly meant to be Col. Sanders from Kentucky Fried Chicken, but for legal reasons this character is credited as 'Bearded Man'. This is also an anachronism as Col. Sanders had not yet been born, and Kentucky Fried Chicken would not be founded until midway through the next (20th) century.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(155,\"A Christmas they Never Forgot\",\"Adam and Mary return to Walnut Grove for Christmas, and arrive at the Ingalls' just ahead of a fierce blizzard. The Ingalls, along with their friend, Hester Sue, spend the snowy Christmas Eve recalling favorite holiday memories.\",8,\"Last appearances of Melissa Sue Anderson and Linwood Boomer.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(156,\"No Beast So Fierce\",\"James makes friends with Gideon, a young boy who stutters. Behind his friend's back, James joins in the teasing, and a distraught Gideon runs away. While Caroline searches for Gideon (to persuade him to come home), Charles invites James along on a shipping trip to Mankato. Along the way, a feral dog tags along and ends up playing a key role in resolving James' and Gideon's differences.\",8,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(157,\"Stone Soup\",\"Laura has a heart-to-heart talk with Willie about responsibility and being a good example to younger students. It's a talk Willie takes seriously, particularly after a pregnant Laura, overwhelmed by managing Almanzo's orchard in his absence, collapses from heat stroke. Willie runs to get Doc Baker, and winds up saving Laura's life. Then, after hearing Caroline read 'Stone Soup' at school, Willie commissions his classmates to help local farmers deal with the drought (starting with Laura's orchard) until Almanzo returns.\",8,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(158,\"The Legacy\",\"In a flashforward to 1982, a couple is purchasing an antique table branded with a large 'CI'. In flashback, we learn that the table was a patent Charles created. Charles had gone to a factory to have the tables produced, but a crooked businessman decides to steal the plans and make a fortune for himself, and succeeds. In the end, Charles decides after all that his greatest legacy is his family.\",8,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(159,\"Uncle Jed\",\"Just as Charles and Caroline are about to formally adopt James and Cassandra, Uncle Jed shows up wanting custody. Initially, this is granted by a circuit judge (as the adoption was not yet formalized), but after suffering a coughing fit in front of the Mercantile, he is diagnosed with consumption and advised to move to the Southwest by Doc Baker. Taking the doctor's advice, he relinquishes custody to the Ingalls, telling the children he has sudden 'business' far from Walnut Grove.\",8,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(160,\"Second Chance\",\"Hester Sue's ex-husband Sam Terhune comes to Walnut Grove, claiming he has reformed himself from his drinking and gambling and wants a second chance. Hester Sue believes him and it isn't long before they plan to get re-married. But on the wedding day, a surprise visitor shows up, who turns out to be Sam's wife Naomi saying she will divorce Sam, and it becomes clear that he does not deserve a second chance.\",8,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(161,\"Days of Sunshine, Days of Shadow (70+45 minutes)\",\"Part 1 (70 minutes): When Almanzo becomes ill, he begins worrying about the condition of his crops. During a hailstorm, he rushes outside but begins to go numb. He suffers a stroke and becomes bitterly resigned to life as a cripple. Part 2: Almanzo grows more and more depressed after his stroke. He refuses to take therapy and even the birth of his daughter, Rose doesn't help. Making things worse is meddlesome Eliza Jane, who plans to care for her brother and get him a 'less stressful job' in Minneapolis. Only after Laura is injured when a tornado levels their home, and she too becomes embittered and wrapped in self-pity, does Almanzo decide to change his grim outlook on life.\",8,\"This note applies to part 2: Final appearance of Lucy Lee Flippin as Eliza Jane.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(162,\"A Promise to Keep\",\"Mr. Edwards returns to Walnut Grove, harboring some devastating secrets. His alcoholism, fueled by his grief over John Jr.'s violent death, has caused his marriage to fall apart. He goes to great lengths to obtain alcohol. While in Sleepy Eye, a drunken Edwards causes another accident that nearly kills Albert. An angry Charles orders Edwards to leave and never come near the family again, leaving Laura as his last hope. Laura takes Edwards in and helps him sober up, until he receives a letter from Grace telling him that she has filed for divorce. A desperate Edwards tries to break into the Mercantile to steal some alcoholic beverages, but eventually walks into the church and begs God for forgiveness and guidance. He becomes godfather to Laura's daughter Rose and is converted to Christianity.\",8,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(163,\"A Faraway Cry\",\"Caroline accompanies Doc Baker to a mining camp where an influenza virus has felled many of its residents and where Caroline's childhood friend is pregnant and desperately ill. Caroline vows to give the baby a good home after its mother dies shortly after giving birth.\",8,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(164,\"He Was Only Twelve\",\"Part 1: Charles, Albert, James, and Mr. Edwards travel to Sleepy Eye on business. James, wanting to open a savings account with his birthday check from Uncle Jed, walks into the bank as it is being robbed. James is shot and critically wounded. When the doctor tells Charles that the injuries are potentially fatal, he and Mr. Edwards, and eventually Albert, who joins against Charles' orders, go on a hunt for the robbers. Part 2: James remains comatose after being wounded. Charles refuses to believe that James' injuries are fatal and begins shunning his friends and verbally abusing his family. Eventually, Charles leaves with James, and builds an altar in the woods. Charles prays to God for a miracle.\",8,\"This note applies to part 1: An episode of Bonanza, titled 'He Was Only Seven' had a story with a similar theme to this episode. This note applies to part 2: Final appearances of Karen Grassle as Caroline Ingalls (until Little House: The Last Farewell), Lindsay and Sidney Greenbush as Carrie Ingalls, Wendi and Brenda Turnbaugh as Grace Ingalls, Missy Francis as Cassandra Cooper Ingalls, and Jason Bateman as James Cooper Ingalls. It was also the final episode of the original 'Little House on the Prairie' series.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	//Season 9
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(165,\"Times Are Changing\",\"Part 1: In the spin-off pilot, the Ingalls move to Iowa, selling their homestead to the Carter family, who are moving from New York City to find a simpler life, while the Ingalls in turn move to Bur Oak, Iowa, having suffered hard times and wanting to find a better life in the city. Four months later, Laura announces her resignation from Walnut Grove School to raise Rose at home, while Almanzo's brother, Royal, arrives with his daughter, Jenny, and a devastating secret: he is terminally ill, and that the true reason he came back to Walnut Grove is to give Jenny a chance to know who would become her adopted parents. Part 2: In the conclusion of the pilot film, the Carters adjust to life in Walnut Grove, but Jenny has a hard time doing so after her father dies and is so distraught that she attempts suicide by drowning herself. Jeb gets over his fear of water by diving in and saving Jenny, and Laura teaches her adopted daughter a 'tough love' lesson on the importance of life, just as her father did before her.\",9,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(166,\"Welcome to Olesonville\",\"A power-hungry Mrs. Oleson obtains the town's bond and uses it to force an election: Elect Nels mayor or else. The townsfolk realize Nels will merely become a puppet for his wife and fight back with a candidate of their own.\",9,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(167,\"Rage\",\"A farmer named Mr. Stark is denied a loan at the bank and soon goes bankrupt. In a rage, he shoots his wife and daughter, then goes on the run. During the manhunt, Mr. Stark hides at the Wilders' residence, and then snaps. He begins to think Laura and Jenny are his wife and daughter. With Almanzo part of the posse, Laura and Jenny must rely on their own wits to defeat Mr. Stark.\",9,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(168,\"Little Lou\",\"A widowed circus man and young father named Little Lou moves to Walnut Grove to try to make a living. He gets a job at the bank, but a prejudiced Mrs. Oleson refuses to do business as long as he is employed there. Jobless, Little Lou begins stealing from the Mercantile to support his baby daughter. Just before he is set to go on trial for theft, Nancy falls down a well, and Little Lou is the only one who can reach inside to save her.\",9,\"An episode of Bonanza, titled 'It`s a Small World', had a story with a similar theme to this episode.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(169,\"The Wild Boy\",\"Part 1: The circus comes to Walnut Grove, and one of the most popular attractions is a 'wild boy.' That night, the boy, whose name is Matthew, runs away from the circus and hides at the Wilders' home. There, Almanzo and Laura discover Matthew had been beaten by his master and given morphine. While they try to keep Matthew safe with Mr. Edwards, his master has posted a reward for the boy's return. Part 2: Nancy, whose mind is focused on the large reward, finds out where Matthew is hiding and leads his master to Mr. Edwards. This initiates a custody battle between the cruel circus master and Mr. Edwards. A judge decides to have Matthew put in a mental hospital, but then allows Mr. Edwards to keep him in Walnut Grove as long as he keeps silent.\",9,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(170,\"The Return of Nellie\",\"Who would ever think someone would be jealous over Nellie? That's exactly what happens when she comes home to visit her family in Walnut Grove. Nellie tries to make friends with her new sister, but Nancy rebuffs her efforts. Later, the people of Walnut Grove toast Nellie at a party, but Nancy, feeling left out, runs away. Nels and Nellie are left to search for Nancy in the woods.\",9,\"Final appearance of Alison Arngrim as Nellie.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(171,\"The Empire Builders\",\"The railroad is coming to Walnut Grove, and with it the promise of jobs and economic growth. But that joy turns sour when the townspeople learn the side effects: the railroad needs property easements, forcing many farmers from their homes; and plenty of ill repute to boot.\",9,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(172,\"Love\",\"Laura's childhood friend, who is blind, falls in love with Mr. Edwards, and the age difference doesn't seem to matter. Later, the young woman has surgery to restore her sight, and her feelings don't change at all when she sees that Mr. Edwards is gruff-looking. Eventually, he encourages her to pursue her dreams.\",9,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(173,\"Alden's Dilemma\",\"A traveling minister is planning a surprise party for Rev. Alden, but this truth doesn't come to light until Alden concludes his congregation is planning to leave him.\",9,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(174,\"Marvin's Garden\",\"A retiring doctor's last patient is Jenny, who is rendered unable to walk or talk after a near drowning.\",9,\"The main theme to the episode's original score would later serve as the theme music to Michael Landon's next series, Highway To Heaven.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(175,\"Sins of the Fathers\",\"Sarah Carter's imposing father visits Walnut Grove, demanding they move back to New York.\",9,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(176,\"The Older Brothers\",\"Mr. Edwards, and later, Almanzo and John, become mixed up with the criminal activities of a bumbling gang of outlaws.\",9,\"An episode of Bonanza, titled 'The Younger Brother's Younger Brother', had a story with a smiliar theme to this episode.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(177,\"Once Upon a Time\",\"Laura wins a story-writing contest and is offered the opportunity to publish her writings in heavily modified form.\",9,\"The book that Jenny reads about 10 minutes from the end is Laura Ingalls Wilder's first book, Little House in the Big Woods. At the end of the episode Michael Landon works as the narrator when a flashforward to present time is seen the first time since episode The Legacy. In the flashforward Michael Landon's daughter Shawna Landon is the little girl purchasing a copy of Laura Ingalls Wilder's 3rd book \nLittle House on the Prairie.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(178,\"Home Again\",\"Charles and Albert return to Walnut Grove after Albert has repeated run-ins with the law (for curfew violations and theft). It is soon discovered that Albert is hooked on morphine, leading Charles to take drastic measures to help his son withdraw from the drug. Because of Albert's morphine addiction, he begins to become out of control, especially when he attacks Jeb Carter in school and hits Etta Plum in the face when she tries to stop him.\",9,\"1) Originally aired as a two-hour episode. In both syndication and the Lionsgate/NBC DVD, it is shown as a two-part episode. 2) Final series appearance of Michael Landon as Charles Ingalls and Matthew Laborteaux as Albert Ingalls until the post-series movies.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(179,\"A Child With No Name\",\"Laura's newborn son unexpectedly dies from an epidemic picked up during a vacation while Laura was pregnant. Laura blames Doc Baker for the baby's death and chalks it up to his incompetence. Doc Baker's reputation is badly damaged and he is almost forced to leave Walnut Grove. Later, Rose becomes sick with smallpox and, against Laura's wishes, Almanzo calls on Doc Baker. When the two are quarantined, Laura soon realizes what she always knew: that Doc Baker is a good doctor.\",9,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(180,\"The Last Summer\",\"Jason begins doing odd jobs for an aging woman. Sarah becomes jealous over the blossoming friendship, until she realizes the woman thinks of Jason as her surrogate grandson. Jason makes plenty of happy memories with his friend before her death.\",9,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(181,\"For the Love of Blanche\",\"Mr. Edwards promises to care for a dying traveler's 'baby,' only to discover it to be an orangutan. The orangutan, named Blanche, makes quick friends with everyone except Nancy. Nancy tries to swat the animal, who fights back. Mrs. Oleson wants Blanche killed, but Willie and Mr. Edwards devise a plan to trick them into thinking Blanche is dead. Mr. Edwards decides that Blanche needs to live in a zoo. Later, Blanche saves Rose from a potentially deadly house fire, and when Jenny tells the story at school, Nancy finds out that Blanche is still alive. Mrs. Oleson demands that the sheriff make sure Blanche is dead this time.\",9,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(182,\"May I Have This Dance?\",\"Willie, fed up once and for all with his mother's meddling, is resolved to marry his sweetheart, Rachel Brown, and take over management of Nellie's restaurant and hotel. Nels is proud of his son, but Mrs. Oleson decides to boycott the wedding.\",9,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(183,\"Hello and Goodbye\",\"Mr. Edwards is devastated when he learns that Matthew's natural father wants to reclaim custody of his son. He winds up moving to Laura's new boarding house, where an Englishman named Sherwood Montague, and newlyweds Willie and Rachel Oleson, have also taken up residence.\",9,\"Low ratings (#28) caused this spin-off series to be canceled after only one season, thus ending a total of nine seasons of the 'Little House' franchise. Thus, in order to wrap up the series' storyline, post-series TV movies of this show will air in the following season.\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	//Season 10
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(184,\"Little House on the Prairie: Look Back to Yesterday (90 minutes)\",\"Charles and Albert return to Walnut Grove to assist the farmers in starting a cooperative. During the visit, Albert begins suffering from serious nosebleeds, which he learns is a symptom of a rare (and possibly fatal) blood disease. In the end, he lives through the final scene holding Laura's hand at the top of the hill in front of the keepsake tree.\",10,\"\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(185,\"Little House on the Prairie: Bless All the Dear Children (90 minutes)\",\"While the Wilders and Mr. Edwards are shopping in Mankato, Rose is kidnapped by a grief-stricken mother, prompting a desperate search for the little girl. A young orphan boy is a key player in the frantic search. Meanwhile, Jason starts a Christmas tree delivery service (to raise money for gifts), Nancy refuses to help contribute to the Olesons' Christmas gathering, while Mr. Montague learns the meaning of Christmas.\",10,\"The movie was originally intended to air in December 1983; however, it did not air until December 1984, 10 months after the official 'finale.'\");"))
	{
		exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	if (mysql_query(conn, "INSERT IGNORE INTO tbl_episodes values(186,\"Little House on the Prairie: The Last Farewell (90 minutes)\",\"During Charles and Caroline's visit to Walnut Grove in the year 1890, residents learn that railroad tycoon Nathan Lassiter holds deed to Hero Township. Meanwhile, Mrs. Oleson is seriously ill and is in a hospital in Minneapolis. Despite their best efforts, the residents are unable to drive Mr. Lassiter away. When they attempt to resist with force, Mr. Lassiter comes back with a detachment of Union troops who order everyone to leave. Though Mr. Lassiter demands the residents' instant evacuation, the soldiers allow the residents to remain until Easter Sunday. Angered at the injustice done to them, the residents decide that they should send a (literally) explosive message to Mr. Lassiter that he can have the land, but not the town. In the end Rev. Alden says 'Did you hear? Walnut Grove did not die in vain.'\",10,\"\");"))
	{
	  exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
	}
	
}
