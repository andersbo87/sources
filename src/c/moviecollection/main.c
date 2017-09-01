#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <readline/readline.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>

int addMovie();
int addMovieDistributor();
int addMovieGenere();
int createDatabase(char *u);
int createMovieTable();
int createGenereTable();
int createMovieCompanyTable();
int createMovieView();
int deleteRecord(char *deleteString);
int funksjon();
int search();
int searchDatabase(char *searchString);
int updateRecord(char *updateString);
void exitApp(int errCode);
void prepareToExit(int errCode, char *errMsg);

char user[100];
char *password;
int recursive = 0;

//storing the tool name as a constant character string...
const char* program_name;
//whether to display verbose messages
int verbose = 0;

static char *line_read = (char *)NULL;

void catch_int7(int sig_num)
{
	signal(SIGBUS, catch_int7);
	printf("\n***Caught SIGBUS signal. Quitting...***\n");
	//kill(getpid(), sig_num);
	prepareToExit(SIGSEGV, "A bus error was caught\n");
}

void catch_int6(int sig_num)
{
	signal(SIGSEGV, catch_int6);
	printf("\n***Process %d caught SIGTERM signal. Quitting...***\n", getpid());
	printf("\nAn error is causing the program to abnormally terminate.\n"
		   "This error is usually caused by a mistake in the sorurce code.\n"
		   "Dumping core\n");
	signal(sig_num, SIG_DFL);
	kill(getpid(), sig_num);
}
void catch_int5(int sig_num)
{
	signal(SIGQUIT, catch_int5);
	printf("\n***Caught ctrl-\\ signal***\n");
    printf("Please press ctrl-c on your keyboard to quit\n");
	search();
}
void catch_int4(int sig_num)
{
	signal(SIGHUP, catch_int4);
	printf("\n***Caught SIGHUP signal***\n");
    printf("Please press ctrl-c on your keyboard to quit\n");
	search();
}
void catch_int3(int sig_num)
{
	signal(SIGABRT, catch_int3);
	printf("\n***Caught ctrl-D signal***\n");
    printf("Please press ctrl-c on your keyboard to quit\n");
	search();
}
void catch_int2(int sig_num) //function that prevents the user from quitting the "application" by using ctrl-z
{
	signal(SIGTSTP, catch_int2);
	printf("\n***Caught ctrl-z signal***\n");
    printf("Please press ctrl-c on your keyboard to quit\n");
	search();
}
void catch_int(int sig_num)
{
    /* re-set the signal handler again to catch_int, for next time */
    signal(SIGINT, catch_int);
    printf("\n***Caught ctrl-c signal***\n");
	printf("Please press 'q' on your keyboard to quit\n");
	search();
}
/*
 Prints usage information for this program to STREAM
 (typically stdout or stderr), and exit the program
 with EXIT_CODE. Does not return
 */
void print_usage(FILE* stream, int exit_code)
{
	fprintf(stream, "%s: usage: options\n", program_name);
	fprintf(stream,
			"-h --help: Display this information\n"
			"-a --add: Add a new item to the database\n"
			"-u --update: Update an existing item in the database\n"
			"-d --delete: Remove an existing intem from the database\n"
			"-s --search: Search the databae\n"
            "-r --recursive: run either -a -d -s or -u recursively"
			"-v --verbose: Print verbose messages\n");
	exit(exit_code);
}

