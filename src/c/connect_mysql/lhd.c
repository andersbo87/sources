#include <stdio.h>
#include <mysql.h>
#include <sys/stat.h>
#include <string.h>
#include "remove_word.h"
#include "search_word.h"
#include "add_word.h"

int addEnglish();
int addNorwegian();
int getRecords(char en_word);
int makeBackupOfDatabase();
int printHelp();
int printAllEnglishWords();
int printAllNorwegianWords();
int system(const char *);
void checkTermType();
char getenv(const char *);
int main (int argc, const char * argv[]) 
{
	//check if the databases exists
	struct stat st;
	if(!stat("/usr/var/enno_dic",&st) == 0)
	{
        //fprintf(stdout,"/usr/var/little_house is not present\n");
		if(createEnNoDic() == 0)
		{
			//printf("sjekk");
			createEnTable();
			//insertTable();
		}
	}
	if(!stat("/usr/var/noen_dic",&st) == 0)
	{
        //fprintf(stdout,"/usr/var/little_house is not present\n");
		if(createNoEnDic() == 0)
		{
			//printf("sjekk");
			createNoTable();
			//insertTable();
		}
	}
	if (argc == 2 && strcmp("-r", argv[1]) == 0) 
	{
		int recs = getRecords((long)argv[1]);
		return recs;
	}
	else if(argc == 2 && strcmp("-b", argv[1]) == 0)
	{
		int res1 = 0;
		makeBackupOfDatabase();
		return res1;
	}
	else if(argc == 2 && strcmp("-h", argv[1]) == 0)
	{
		printHelp();
		return 0;
	}
	else if(argc == 2 && strcmp("--help", argv[1]) == 0)
	{
		printHelp();
		return 0;
	}
	else if(argc == 3 && strcmp("-p", argv[1]) == 0)// || argc == 2 && strcmp("-pe", argv[1]) == 0)
	{
		if(argc == 3 && strcmp("-e", argv[2]) == 0)
		{
			printAllEnglishWords();
			return 0;
		}
		else if(argc == 3 && strcmp("-n", argv[2]) ==0)
		{
			printAllNorwegianWords();
			return 0;
		}
		else if(argc == 2 && strcmp("e", argv[1]) == 0)
		{
			printAllEnglishWords();
			return 0;
		}
		else
		{
			printf("%d\n", argc);
			printHelp();
		}
	}
	else if (argc == 2 && strcmp("-pe", argv[1]) == 0)
	{
		printAllEnglishWords();
		return 0;
	}
	else if (argc == 2 && strcmp("-pn", argv[1]) == 0)
	{
		printAllNorwegianWords();
		return 0;
	}
	else if(argc == 2 && strcmp("-d", argv[1]) == 0)
	{
		if(argc == 3 && strcmp("-e", argv[2]) == 0)
		{
			removeEnWord();
		}
		else if(argc == 3 && strcmp("-n", argv[2]) == 0)
		{
			removeNoWord();
		}
	}
	else if(argc == 3 && strcmp("-s", argv[1]) == 0)
	{
		if(argc == 3 && strcmp("-e", argv[2]) == 0)
		{
			int res = 0;
			res = searchEnglish();
			return res;
		}
		else if(argc == 3 && strcmp("-n", argv[2]) == 0) 
		{
			int res = 0;
			/*if(checkTermType() == "/dev/console")
			{
				printf("Advarsel: Du koblet til via /dev/console som ikke \"virker\" med norske bokstaver. Dette betyr at enkelte ord ikke gir treff under oppslag i databasen.");
			}*/
			checkTermType();
			res = searchNorwegian();
			return res;
		}
		else
		{
			printHelp();
		}
	}
	else if(argc == 3 && strcmp("-a", argv[1]) == 0)
	{
		if(argc == 3 && strcmp("-e", argv[2]) == 0)
		{
			int res = 0;
			res = addEnglish();
			return res;
		}
		else if(argc == 3 && strcmp("-n", argv[2]) == 0) 
		{
			int res = 0;
			/*if(checkTermType() == "/dev/console")
			{
				printf("Advarsel: Du koblet til via /dev/console som ikke \"virker\" med norske bokstaver.");
			}*/
			res = addNorwegian();
			return res;
		}
		else
		{
			printHelp();
		}
	}
	else if(argc == 4 && strcmp("-a", argv[1]) == 0)
	{
		if(argc == 4 && strcmp("-e", argv[2]) == 0)
		{
			if(argc == 4 && strcmp("-r", argv[3]) == 0)
			{
				int res = 0;
				res = addEnglishRecursive();
				return res;
			}
		}
	}
	else if(argc == 3 && strcmp("-u", argv[1]) == 0)
	{
		if(argc == 3 && strcmp("-e", argv[2]) == 0)
		{
			int res = 0;
			res = updateEnglishWord();
			return res;
		}
		else if(argc == 3 && strcmp("-n", argv[2]) == 0) 
		{
			int res = 0;
			/*if(checkTermType() == "/dev/console")
			{
				printf("Advarsel: Du koblet til via /dev/console som ikke \"virker\" med norske bokstaver. Dette betyr at enkelte ord ikke kan oppdateres Logg inn på terminalen fra det grafiske grensesnittet og start programmet derfra.");
			}*/
			res = updateNorwegianWord();
			return res;
		}
		else
		{
			printHelp();
		}
	}
	else 
	{
		printf("%d\n", argc);
		printHelp();
	}
}
int printAllEnglishWords()
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *server = "localhost";
	char *user = "root";
	char *password = "klaand"; /* set me first */
	char *database = "enno_dic";
	conn = mysql_init(NULL);
	int success;
	if (conn == NULL) 
	{
		fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return mysql_errno(conn);
	}
	
	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) 
	{
		fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return mysql_errno(conn);
	}
	if(mysql_query(conn, "SELECT en_word, no_word FROM tbl_words ORDER BY en_word ASC;"))
	{
		fprintf(stderr, "Feil: %s\n", mysql_error(conn));
		success = mysql_errno(conn);
		return mysql_errno(conn);
	}
	
	res = mysql_use_result(conn);
	
	/* output table name */
	printf("Resultat:\n");
	if((row = mysql_fetch_row(res)) == NULL)
	{
		printf("Databasen er tom.\n");
		return success;
	}
	else 
	{
		printf("%s betyr %s \n", row[0], row[1]);
	}

	while((row = mysql_fetch_row(res)) != NULL)
	{
		// while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s betyr %s \n", row[0], row[1]);
	}
	return success;
}

