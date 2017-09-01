/*
 *  remove_word.c
 *  connect_mysql
 *
 *  Created by Anders Bolt-Evensen on 4/8/10.
 *  Copyright 2010 Høgskolen i Østfold. All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include "remove_word.h"
#include <string.h>
/*Fjerner ordet med den spesifiserte indeksen fra databasen*/
int removeEnWord()
{
	MYSQL *conn;
	char *server = "localhost";                                                
	char *user = "root";
	char *password = "klaand"; /* set me first */
	char *database = "enno_dic";
	int success;
	conn = mysql_init(NULL);
	
	if (conn == NULL) {
		fprintf(stderr, "Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		fprintf(stderr, "Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	char read[95];
	printf("Skriv inn ordet du vil fjerne (maks 90 tegn): ");
	fgets(read, 95, stdin);
	if(read[strlen(read) -1] == '\n')
	{
		read[strlen(read) -1] = '\0';
	}
	//setter sammen 2 strenger som skal utgjøre remove-kommandoen
	//printf("OK\n");
	char s1[150] = "DELETE FROM tbl_words WHERE en_word= \"";
	char s2 = strcat(s1,strcat(read,"\";")); //legger til verdien til wordId og et semikolon i strengen s1
	// kommandoen blir da seendes slik ut "DELETE FROM tbl_word WHERE id = wordId;"
	//printf("%s",&s1);
	if(mysql_query(conn,&s1))
	{
		fprintf(stderr, "Feil: %s\n", mysql_error(conn));
		success = mysql_errno(conn);
		return mysql_errno(conn);
	}
	else 
	{
		printf("Ordet ble fjernet\n");
	}

	return success;
}
int removeNoWord()
{
	MYSQL *conn;
	char *server = "localhost";                                                
	char *user = "root";
	char *password = "klaand"; /* set me first */
	char *database = "noen_dic";
	int success;
	conn = mysql_init(NULL);
	
	if (conn == NULL) {
		fprintf(stderr, "Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		fprintf(stderr, "Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	char read[95];
	printf("Skriv inn ordet du vil fjerne (maks 90 tegn): ");
	fgets(read, 95, stdin);
	if(read[strlen(read) -1] == '\n')
	{
		read[strlen(read) -1] = '\0';
	}
	//setter sammen 2 strenger som skal utgjøre remove-kommandoen
	//printf("OK\n");
	char s1[150] = "DELETE FROM tbl_words WHERE en_word= \"";
	char s2 = strcat(s1,strcat(read,"\";")); //legger til verdien til wordId og et semikolon i strengen s1
	// kommandoen blir da seendes slik ut "DELETE FROM tbl_word WHERE id = wordId;"
	//printf("%s",&s1);
	if(mysql_query(conn,&s1))
	{
		fprintf(stderr, "Feil: %s\n", mysql_error(conn));
		success = mysql_errno(conn);
		return mysql_errno(conn);
	}
	else 
	{
		printf("Ordet ble fjernet\n");
	}
	
	return success;
}