int main (int argc, const char * argv[]) 
{
    // insert code here...
	int choise = 0;
    fprintf(stdout, "Hello, World!\n");
	int next_option;
	//a string listing valid short option letters
	const char* const short_options = "hau:d:svr";
	/*An array describing valid long options.*/
	const struct option long_options[] = {
		{ "help",    0, NULL, 'h' },
		{ "add",     0, NULL, 'a' },//change the 0 to 1 later on
        { "delete",  0, NULL, 'd' },
		{ "update",  1, NULL, 'u' },
		{ "recursive",  1, NULL, 'r' },
		{ "search",  0, NULL, 's' },
		{ "verbose", 0, NULL, 'v' },
		{ NULL,      0, NULL, 0   }
	};
	/*
	 Remember the name of the program, to incorporate in messages.
	 The name is stored in argv[0]
	 */
	program_name = argv[0];
	do 
	{
		next_option = getopt_long(argc, argv, short_options, long_options, NULL);
		switch (next_option) 
		{
		case 'r':
		  recursive = 1;
		  break;
		case 'h':
		  print_usage(stdout, 0);
		  break;
		case 'a':
		  //add a new item.. to be implemnted later on
		  fprintf(stdout, "Add a new item to the database\n");
		  choise = 1;
		  break;
		case 'u':
		  //update an existing item in the databsase. to be implemented later on
		  fprintf(stdout, "Update an existing item in the database\n");
		  choise = 2;
		  break;
		case 'd':
		  //remove an item from the database. to be implemented later on…
		  fprintf(stdout, "Remove an item from the database\n");
		  break;
		case 's':
		  //search the database. to be implemented later…
		  fprintf(stdout, "Search the database\n");
		  choise =3;
		  break;
		case 'v':
		  //be verbose
		  verbose = 1;
		  //funksjon();
		  break;
		case '?': //the user specified an invalid option.
		  /*Print usage information to standard error and exit with exit code -1,
		    indicating abnormal termination*/
		  print_usage(stderr, -1);
		case -1:
		  break;
		default:
		  abort();
		}
	} 
	while (next_option != -1);
	
	if(verbose)
	{
	  fprintf(stdout, "Verbose\n");
	}
	if(choise == 1)
	{
	  // int b = add();
	  getMysqlUsernameAndPasswordAndInitialize();
	  int b = add();
	  /*if(b == 1)
	    addMovie(recursive);
	  else if(b == 2)
	    addMovieDistributor(recursive);
	  else if(b == 3)
	  addMovieGenere(recursive);*/
	}
	else if(choise == 2)
	{
	  getMysqlUsernameAndPasswordAndInitialize();
	}
	else if(choise == 3)
	  {
	    getMysqlUsernameAndPasswordAndInitialize();
	    search();
	  }
	return 0;
}

void prepareToExit(int errCode, char *errMsg)
{
	//do something...
	exitApp(errCode);
}

void exitApp(int errCode)
{
	if(errCode != 0)
	{
		fprintf(stderr, "An error has occurred. Quitting... Error code: %d\n", errCode);
		exit(errCode);
	}
	else 
	{
		fprintf(stdout, "Goodbye\n");
		exit(errCode);
	}

}


int getMysqlUsernameAndPasswordAndInitialize()
{
  signal(SIGBUS, catch_int7);
  signal(SIGSEGV, catch_int6);
  //asking for the MySQL username
  fprintf(stdout, "Enter your mysql user name: ");
  //scanf("%s", &user);
  fgets(user, 100, stdin); //reads the mysql username ("user")
  if(user[strlen(user) -1] == '\n')
    {
      user[strlen(user) -1] = '\0';
    }
  printf("user: %s\n", user);
  
  assert(&user != NULL);
  password = getpass("Enter your mysql password: "); //reads the mysql password
  if(verbose)
    {
      fprintf(stdout, "Creating the movie database unless it already exists...\n");
      createDatabase(user);
      fprintf(stdout, "Creating the genere table unless it already exists...\n");
      createGenereTable();
      fprintf(stdout, "Creating the movie company table if it doesn't exist...\n");
      createMovieCompanyTable();
      fprintf(stdout, "Creating the movie table, unless it already exists...\n");
      createMovieTable();
      fprintf(stdout, "Creating the movie view, unless it already exists...\n");
      createMovieView();
    }
  else 
    {
      createDatabase(user);
      createGenereTable();
      createMovieCompanyTable();
      createMovieTable();
      createMovieView();
    }
  return 0;
}

