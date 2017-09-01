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

static char *line_read = (char *)NULL;
//void exitApp(unsigned int errNo, char *errMsg);
void exitApp(int errNo, char *errMsg);
void searchHelp();
int search();
void searchEpisode(char *search);
void searchSeason(char *search);
int searchEpisodesByTitle(char *search);

void catch_siginfo(int sig_num)
{
#ifdef SIGINFO
    signal(SIGINFO, catch_siginfo);
    fprintf(stdout, "lh: A database command line utility about Little House on the Prairie (books, film and TV-series).\n");
#endif
}


int main(int argc, const char * argv[])
{
#ifdef SIGINFO
    signal(SIGINFO, catch_siginfo);
#endif
    signal(SIGINT, catch_int);
  usernameAndPasswordInitialize();
  searchHelp();
  search();
  }

//void exitApp(unsigned int errCode, char *errMsg)
void exitApp(int errCode, char *errMsg)
{
  if(errCode != 0)
    {
      fprintf(stderr, "An error hass occurred.\n"
	      "Error code: %u (Error message: %s)\n", errCode, errMsg);
      exit(errCode);
    }
  else
    {
      fprintf(stdout, "Goodbye\n");
      exit(errCode);
    }
}

void searchHelp()
{
  fprintf(stdout, "Here you can browse the Little House movies and TV series database.\nYou can type\n\t*) e + an episode number (e0-e186) or an episode title to \n\t   display information about a given episode, or\n\t*) s + a season number (s0-s10) to display information about the given\n\t   season, or\n\t*) parts of an episode title, if the first letter is uppercase.\n\t   This will return the episode ID, title and season.\n\t   You can then type eX where X is the returned episode ID\n\t   for more information about that episode.\n");
}
int searchEpisodesByTitle(char *search)
{
  char errorString[100] = "MySQL error: ";
  int hits = 0;
  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  char *server = "localhost";
  char *userName = user;
  char *passwd = password;
  char *database = "little_house";
  conn = mysql_init(NULL);
  if (conn == NULL) 
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) 
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  if (mysql_query(conn, search))
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  
  res = mysql_use_result(conn);
  while ((row = mysql_fetch_row(res)) != NULL)
    {
      hits++;
      fprintf(stdout, "Episode ID: \t%s\nEpisode name: \t%s\nSeason id: %s\n", row[0],row[1], row[3]);
    }
  mysql_close(conn);
  return hits;
}

void searchEpisode(char *search)
{
  char errorString[100] = "MySQL error: ";
  int hits = 0;
  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  char *server = "localhost";
  char *userName = user;
  char *passwd = password;
  char *database = "little_house";
  conn = mysql_init(NULL);
  if (conn == NULL) 
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  
  if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) 
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  if (mysql_query(conn, search))
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  
  res = mysql_use_result(conn);
  if((row = mysql_fetch_row(res)) != NULL)
    {
      fprintf(stdout, "episode id: \t%s\n\nepisode name: \t%s\n\ndescription: \t%s\n\nseason id: %s\n\nnotes: %s\n\n", row[0],row[1],row[2], row[3], row[4]);
    }
  else 
    {
      fprintf(stdout, "No matches.\n");
    }
  
  mysql_close(conn);
}

void searchSeason(char *search)
{
  char errorString[100] = "MySQL error: ";
  int hits = 0;
  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  char *server = "localhost";
  char *userName = user;
  char *passwd = password;
  char *database = "little_house";
  conn = mysql_init(NULL);
  if (conn == NULL) 
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) 
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  
  if (mysql_query(conn, search))
    {
      exitApp(mysql_errno(conn), strcat(errorString, mysql_error(conn)));
    }
  
  res = mysql_use_result(conn);
  if((row = mysql_fetch_row(res)) != NULL)
    {
      fprintf(stdout, "season id: \t%s\n\nseason: \t%s\n\ndescription: \t%s\n\n", row[0],row[1],row[2]);
    }
  mysql_close(conn);
}

int mystrlen(char str[])
{
  int i;
  for(i = 0; str[i] != '\0'; i++)
    {}
  return i;
}

int search()
{
  signal(SIGINT, catch_int);
  signal(SIGTSTP, catch_int2);
  signal(SIGABRT, catch_int3);
  signal(SIGHUP, catch_int4);
  signal(SIGQUIT, catch_int5);
#ifdef SIGINFO
    signal(SIGINFO, catch_siginfo);
#endif
  /*if(line_read)
    {
      free(line_read);
      line_read = (char *)NULL;
    }*/
  
  //line_read = readline("lh$ ");
  /*if(line_read && *line_read)
    {
      add_history(line_read);
    }*/
  //char *noe = line_read;
    printf("lh$ ");
    char *noe;
    size_t linecap = 0;
    noe = (char *)malloc(linecap +1);
    if(getline(&noe, &linecap, stdin) == -1)
    {
        exitApp(1, "End-of-file reached or something else has gone wrong.");
    }
  long l2 = strlen(noe);
    if(l2 == 1)
    {
        printf("Search string must contain at least one character.\n");
        search();
    }
  int noeIntS = strspn("s", noe);
  int noeIntE = strspn("e", noe);
  int noeIntQ = strspn("q", noe);
  if(strncmp("e",noe,1) == 0)
  {
      if(l2 == 2)
      {
          fprintf(stderr, "Invalid search.\n");
      }
      else
      {
          char *new_string;
          while ((new_string =strchr(noe, 'e')) != NULL)
          {
              strcpy(new_string,new_string+1);
              char searchString[150] = "SELECT episodeID, episodeName, episodeDescription, season, notes FROM qry_episodes WHERE episodeID = ";
              strcat(searchString,strcat(new_string, ";"));
              searchEpisode(searchString);
          }
      }
    }
  else if(strncmp("h", noe, 1) == 0)
    {
      searchHelp();
    }
  else if(strncmp("s",noe,1) == 0)
  {
      if(l2 == 2)
      {
          fprintf(stderr, "Invalid search.\n");
      }
      else
      {
          char *new_string;
          while ((new_string =strchr(noe, 's')) != NULL)
          {
              strcpy(new_string,new_string+1);
              char searchString[150] = "SELECT * FROM tbl_season WHERE seasonID = ";
              strcat(searchString,strcat(new_string, ";"));
              searchSeason(searchString);
          }
      }
    }
  else if(strncmp("q", noe,1) == 0)
  {
      if(l2 != 2)
      {
          fprintf(stderr, "Invalid search.\n");
      }
      else
      {
          exitApp(0, "");
      }
  }
  else
  {
      if(l2 >= 2)
      {
          fprintf(stderr, "Invalid search: %s\n",noe);
      }
      else
      {
          /*Let the user type in (parts) of an episode name*/
          /*However, the search string must begin with an uppercase letter.
           This is to avoid confusion when the search string beginns with lowercase
           letters e (episode command), q (quit command), s (season command).*/
          char letter[1];
          strcat(letter, noe);
          if(!isupper(letter[0]))
          {
              fprintf(stderr, "Invalid search: %s.\n", noe);
          }
          else
          {
              char *new_string;
              char searchString[150] = "SELECT episodeID, episodeName, episodeDescription, season, notes FROM qry_episodes WHERE episodeName LIKE '%";
              /*char ns = */strcat(searchString, strcat(noe, "%';"));
              if(searchEpisodesByTitle(searchString) == 0)
              {
                  fprintf(stdout, "No matches were found.\n");
              }
          }
      }
  }
  search();
  return 0;
}

