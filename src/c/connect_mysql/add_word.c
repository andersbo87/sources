/*
 *  add_word.c
 *  connect_mysql
 *
 *  Created by Anders Bolt-Evensen on 4/9/10.
 *  Copyright 2010 Høgskolen i Østfold. All rights reserved.
 *
 */

#include "add_word.h"
#include <mysql.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "search_word.h"

int addEnglishRecursive() //adds a new word to the database. commented printf() functions are kept and used for debugging purposes.
{
	char en_word[95]; 
	char no_word[95];
	MYSQL *conn;
	char *server = "localhost";                                                
	char *user = "root";
	char *password = "klaand"; /* set me first */
	char *database = "enno_dic";
	int success;
	conn = mysql_init(NULL);
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
	int isTableCreated = createEnTable();
	if(isTableCreated != 0)
	{
		fprintf(stderr, "En feil har oppstått: %u %s\n", mysql_errno(conn), mysql_error(conn));
		success = isTableCreated;
		return isTableCreated;
	}
	
	if (conn == NULL) {
		fprintf(stderr, "Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		fprintf(stderr, "Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	printf("Skriv inn det engelske ordet du vil legge inn (maks 90 tegn): ");
	fgets(en_word, 95, stdin);
	if(en_word[strlen(en_word) -1] == '\n')
		en_word[strlen(en_word) -1] = '\0';
	int enw_length = strlen(en_word);
	if(enw_length >= 91)
	{
		fprintf(stderr, "Ordet du skrev inn, er for langt\n");
		return 1;
	}
	//scanf("%s", &en_word);
	//printf("%s\n", en_word);
	printf("Skriv inn den norske betydningen av ordet (maks 90 tegn): ");
	fgets(no_word, 95, stdin);
	int now_length = strlen(no_word);
	if(no_word[strlen(no_word) -1] == '\n')
		no_word[strlen(no_word) -1] = '\0';
	if(now_length >= 91)
	{
		fprintf(stderr, "Den norske betydningen av uttrykket er for langt\n");
		return 1;
	}
	//scanf("%s", &no_word);
	//printf("%s\n", no_word);
	char nc1[350] = "INSERT INTO tbl_words (en_word, no_word) VALUES('";
	// printf("a\n");
	char *nc2 = strcat(nc1, en_word);
	// printf("b\n");
	//printf("%s\n", en_word);
	//printf("%s\n", nc1);
	char *nc3 = strcat(nc2, "','");
	char *nc4 = strcat(nc3, no_word);
	char *nc5 = strcat(nc4, "');");
	//printf("%s\n", nc4);
	if (mysql_query(conn, nc4)) {
		printf("Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	else
	{
		printf("Ordlistetabellen ble oppdatert og %ld ord ble lagt til.\n", (long) mysql_affected_rows(conn));
	}
	
	mysql_close(conn);
	addEnglishRecursive();
	return 0;
}

int addEnglish() //adds a new word to the database. commented printf() functions are kept and used for debugging purposes.
{
	char en_word[95]; 
	char no_word[95];
	MYSQL *conn;
	char *server = "localhost";                                                
	char *user = "root";
	char *password = "klaand"; /* set me first */
	char *database = "enno_dic";
	int success;
	conn = mysql_init(NULL);
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
	int isTableCreated = createEnTable();
	if(isTableCreated != 0)
	{
		fprintf(stderr, "En feil har oppstått: %u %s\n", mysql_errno(conn), mysql_error(conn));
		success = isTableCreated;
		return isTableCreated;
	}
	
	if (conn == NULL) {
		fprintf(stderr, "Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		fprintf(stderr, "Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	fprintf(stdout,"Skriv inn det engelske ordet du vil legge inn (maks 90 tegn): ");
	fgets(en_word, 95, stdin);
	if(en_word[strlen(en_word) -1] == '\n')
		en_word[strlen(en_word) -1] = '\0';
	int enw_length = strlen(en_word);
	if(enw_length >= 91)
	{
		fprintf(stderr, "Ordet du skrev inn, er for langt\n");
		return 1;
	}
	//scanf("%s", &en_word);
	//printf("%s\n", en_word);
	if(enw_length != 0)
	{
		printf("Skriv inn den norske betydningen av ordet (maks 90 tegn): ");
		fgets(no_word, 95, stdin);
		
	}
	else {
		fprintf(stderr, "You have to enter an English word\n");
		return 1;
	}

	int now_length = strlen(no_word);
	if(no_word[strlen(no_word) -1] == '\n')
	no_word[strlen(no_word) -1] = '\0';
	if(now_length >= 91)
	{
		fprintf(stderr, "Den norske betydningen av uttrykket er for langt\n");
		return 1;
	}
	//scanf("%s", &no_word);
	//printf("%s\n", no_word);
	char nc1[350] = "INSERT INTO tbl_words (en_word, no_word) VALUES('";
	// printf("a\n");
	char *nc2 = strcat(nc1, en_word);
	// printf("b\n");
	//printf("%s\n", en_word);
	//printf("%s\n", nc1);
	char *nc3 = strcat(nc2, "','");
	char *nc4 = strcat(nc3, no_word);
	char *nc5 = strcat(nc4, "');");
	//printf("%s\n", nc4);
	if (mysql_query(conn, nc4)) {
		printf("Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	else
	{
		printf("Ordlistetabellen ble oppdatert og %ld ord ble lagt til.\n", (long) mysql_affected_rows(conn));
	}
	
	mysql_close(conn);
	return 0;
}
int addNorwegian() //adds a new word to the database. commented printf() functions are kept and used for debugging purposes.
{
	char no_word[95]; 
	char en_word[95];
	MYSQL *conn;
	char *server = "localhost";                                                
	char *user = "root";
	char *password = "klaand"; /* set me first */
	char *database = "noen_dic";
	int success;
	conn = mysql_init(NULL);
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
	int isTableCreated = createNoTable();
	if(isTableCreated != 0)
	{
		fprintf(stderr, "En feil har oppstått: %u %s\n", mysql_errno(conn), mysql_error(conn));
		success = isTableCreated;
		return isTableCreated;
	}
	if (conn == NULL) {
		fprintf(stderr, "Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		fprintf(stderr, "Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	printf("Skriv inn det norske ordet du vil legge inn (maks 90 tegn): ");
	fgets(no_word, 95, stdin);
	if(no_word[strlen(no_word) -1] == '\n')
		no_word[strlen(no_word) -1] = '\0';
	int now_length = strlen(no_word); //now means "Norwegian" word (in this case)
	if(now_length >= 91)
	{
		fprintf(stderr, "Ordet du skrev inn, er for langt\n");
		return 1;
	}
	//scanf("%s", &en_word);
	//printf("%s\n", en_word);
	printf("Skriv inn den engelske betydningen av ordet (maks 90 tegn): ");
	fgets(en_word, 95, stdin);
	int enw_length = strlen(en_word);
	if(en_word[strlen(en_word) -1] == '\n')
		en_word[strlen(en_word) -1] = '\0';
	if(enw_length >= 91)
	{
		fprintf(stderr, "Den engelske betydningen av uttrykket er for langt\n");
		return 1;
	}
	//scanf("%s", &no_word);
	//printf("%s\n", no_word);
	char nc1[350] = "INSERT INTO tbl_words (no_word, en_word) VALUES('";
	// printf("a\n");
	char *nc2 = strcat(nc1, no_word);
	// printf("b\n");
	//printf("%s\n", en_word);
	//printf("%s\n", nc1);
	char *nc3 = strcat(nc2, "','");
	char *nc4 = strcat(nc3, en_word);
	char *nc5 = strcat(nc4, "');");
	printf("%s\n", nc4);
	if (mysql_query(conn, nc4)) {
		printf("Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	else
	{
		printf("Ordlistetabellen ble oppdatert og %ld ord ble lagt til.\n", (long) mysql_affected_rows(conn));
	}
	
	mysql_close(conn);
	return 0;
}

int getRecords(char en_word)
{
	int recs = 0;
	MYSQL *conn;
	char *server = "localhost";                                                
	char *user = "root";
	char *password = "klaand"; /* set me first */
	char *database = "enno_dic";
	MYSQL_RES *res;
	MYSQL_ROW row;
	conn = mysql_init(NULL);
	
	if (conn == NULL) {
		printf("Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	
	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		printf("Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	
	if(mysql_query(conn, "SELECT * FROM tbl_words"))
	{
		printf("Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;// mysql_errno(conn), mysql_error(conn);
	}
	
	res = mysql_use_result(conn);
	
    while((row = mysql_fetch_row(res)) != NULL)
	{
		//printf("%s\n", row[0]);
		recs++;
		//printf("%d\n", recs);
	}
    printf("Antall ord i databasen: %d \n", recs);
	mysql_free_result(res);
	mysql_close(conn);
	return 0;
}