int add()
{
  int res = 0;
  fprintf(stdout, "What would you like to add?\n"
	  "Enter 1 for movie\n"
	  "Enter 2 for movie distributor\n"
	  "Enter 3 for movie genere.\n");
  /*int ans;
  scanf("%1d", &ans);
  if(ans == 0)
    {
      fprintf(stderr, "Enter a valid integer\n.");
      add();
    }
  else if(ans >= 4)
    {
      add();
    }
  else
  res = ans;*/
  if(line_read)
    {
      free(line_read);
      line_read = (char *)NULL;
    }
  line_read = readline("Enter your selection: ");
  if(line_read && *line_read)
    {
      add_history(line_read);
    }
  char *ans = line_read;
  int lc_length = strlen(ans);
  if(lc_length == 1)
    {
      if(*ans == 'q')
	{
	  exitApp(0);
	}
      else if(*ans == '1')
	{	
	  res = 1;
	  addMovie(recursive);
	}
      else if(*ans == '2')
	{
	  res = 2;
	  addMovieDistributor(recursive);
	}
      else if(*ans == '3')
	{	
	  res = 3;
	  addMovieGenere(recursive);
	}
      else
	{
	  fprintf(stdout, "Choose one of the options on the list above.\n");
	  add();
	}
    }
  return res;
}

int createDatabase(char *u)
{
	MYSQL *conn;
	char *mysql_user = user;
	char *mysql_password = password;
	char *server = "localhost";
	//char *database = "mymovies";
	conn = mysql_init(NULL);
    printf("mysql_user: %s\n", mysql_user);
	if(conn == NULL)
	{
		if(verbose)
		{
			fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		}
		exitApp(mysql_errno(conn));
	}
	if(!mysql_real_connect(conn, server, u, mysql_password, NULL, 0, NULL, 0))
	{
		if(verbose)
		{
			fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		}
		exitApp(mysql_errno(conn));
	}
	if(mysql_query(conn, "CREATE DATABASE IF NOT EXISTS mymovies DEFAULT CHARACTER SET utf8 COLLATE UTF8_UNICODE_CI;"))
	{
		if(verbose)
		{
			fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		}
		exitApp(mysql_errno(conn));
	}
    mysql_close(conn);
	return 0;
}


int createGenereTable()
{
	MYSQL *conn;
	char *server = "localhost";
	char *mysql_user = user;
	char *mysql_password = password;
	char *database = "mymovies";
	conn = mysql_init(NULL);
	if(conn == NULL)
	{
		if(verbose)
		{
			fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		}
		exitApp(mysql_errno(conn));
	}
	if(!mysql_real_connect(conn, server, mysql_user, mysql_password, database, 0, NULL, 0))
	{
		if(verbose)
		{
			fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		}
		exitApp(mysql_errno(conn));
	}
	if(mysql_query(conn, "CREATE TABLE IF NOT EXISTS tbl_genere (genereId int not null auto_increment, genereName varchar(100) not null unique, primary key(genereId));"))
	{
		if(verbose)
		{
			fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		}
		exitApp(mysql_errno(conn));
	}
    mysql_close(conn);
	return 0;
}

int createMovieCompanyTable()
{
  MYSQL *conn;
  char *server = "localhost";
  char *mysql_user = user;
  char *mysql_password = password;
  char *database = "mymovies";
  conn = mysql_init(NULL);
  if(conn == NULL)
    {
      if(verbose)
	{
	  fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
	}
      exitApp(mysql_errno(conn));
    }
  if(!mysql_real_connect(conn, server, mysql_user, mysql_password, database, 0, NULL, 0))
    {
      if(verbose)
	{
	  fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
	}
      exitApp(mysql_errno(conn));
    }
  if(mysql_query(conn, "CREATE TABLE IF NOT EXISTS tbl_movieCompany (companyId int not null auto_increment, companyName varchar(100) not null, primary key(companyId));"))
    {
      if(verbose)
	{
	  fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
	}
      exitApp(mysql_errno(conn));
    }
  mysql_close(conn);
  return 0;
}