int printAllNorwegianWords()
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *server = "localhost";
	char *user = "root";
	char *password = "klaand"; /* set me first */
	char *database = "noen_dic";
	conn = mysql_init(NULL);
	int success;
	if (conn == NULL) 
	{
		fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return mysql_errno(conn);
	}
	
	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) 
	{
		fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return mysql_errno(conn);
	}
	if(mysql_query(conn, "SELECT no_word, en_word FROM tbl_words ORDER BY no_word ASC;"))
	{
		fprintf(stderr, "Feil: %s\n", mysql_error(conn));
		success = mysql_errno(conn);
		return mysql_errno(conn);
	}
	
	res = mysql_use_result(conn);
	
	/* output table name */
	printf("Resultat:\n");
	if((row = mysql_fetch_row(res)) == NULL)
	{
		printf("Databasen er tom.\n");
		return success;
	}
	else 
	{
		printf("%s betyr %s \n", row[0], row[1]);
	}

	while((row = mysql_fetch_row(res)) != NULL)
	{
		// while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s betyr %s \n", row[0], row[1]);
	}
	return success;
}

int printHelp(void)
{
  //funksjon som skal printe ut kort informasjon om hvordan programmet skal brukes.
  printf("Følgende opsjoner er tilgjengelige:\n-a:\t-e: Legg til et nytt engelsk ord i databasen\n\t-n: Legg til et norsk ord i databasen\n-b: Ta backup av databasen når programmet er ferdig.\n-d: Fjerne ord fra databasen\n-p: Skriver ut alle\n\t -e engelske ord\n\t-n norske ord\n-r: Teller opp antall ord i databasen\n-s:\t-e: Søk etter engelske ord\n\t-n: Søk etter norske ord\n\tHvis søket ikke returnerer noen treff, kan du legge inn det nye ordet.\n-u: Oppdatere betydningen av et allerede eksisterende ord\n-h eller --help: Skriver ut denne hjelpen\n");
	return 0;
}


/*funksjonen nedenfor skal forsøke å ta en backup av filen (etter å ha "lekt" meg litt for mye med mappen "data"
 som ligger i katalogen der mysql ligger, vet jeg at dette kan være en god idé…
 siden det ikke finnes noen C-funksjoner som støtter dette, etter det jeg vet om, bruker jeg funksjonen systen()
 som kan bruke til å starte opp andre programmer…*/
int makeBackupOfDatabase(void)
{
  system("mysqldump -u root -p --databases dic_little_house > /Users/Shared/backup.sql");
	return 0;
}

int startProcess(void)
{
  /*int nr;
  nr = fork();
  if(nr == 0)
  {
    char *argv[3];
    argv[0] = strdup("add_word");
    argv[1] = strdup("-a");
    argv[2] = NULL;
    execvp(argv[0], argv);
  }
  waitpid(nr, NULL, 0);*/
	return 0;
}

void checkTermType()
{
	char termType[13];
	//char *pHome = getenv("HOME");
	system("echo $HOME &> /tmp/noe.txt");
	char pHome[30];
	fgets(pHome, 30, fopen("/tmp/noe.txt", "rb"));
	if(pHome[strlen(pHome) -1] == '\n')
	{
		pHome[strlen(pHome) -1] = '\0';
	}
	if(pHome != NULL)
	{
		char *filename = strcat(pHome,"/ttyinfo.txt");
		fgets(termType, 13, fopen(filename, "rb")); //legger til innholdet i $HOME/ttyinfo.txt i variabelen termType
		if(termType[strlen(termType) -1] == '\n')
		{
			termType[strlen(termType) -1] = '\0';
		}
		if(termType != NULL) //sjekker om termType er tom
		{
			//printf("%d\n",strcmp(termType, "/dev/console"));
			if(strcmp(termType, "/dev/console") == 0)
			{
				printf("%s\n", termType);
				printf("Advarsel: Du er koblet til via /dev/console som ikke \"virker\" med norske bokstaver. Dette betyr at enkelte ord ikke gir treff under oppslag i databasen, og at enkelte ord ikke vil la seg oppdateres.\n");
			}
			else
			{
				//printf("%s\n", termType);
			}
			//printf("%s", terminal);
		}
	}
	else
	{
		printf("null\n");
	}
}
