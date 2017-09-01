/*
 *  search_word.c
 *  connect_mysql
 *
 *  Created by Anders Bolt-Evensen on 4/9/10.
 *  Copyright 2010 Høgskolen i Østfold. All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include "search_word.h"
void catch_no_int5(int sig_num)
{
	signal(SIGQUIT, catch_no_int5);
	printf("\n***Caught ctrl-D signal***\n");
    printf("Please press ctrl-c on your keyboard to quit\n");
	searchNorwegian();
}
void catch_no_int4(int sig_num)
{
	signal(SIGHUP, catch_no_int4);
	printf("\n***Caught SIGHUP signal***\n");
    printf("Please press ctrl-c on your keyboard to quit\n");
	searchNorwegian();
}
void catch_no_int3(int sig_num)
{
	signal(SIGABRT, catch_no_int3);
	printf("\n***Caught ctrl-\\ signal***\n");
    printf("Please press ctrl-c on your keyboard to quit\n");
	searchNorwegian();
}
void catch_no_int2(int sig_num) //function that prevents the user from quitting the "application" by using ctrl-z
{
	signal(SIGTSTP, catch_no_int2);
	printf("\n***Caught ctrl-z signal***\n");
    printf("Please press ctrl-c on your keyboard to quit\n");
	searchNorwegian();
}
void catch_no_int(int sig_num)
{
    /* re-set the signal handler again to catch_int, for next time */
    signal(SIGINT, catch_no_int);
    printf("\n***Caught ctrl-c signal***\n");
	printf("Please enter \"q\" to exit the application.\n");
	//code to save the contents of readline's history...
	searchNorwegian();
}
void catch_en_int5(int sig_num)
{
	signal(SIGQUIT, catch_en_int5);
	printf("\n***Caught ctrl-D signal***\n");
    printf("Please press ctrl-c on your keyboard to quit\n");
	searchEnglish();
}
void catch_en_int4(int sig_num)
{
	signal(SIGHUP, catch_en_int4);
	printf("\n***Caught SIGHUP signal***\n");
    printf("Please press ctrl-c on your keyboard to quit\n");
	searchEnglish();
}
void catch_en_int3(int sig_num)
{
	signal(SIGABRT, catch_en_int3);
	printf("\n***Caught ctrl-\\ signal***\n");
    printf("Please press ctrl-c on your keyboard to quit\n");
	searchEnglish();
}
void catch_en_int2(int sig_num) //function that prevents the user from quitting the "application" by using ctrl-z
{
	signal(SIGTSTP, catch_en_int2);
	printf("\n***Caught ctrl-z signal***\n");
    printf("Please press ctrl-c on your keyboard to quit\n");
	searchEnglish();
}
void catch_en_int(int sig_num)
{
    /* re-set the signal handler again to catch_int, for next time */
    signal(SIGINT, catch_en_int);
    printf("\n***Caught ctrl-c signal***\n");
	printf("Please enter \"q\" to exit the application.\n");
	//code to save the contents of readline's history...
	searchEnglish();
}
int createEnNoDic() //oppretter databasen hvis den ikke finnes fra før.
{
	MYSQL *conn;
	char *server = "localhost";
	char *user = "root";
	char *password = "klaand"; /* set me first */
	//char *database = "dic_little_house";
	conn = mysql_init(NULL);
	
	if (conn == NULL) 
	{
		fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return mysql_errno(conn);
	}
	
	if(!mysql_real_connect(conn, server, user, password, NULL, 0, NULL, 0)) 
	{
		fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return mysql_errno(conn);
	}
	if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS enno_dic DEFAULT CHARACTER SET utf8 COLLATE UTF8_UNICODE_CI;"))
	{
		fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return mysql_errno(conn);
	}
	mysql_close(conn);
	return 0;
}
int createNoEnDic()
{
	MYSQL *conn;
	char *server = "localhost";
	char *user = "root";
	char *password = "klaand"; /* set me first */
	//char *database = "dic_little_house";
	conn = mysql_init(NULL);
	
	if (conn == NULL) 
	{
		fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return mysql_errno(conn);
	}
	
	if(!mysql_real_connect(conn, server, user, password, NULL, 0, NULL, 0)) 
	{
		fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return mysql_errno(conn);
	}
	if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS noen_dic DEFAULT CHARACTER SET utf8 COLLATE UTF8_UNICODE_CI;"))
	{
		fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return mysql_errno(conn);
	}
	mysql_close(conn);
	return 0;
}
int createEnTable() //oppretter tabellen hvis denne ikke finnes fra før
{
	MYSQL *conn;
	char *server = "localhost";
	char *user = "root";
	char *password = "klaand"; /* set me first */
	char *database = "enno_dic";
	conn = mysql_init(NULL);
	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) 
	{
		//fprintf(stderr,
		fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return mysql_errno(conn);
	}
	if (mysql_query(conn, "create table if not exists tbl_words(id int not null auto_increment, en_word varchar(150) unique not null, no_word varchar(150) not null, primary key(id, en_word));"))
	{
		fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return mysql_errno(conn);
	}
	mysql_close(conn);
	return 0;
}
int createNoTable() //oppretter tabellen hvis denne ikke finnes fra før
{
	MYSQL *conn;
	char *server = "localhost";
	char *user = "root";
	char *password = "klaand"; /* set me first */
	char *database = "noen_dic";
	conn = mysql_init(NULL);
	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) 
	{
		//fprintf(stderr,
		fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return mysql_errno(conn);
	}
	if (mysql_query(conn, "create table if not exists tbl_words(id int not null auto_increment, en_word varchar(150) unique not null, no_word varchar(150) not null, primary key(id, en_word));"))
	{
		fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return mysql_errno(conn);
	}
	mysql_close(conn);
	return 0;
}
int searchNorwegian()//"kobler til" databasen, lar brukeren skrive inn søkeordet og viser resultatet
{	
	signal(SIGINT, catch_no_int);
	signal(SIGTSTP, catch_no_int2);
	signal(SIGABRT, catch_no_int3);
	signal(SIGHUP, catch_no_int4);
	signal(SIGQUIT, catch_no_int5);
	int success = 0;
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int times;//antall ganger
	char *server = "localhost";
	char *user = "root";
	char *password = "klaand"; /* set me first */
	char *database = "noen_dic";
	
	conn = mysql_init(NULL);
	
	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) 
	{
		//Opprette databasen
		/*int isCreated = createDatabase();
		if(isCreated != 0)
		{*/
			fprintf(stderr, "En feil har oppstått: %u %s\n", mysql_errno(conn), mysql_error(conn));
			//return isCreated;
			//success = isCreated;
		//}
	}

	if(times == 0)
	{
		//opprette tabellen hvis den ikke finnes fra før
		int isTableCreated = createNoTable();
		if(isTableCreated != 0)
		{
			fprintf(stderr, "En feil har oppstått: %u %s\n", mysql_errno(conn), mysql_error(conn));
			success = isTableCreated;
			return isTableCreated;
		}
		times=1;
	}
	char read[95];
	printf("Skriv inn ordet du ser etter (maks 90 tegn): ");
	fgets(read, 95, stdin);
	if(read[strlen(read) -1] == '\n')
	{
		read[strlen(read) -1] = '\0';
	}
	
	//scanf("%91s", read);
	int string_length = strlen(read);
	//printf("Lengden til ordet: %d\n", strlen(read));
	if(string_length == 1)
	{
		//printf("Sjekker bokstaven som ble skrevet inn: %s\n", read);
		char *p;
		p = strchr(read, 'q');
		if(p != NULL)
	    {
			exit(0);
	    }
	}
	if(string_length >= 91)
	{
		printf("Ordet du skrev inn, er for langt\n");
		return 1;
	}
	/*de neste 2 linjene kobler sammen ordet brukeren oppga til 
	 selve SQL-spørringen som skal kjøres. Dette kan sikkert gjøres på en enklere måte*/ 
	char c1[150] = "SELECT no_word, en_word FROM tbl_words WHERE no_word LIKE \"%"; 
	char c2 = strcat(c1, strcat(read,"%\";"));
	//printf("%s", c1);
	if (mysql_query(conn, &c1)) 
	{
		fprintf(stderr, "Feil: %s\n", mysql_error(conn));
		success = mysql_errno(conn);
		return mysql_errno(conn);
	}
	
	res = mysql_use_result(conn);
	
	/* output table name */
	printf("Resultat:\n");
	if((row = mysql_fetch_row(res)) != NULL)
	{
		// while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s betyr %s \n", row[0], row[1]);
	}
	else
	{
		fprintf(stdout, "Beklager, men fant ingen treff.\n");
	}
	/* close connection */
	if(success == 0)
	{
		//memset(read, 0, sizeof read);
		read[strlen(read) -1] = "";
		searchNorwegian();
	}
	else //hvis det oppsto en feil med MySQL-forbindelsen
	{
		printf("Programmet avsluttes…\n");
		mysql_free_result(res);
		mysql_close(conn);
		return success; //returnerer feilkoden
	}
}