int createMovieTable()
{
	MYSQL *conn;
	char *server = "localhost";
	char *mysql_user = user;
	char *mysql_password = password;
	char *database = "mymovies";
	conn = mysql_init(NULL);
	if(conn == NULL)
	{
		if(verbose)
		{
			fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		}
		exitApp(mysql_errno(conn));
	}
	if(!mysql_real_connect(conn, server, mysql_user, mysql_password, database, 0, NULL, 0))
	{
		if(verbose)
		{
			fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		}
		exitApp(mysql_errno(conn));
	}
	if(mysql_query(conn, "CREATE TABLE IF NOT EXISTS tbl_movie (movieId int not null auto_increment, movieTitle varchar(100) not null unique, companyID int not null, actors varchar(100), productionYear int not null, genereID int not null, movieDescription varchar(300), PRIMARY KEY(movieId));"))
	{
		if(verbose)
		{
			fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		}
		exitApp(mysql_errno(conn));
	}
    mysql_close(conn);
	return 0;
}
int createMovieView()
{
	MYSQL *conn;
	char *server = "localhost";
	char *mysql_user = user;
	char *mysql_password = password;
	char *database = "mymovies";
	conn = mysql_init(NULL);
	if(conn == NULL)
	{
		if(verbose)
		{
			fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		}
		exitApp(mysql_errno(conn));
	}
	if(!mysql_real_connect(conn, server, mysql_user, mysql_password, database, 0, NULL, 0))
	{
		if(verbose)
		{
			fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		}
		exitApp(mysql_errno(conn));
	}
	if(mysql_query(conn, "CREATE OR REPLACE VIEW qry_movie AS SELECT movieID, movieTitle, tbl_movieCompany.companyId, companyName, actors, productionYear, tbl_genere.genereId, genereName, movieDescription FROM tbl_movie, tbl_genere, tbl_movieCompany WHERE tbl_movieCompany.companyId = tbl_movie.movieId AND tbl_genere.genereId = tbl_movie.genereId;"))
	{
		if(verbose)
		{
			fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		}
		exitApp(mysql_errno(conn));
	}
    mysql_close(conn);
	return 0;
}

//searches the database...
int search()
{
	signal(SIGINT, catch_int);
	signal(SIGTSTP, catch_int2);
	signal(SIGABRT, catch_int3);
	signal(SIGHUP, catch_int4);
	signal(SIGQUIT, catch_int5);
	signal(SIGBUS, catch_int7);
	signal(SIGSEGV, catch_int6);
	if(line_read)
	{
		free(line_read);
		line_read = (char *)NULL;
	}
	line_read = readline("search-database$ ");
	if(line_read && *line_read)
	{
		add_history(line_read);
	}
	char *c = line_read;
	int c_length = strlen(c);
	if(c_length == 1)
	{
		if(*c == 'q')
		{
			exitApp(0);
		}
	}
	char searchString[150] = "SELECT * FROM qry_movie WHERE movieTitle = '";
	strcat(searchString, strcat(c, "';"));
	printf("%s\n", searchString);
	searchDatabase(searchString);
    /*calling the search function recursively so that the user doesn't have to restart
     this utility if he or she is going to make more than one consecutive search*/
	if(recursive == 1)
	{
	  search();
	}
	return 0;
}

int searchDatabase(char *searchString)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *server = "localhost";
	char *mysql_user = user;
	//printf("user: %s\n", user);
	char *mysql_password = password;
	char *database = "mymovies";
	conn = mysql_init(NULL);
	if(conn == NULL)
	{
		if(verbose)
		{
			fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		}
		exitApp(mysql_errno(conn));
	}
	if(!mysql_real_connect(conn, server, mysql_user, mysql_password, database, 0, NULL, 0))
	{
		if(verbose)
		{
			fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		}
		exitApp(mysql_errno(conn));
	}
	if(mysql_query(conn, searchString))
	{
		if(verbose)
		{
			fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		}
		exitApp(mysql_errno(conn));
	}
	res = mysql_use_result(conn);
	if((row = mysql_fetch_row(res)) != NULL)
	{
		fprintf(stdout, 
				"Movie Title:       %s\n" 
				"Movie Company:     %s\n" 
				"Actors:            %s\n" 
				"Production Year:   %s\n" 
				"Genere:            %s\n" 
				"Movie Description: %s\n",
				row[1], row[3], row[4], row[5], row[7], row[8]);
	}
	else {
		fprintf(stdout, "Sorry, no matches.\n");
	}
    mysql_free_result(res);
    mysql_close(conn);
	return 0;
}

