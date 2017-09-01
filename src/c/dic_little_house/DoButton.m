//
//  DoButton.m
//  dic_little_house
//
//  Created by Anders Bolt-Evensen on 12/30/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import "DoButton.h"
#import <mysql.h>


@implementation DoButton
- (IBAction)doSomething:(id)pId;
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	char *server;// = "localhost";
	char *user = "root";
	char *password = "klaand"; /* set me first */
	char *database = "dic_little_house";
	
	conn = mysql_init(NULL);
	
	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) 
	{
		//Opprette databasen
		int isCreated = createDatabase();
		if(isCreated != 0)
		{
			fprintf(stderr, "En feil har oppstått: %s\n", mysql_error(conn));
			return isCreated;
		}
	}
	else
	{
		printf("Du er nå koblet til databasen\n");
	}
	char *read[150];
	printf("Skriv inn et søkeord (maks 150 tegn): ");
	NSString *str = [textField1 stringValue];
	//scanf("%s", read);
	/*de neste 2 linjene kobler sammen ordet brukeren oppga til 
	 selve SQL-spørringen som skal kjøres. Dette kan sikkert gjøres på en enklere måte*/ 
	char c1[150] = "SELECT en_word, no_word FROM tbl_words WHERE en_word = '"; 
	char c2 = strcat(c1, strcat(read,"';"));
	//printf("%s\n\n", &c1);
	//char noe = scanf("SELECT en_word, no_word FROM tbl_words WHERE en_word = \"%s\";", &read);
	if (mysql_query(conn, &c1)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		return 1;
	}
	
	res = mysql_use_result(conn);
	
	/* output table name */
	printf("Resultat:\n");
	if((row = mysql_fetch_row(res)) != NULL)
	{
		// while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s betyr %s \n", row[0], row[1]);
		return 0;
	}
	else
	{
		NSLog(@"Ingen treff");
		/*while(1)
		{
			printf("Beklager, men fant ingen treff. Vil du legge til dette ordet nå (j,n)? ");
			char answer;
			scanf("%s", &answer);
			if(answer == 'j')
			{
				startProcess();
				break;
			}
			else if(answer == 'n')
				break;
			else
				printf("Vennligst svar j for ja eller n for nei.\n");
		}*/
	}
	/* close connection */
	mysql_free_result(res);
	mysql_close(conn);
	return 0;
	//connectAndShowResults();
	//NSLog(@"Hi there");
} // end doSomething
int createDatabase() //oppretter databasen hvis den ikke finnes fra før.
{
	MYSQL *conn;
	char *server;// = "localhost";
	char *user = "root";
	char *password = "klaand"; /* set me first */
	char *database = "dic_little_house";
	conn = mysql_init(NULL);
	
	if (conn == NULL) {
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	
	if(!mysql_real_connect(conn, server, user, password, NULL, 0, NULL, 0)) 
	{
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	
	if (mysql_query(conn, "create database dic_little_house")) {
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	else
	{
		printf("Databasen dic_little_house ble opprettet\n");
	}
	
	mysql_close(conn);
	createTable();
	return 0;
}

int createTable() //oppretter tabellen hvis denne ikke finnes fra før
{
	MYSQL *conn;
	char *server;// = "localhost";
	char *user = "root";
	char *password = "klaand"; /* set me first */
	char *database = "dic_little_house";
	conn = mysql_init(NULL);
	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) 
	{
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	if (mysql_query(conn, "create table tbl_words(id int not null auto_increment, en_word varchar(150) unique not null, no_word varchar(150) not null, primary key(id, en_word));")) {
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	else{
		printf("Tabellen som skal inneholde ordene i \"ordlisten\" ble opprettet.\n");
	}
	mysql_close(conn);
	connectAndShowResults();
	return 0;
}

int connectAndShowResults()//"kobler til" databasen, lar brukeren skrive inn søkeordet og viser resultatet
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	char *server;// = "localhost";
	char *user = "root";
	char *password = "klaand"; /* set me first */
	char *database = "dic_little_house";
	
	conn = mysql_init(NULL);
	
	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) 
	{
		//Opprette databasen
		int isCreated = createDatabase();
		if(isCreated != 0)
		{
			fprintf(stderr, "En feil har oppstått: %s\n", mysql_error(conn));
			return isCreated;
		}
	}
	else
	{
		printf("Du er nå koblet til databasen\n");
	}
	char *read[150];
	printf("Skriv inn et søkeord (maks 150 tegn): ");
	scanf("%s", read);
	/*de neste 2 linjene kobler sammen ordet brukeren oppga til 
	 selve SQL-spørringen som skal kjøres. Dette kan sikkert gjøres på en enklere måte*/ 
	char c1[150] = "SELECT en_word, no_word FROM tbl_words WHERE en_word = '"; 
	char c2 = strcat(c1, strcat(read,"';"));
	//printf("%s\n\n", &c1);
	//char noe = scanf("SELECT en_word, no_word FROM tbl_words WHERE en_word = \"%s\";", &read);
	if (mysql_query(conn, &c1)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		return 1;
	}
	
	res = mysql_use_result(conn);
	
	/* output table name */
	printf("Resultat:\n");
	if((row = mysql_fetch_row(res)) != NULL)
	{
		// while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s betyr %s \n", row[0], row[1]);
		return 0;
	}
	else
	{
		NSLog(@"Ingen treff");
		while(1)
		{
			printf("Beklager, men fant ingen treff. Vil du legge til dette ordet nå (j,n)? ");
			char answer;
			scanf("%s", &answer);
			if(answer == 'j')
			{
				startProcess();
				break;
			}
			else if(answer == 'n')
				break;
			else
				printf("Vennligst svar j for ja eller n for nei.\n");
		}
	}
	/* close connection */
	mysql_free_result(res);
	mysql_close(conn);
	return 0;
}
int startProcess(void)
{
	int nr;
	nr = fork();
	if(nr == 0)
	{
		char *argv[3];
		argv[0] = strdup("./add_word");
		argv[1] = strdup("-a");
		argv[2] = NULL;
		execvp(argv[0], argv);
	}
	waitpid(nr, NULL, 0);
}

@end