int searchEnglish()//"kobler til" databasen, lar brukeren skrive inn søkeordet og viser resultatet
{	
	//printf("Start\n");
	signal(SIGINT, catch_en_int);
	signal(SIGTSTP, catch_en_int2);
	signal(SIGABRT, catch_en_int3);
	signal(SIGHUP, catch_en_int4);
	signal(SIGQUIT, catch_en_int5);
	int success = 0;
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int times;//antall ganger
	char *server = "localhost";
	char *user = "root";
	char *password = "klaand"; /* set me first */
	char *database = "enno_dic";
	
	conn = mysql_init(NULL);
	
	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) 
	{
		//Opprette databasen
		/*int isCreated = createDatabase();
		if(isCreated != 0)
		{*/
			fprintf(stderr, "En feil har oppstått: %u %s\n", mysql_errno(conn), mysql_error(conn));
			/*return isCreated;
			success = isCreated;
		}*/
	}
	if(times == 0)
	{
		//opprette tabellen hvis den ikke finnes fra før
		int isTableCreated = createEnTable();
		if(isTableCreated != 0)
		{
			fprintf(stderr, "En feil har oppstått: %u %s\n", mysql_errno(conn), mysql_error(conn));
			success = isTableCreated;
			return isTableCreated;
		}
		times=1;
	}
	char read[95];
	printf("Skriv inn ordet du ser etter (maks 90 tegn): ");
	fgets(read, 95, stdin);
	if(read[strlen(read) -1] == '\n')
	{
		read[strlen(read) -1] = '\0';
	}
	
	//scanf("%91s", read);
	int string_length = strlen(read);
	//printf("Lengden til ordet: %d\n", strlen(read));
	if(string_length == 1)
	{
		//printf("Sjekker bokstaven som ble skrevet inn: %s\n", read);
		char *p;
		p = strchr(read, 'q');
		if(p != NULL)
	    {
			exit(0);
	    }
	}
	if(string_length >= 91)
	{
		printf("Ordet du skrev inn, er for langt\n");
		return 1;
	}
	/*de neste 2 linjene kobler sammen ordet brukeren oppga til 
	 selve SQL-spørringen som skal kjøres. Dette kan sikkert gjøres på en enklere måte*/ 
	char c1[150] = "SELECT en_word, no_word FROM tbl_words WHERE en_word LIKE \"%"; 
	char c2 = strcat(c1, strcat(read,"%\";"));
	//printf("%s", c1);
	if (mysql_query(conn, &c1)) 
	{
		fprintf(stderr, "Feil: %s\n", mysql_error(conn));
		success = mysql_errno(conn);
		return mysql_errno(conn);
	}
	
	res = mysql_use_result(conn);
	
	/* output table name */
	printf("Resultat:\n");
	if((row = mysql_fetch_row(res)) != NULL)
	{
		// while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s betyr %s \n", row[0], row[1]);
	}
	else
	{
		fprintf(stdout,"Beklager, men fant ingen treff.\n");
	}
	/* close connection */
	if(success == 0)
	{
		//memset(read, 0, sizeof read);
		read[strlen(read) -1] = "";
		searchEnglish();
	}
	else //hvis det oppsto en feil med MySQL-forbindelsen
	{
		printf("Programmet avsluttes…\n");
		mysql_free_result(res);
		mysql_close(conn);
		return success; //returnerer feilkoden
	}
}