int updateRecord(char *updateString)
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "localhost";
    char *mysql_user = user;
    char *mysql_password = password;
    char *database = "mymovies";
    conn = mysql_init(NULL);
    if(conn == NULL)
    {
        if(verbose)
        {
            fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        }
        exitApp(mysql_errno(conn));
    }
    if(!mysql_real_connect(conn, server, mysql_user, mysql_password, database, 0, NULL, 0))
    {
        if(verbose)
        {
            fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        }
        exitApp(mysql_errno(conn));
    }
    if(mysql_query(conn, updateString))
    {
        if(verbose)
        {
            fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        }
        exitApp(mysql_errno(conn));
    }
    res = mysql_use_result(conn);
    if((row = mysql_fetch_row(res)) != NULL)
    {
        fprintf(stdout, "%ld affected rows\n", (long)mysql_affected_rows(conn));
    }
    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}

int deleteRecord(char *deleteString)
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "localhost";
    char *mysql_user = user;
    char *mysql_password = password;
    char *database = "mymovies";
    conn = mysql_init(NULL);
    if(conn == NULL)
    {
        if(verbose)
        {
            fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        }
        exitApp(mysql_errno(conn));
    }
    if(!mysql_real_connect(conn, server, mysql_user, mysql_password, database, 0, NULL, 0))
    {
        if(verbose)
        {
            fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        }
        exitApp(mysql_errno(conn));
    }
    if(mysql_query(conn, deleteString))
    {
        if(verbose)
        {
            fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        }
        exitApp(mysql_errno(conn));
    }
    res = mysql_use_result(conn);
    if((row = mysql_fetch_row(res)) != NULL)
    {
        fprintf(stdout, "%ld rows were deleted\n", (long)mysql_affected_rows(conn));
    }
    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}

int searchMovieDistributors(char *searchString)
{
  long matches = 0;
  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  char *server = "localhost";
  char *mysql_user = user;
  //printf("user: %s\n", user);
  char *mysql_password = password;
  char *database = "mymovies";
  conn = mysql_init(NULL);
  if(conn == NULL)
    {
      if(verbose)
	{
	  fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
	}
      exitApp(mysql_errno(conn));
    }
  if(!mysql_real_connect(conn, server, mysql_user, mysql_password, database, 0, NULL, 0))
    {
      if(verbose)
	{
	  fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
	}
      exitApp(mysql_errno(conn));
    }
  if(mysql_query(conn, searchString))
    {
      if(verbose)
	{
	  fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
	}
      exitApp(mysql_errno(conn));
    }
  res = mysql_use_result(conn);
  if((row = mysql_fetch_row(res)) != NULL)
    {
      fprintf(stdout,
	      "DistributorID: %s (%s)\n", row[0], row[1]);
      matches++;
    }
  mysql_free_result(res);
  mysql_close(conn);
  return matches;
}

int searchMovieGeneres(char *searchString)
{
  long matches = 0;
  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  char *server = "localhost";
  char *mysql_user = user;
  //printf("user: %s\n", user);
  char *mysql_password = password;
  char *database = "mymovies";
  conn = mysql_init(NULL);
  if(conn == NULL)
    {
      if(verbose)
	{
	  fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
	}
      exitApp(mysql_errno(conn));
    }
  if(!mysql_real_connect(conn, server, mysql_user, mysql_password, database, 0, NULL, 0))
    {
      if(verbose)
	{
	  fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
	}
      exitApp(mysql_errno(conn));
    }
  if(mysql_query(conn, searchString))
    {
      if(verbose)
	{
	  fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
	}
      exitApp(mysql_errno(conn));
    }
  res = mysql_use_result(conn);
  while((row = mysql_fetch_row(res)) != NULL)
    {
      fprintf(stdout,
	      "GenereID: %s (%s)\n",row[0], row[1]);
      matches++;
    }
  mysql_free_result(res);
  mysql_close(conn);
  return matches;
}

char *ggid, *gid;
int getDistributorID(int max)
{
  char input[BUFSIZ], *p;
  int result;
  printf("Please enter a distributor ID from the above list: ");
  for(;;){        /* infinite "for" loop */
    
    fgets(input , sizeof(input), stdin);
 
    result = strtol(input , &p, 10);
    
    if(input[0] != '\n' && result > 0 && (*p == '\n' || *p == '\0'))
      {
	if(result > max)
	  {
	    printf("You can only enter a value between 1 and %d.\n", max);
	    result = 0;
	  }
	else
	  {
	    break;
	  }
      }
    else
      printf("Invalid input !\n\nPlease enter a distributor ID from the above list: ");
    result = 0; 
    printf("Please enter a positive integer : ");
  }
  printf("input: %s\n", input);
  gid = input;
  printf("You've entered the number %ld\n", result);
  return result;
}

int addMovie(int rec)
{
  if(line_read)
    {
      free(line_read);
      line_read = (char *)NULL;
    }
  line_read = readline("Enter the title of the movie: ");
  if(line_read && *line_read)
    {
      add_history(line_read);
    }
  char *movieName = line_read;
  printf("movieName: %s\n", movieName);
  int lc_length = strlen(movieName);
  if(lc_length == 1)
    {
      if(*movieName == 'q')
	{
	  exitApp(0);
	}
    }
  else if(lc_length > 100)
    {
      fprintf(stderr, "The movie title is too long.\n");
      exitApp(1);
    }
  
  int addedMovieDistributors = searchMovieDistributors("SELECT * FROM tbl_movieCompany;");
  if(addedMovieDistributors == 0)
    {
      fprintf(stdout, 
	      "You have not added any movie distributors.\n"
	      "Would you like to do so? (y or n) ");
      char ans;
      scanf("%1s", &ans);
      if(strcmp(&ans, "y") == 0)
	{
	  addMovieDistributor(0);
	}
      else if(strcmp(&ans, "n") == 0)
	{
	  fprintf(stderr, "You must add at least one movie distributor before you can add a movie to your database.\n");
	  exitApp(1);
	}
      else
	{
	  fprintf(stderr, "Error: You must answer either y (for yes) or n (for no).\n");
	  exitApp(1);
	}
    }
  char input[BUFSIZ], *p;
  int result;
  printf("Please enter a distributor ID from the above list: ");
  for(;;){        /* infinite "for" loop */
    
    fgets(input , sizeof(input), stdin);
    if(input[strlen(input) -1] == '\n')
      {
	input[strlen(input) -1] = '\0';
      }
    result = strtol(input , &p, 10);
    if(input[0] != '\n' && result > 0 && (*p == '\n' || *p == '\0'))
      {
	if(result > addedMovieDistributors)
	  {
	    printf("You can only enter a value between 1 and %d.\n", addedMovieDistributors);
	    result = 0;
	  }
	else
	  {
	    break;
	  }
      }
    else
      printf("Invalid input !\n\nPlease enter a distributor ID from the above list: ");
    result = 0; 
    printf("Please enter a positive integer : ");
  }
  printf("input: %s\n", input);
  gid = input;
  printf("You've entered the number %ld\n", result);
  printf("gid: %s\n", gid);
  int gmg = searchMovieGeneres("SELECT * FROM tbl_genere;");
  if(gmg == 0)
    {
      fprintf(stdout,
	      "You have not added any movie generes.\n"
	      "Would you like to add one now? (y or n) ");
      char c;
      scanf("%1s", &c);
      if(strcmp(&c, "y") == 0)
	{
	  addMovieGenere(0);
	}
      else if(strcmp(&c, "n") == 0)
	{
	  fprintf(stderr, "You must add at least one movie genere before you can add a movie to your database.\n");
	}
      else
	{
	  fprintf(stderr, "Error: You must answer either y (for yes) or n (for no).\n");
	  exitApp(1);
	}
    }
  char new_input[BUFSIZ], *new_p;
  int new_result;
  printf("Please enter a genere ID from the above list: ");
  for(;;){        /* infinite "for" loop */
    
    fgets(new_input , sizeof(new_input), stdin);
    if(new_input[strlen(new_input) -1] == '\n')
    {
      new_input[strlen(new_input) -1] = '\0';
    }
    new_result = strtol(new_input , &new_p, 10);
    
    if(new_input[0] != '\n' && new_result > 0 && (*new_p == '\n' || *new_p == '\0'))
      {
	if(new_result > gmg)
	  {
	    printf("You can only enter a value between 1 and %d.\n", gmg);
	    result = 0;
	  }
	else
	  {
	    break;
	  }
      }
    else
      printf("Invalid input !\n\nPlease enter a genere ID from the above list: ");
    new_result = 0; 
    printf("Please enter a positive integer : ");
  }
  ggid = new_input;
  printf("You've entered the number %ld\n", new_result);
  fprintf(stdout, "Enter the name(s) of the actor(s)/actress(es) in the movie: ");
  char actors[100];
  fgets(actors, 98, stdin);
  if(actors[strlen(actors) -1] == '\n')
    {
      actors[strlen(actors) -1] = '\0';
    }
  char year[4];
  fprintf(stdout, "Enter the production year: ");
  scanf("%4s", &year);
  if(strlen(year) < 4)
    {
      fprintf(stderr, "You have to enter a value bigger than 1850 (i.e. 2010).\n");
    }
  if(line_read)
    {
      free(line_read);
      line_read = (char *)NULL;
    }
  line_read = readline("Enter the movie description (max 10000 characters): ");
  if(line_read && *line_read)
    {
      add_history(line_read);
    }
  char *description = line_read;
  int c_length = strlen(description);
  if(c_length == 1)
    {
      if(*description == 'q')
	{
	  exitApp(0);
	}
    }
  if(c_length > 10000)
    {
      fprintf(stderr, "You have entered a description that is too long.\n");
      exitApp(1);
    }
  printf("MovieName = %s\n", movieName);
  char insertString[10500] = "INSERT INTO tbl_movie (movieTitle, companyId, actors, productionYear, genereId, movieDescription) VALUES(\"";
  strcat(insertString, movieName);
  strcat(insertString, "\",");
  strcat(insertString, gid);
  strcat(insertString, ", \"");
  strcat(insertString, actors);
  strcat(insertString, "\",");
  strcat(insertString, year);
  strcat(insertString, ",");
  strcat(insertString, ggid);
  strcat(insertString, ",\"");
  strcat(insertString, description);
  strcat(insertString, "\");");
  printf("insertString: %s\n", insertString);
  /*fprintf(stdout, "");
  fgets(movieName, 98, stdin); //reads the title of the movie
  if(movieName[strlen(movieName) -1] == '\n')
  {
    movieName[strlen(movieName) -1] = '\0';
  }
  fprintf(stdout, "");
  fgets(movieName, 98, stdin); //reads the title of the movie
  if(movieName[strlen(movieName) -1] == '\n')
  {
    movieName[strlen(movieName) -1] = '\0';
  }*/

   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;
   char *server = "localhost";
   char *mysql_user = user;
   char *mysql_password = password;
   char *database = "mymovies";
   conn = mysql_init(NULL);
   if(conn == NULL)
     {
       if(verbose)
	 {
	   fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
	 }
       exitApp(mysql_errno(conn));
     }
   if(!mysql_real_connect(conn, server, mysql_user, mysql_password, database, 0, NULL, 0))
     {
       if(verbose)
	 {
	   fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
	 }
       exitApp(mysql_errno(conn));
     }
   if(mysql_query(conn, insertString))
     {
       if(verbose)
	 {
	   fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
	 }
       exitApp(mysql_errno(conn));
     }
   res = mysql_use_result(conn);
   fprintf(stdout, "%ld affected rows\n", (long)mysql_affected_rows(conn));
   mysql_free_result(res);
   mysql_close(conn);
   if(rec == 1)
     add();
  return 0;
}

int addMovieDistributor(int rec)
{
  signal(SIGINT, catch_int);
  signal(SIGTSTP, catch_int2);
  signal(SIGABRT, catch_int3);
  signal(SIGHUP, catch_int4);
  signal(SIGQUIT, catch_int5);
  signal(SIGBUS, catch_int7);
  signal(SIGSEGV, catch_int6);
  if(line_read)
    {
      free(line_read);
      line_read = (char *)NULL;
    }
  line_read = readline("Enter the name of the movie distributor: ");
  if(line_read && *line_read)
    {
      add_history(line_read);
    }
  char *c = line_read;
  int c_length = strlen(c);
  if(c_length == 1)
    {
      if(*c == 'q')
	{
	  exitApp(0);
	}
    }
  char insertString[200] = "INSERT INTO tbl_movieCompany (companyName) VALUES(\"";
  strcat(insertString, c);
  strcat(insertString, "\");");
  printf("InsertString: %s\n", insertString);
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;
   char *server = "localhost";
   char *mysql_user = user;
   char *mysql_password = password;
   char *database = "mymovies";
   conn = mysql_init(NULL);
   if(conn == NULL)
     {
       if(verbose)
	 {
	   fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
	 }
       exitApp(mysql_errno(conn));
     }
   if(!mysql_real_connect(conn, server, mysql_user, mysql_password, database, 0, NULL, 0))
     {
       if(verbose)
	 {
	   fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
	 }
       exitApp(mysql_errno(conn));
     }
   if(mysql_query(conn, insertString))
     {
       if(verbose)
	 {
	   fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
	 }
       exitApp(mysql_errno(conn));
     }
   res = mysql_use_result(conn);
   fprintf(stdout, "%ld affected rows\n", (long)mysql_affected_rows(conn));
   mysql_free_result(res);
   mysql_close(conn);
   if(rec == 1)
     add();
   return 0;
}

int addMovieGenere(int rec)
{
  signal(SIGINT, catch_int);
  signal(SIGTSTP, catch_int2);
  signal(SIGABRT, catch_int3);
  signal(SIGHUP, catch_int4);
  signal(SIGQUIT, catch_int5);
  signal(SIGBUS, catch_int7);
  signal(SIGSEGV, catch_int6);
  if(line_read)
    {
      free(line_read);
      line_read = (char *)NULL;
    }
  line_read = readline("Enter the movie genere name: ");
  if(line_read && *line_read)
    {
      add_history(line_read);
    }
  char *c = line_read;
  int c_length = strlen(c);
  if(c_length == 1)
    {
      if(*c == 'q')
	{
	  exitApp(0);
	}
    }
  char insertString[200] = "INSERT INTO tbl_genere (genereName) VALUES(\"";
  strcat(insertString, c);
  strcat(insertString, "\");");
  printf("InsertString: %s\n", insertString);
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;
   char *server = "localhost";
   char *mysql_user = user;
   char *mysql_password = password;
   char *database = "mymovies";
   conn = mysql_init(NULL);
   if(conn == NULL)
     {
       if(verbose)
	 {
	   fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
	 }
       exitApp(mysql_errno(conn));
     }
   if(!mysql_real_connect(conn, server, mysql_user, mysql_password, database, 0, NULL, 0))
     {
       if(verbose)
	 {
	   fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
	 }
       exitApp(mysql_errno(conn));
     }
   if(mysql_query(conn, insertString))
     {
       if(verbose)
	 {
	   fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
	 }
       exitApp(mysql_errno(conn));
     }
   res = mysql_use_result(conn);
   fprintf(stdout, "%ld affected rows\n", (long)mysql_affected_rows(conn));
   mysql_free_result(res);
   mysql_close(conn);
   if(rec == 1)
     add();
   return 0;
}
