/*
 *  update_word.c
 *  connect_mysql
 *
 *  Created by Anders Bolt-Evensen on 4/8/10.
 *  Copyright 2010 Høgskolen i Østfold. All rights reserved.
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mysql.h>

#include "update_word.h"

int updateNorwegianWord()
{
	int success;
	char no_word[95];
	char new_no_word[95];
	MYSQL *conn;
	char *server = "localhost";                                                
	char *user = "root";
	char *password = "klaand"; /* set me first */
	char *database = "noen_word";
	conn = mysql_init(NULL);
	
	if (conn == NULL) {
		fprintf(stderr, "Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		success = mysql_errno(conn);
	}
	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		fprintf(stderr, "Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		success = mysql_errno(conn);
	}
	
	printf("Skriv inn ordet du vil bytte ut: ");
	fgets(no_word, 95, stdin);
	int now_length = strlen(no_word);
	if(no_word[strlen(no_word) -1] == '\n')
	{
		no_word[strlen(no_word) -1] = '\0';
	}
	if(now_length >= 91)
	{
		fprintf(stderr, "Ordet du vil bytte ut, er for langt\n");
	}	
	printf("Skriv inn ordet du vil erstatte \"%s\" med: ",no_word);
	fgets(new_no_word, 95, stdin);
	int new_now_length = strlen(new_no_word);
	if(new_no_word[strlen(new_no_word) -1] == '\n')
	{
		new_no_word[strlen(new_no_word) -1] = '\0';
	}
	if(new_now_length >= 91)
	{
		fprintf(stderr, "Erstatningsordet, er for langt\n");
	}
	//utfører en SELECT-setning som skal finne ut av den engelske betydningen av ordet.
	
	//setter så sammen karakterstrengene som skal utgjøre databasekommandoen:
	char update[200] = "UPDATE tbl_words SET no_word = \"";
	char *c = strcat(update,strcat(new_no_word, "\" WHERE no_word = \""));
	char *c2 = strcat(c,strcat(no_word, "\";"));
	
	//printer foreløpig bare ut SQL-kommandoen som skal kjøres; dette må endres innen programmet er klart.
	printf("%s\n",c2);
	if (mysql_query(conn, c2)) {
		fprintf(stderr, "Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		success = mysql_errno(conn);
	}
	else
	{
		printf("Ordlistetabellen ble oppdatert og %ld ord ble lagt til.\n", (long) mysql_affected_rows(conn));
	}
	
	mysql_close(conn);
	return success;
}

int updateEnglishWord()
{
	int success;
	char en_word[95];
	char new_en_word[95];
	MYSQL *conn;
	char *server = "localhost";                                                
	char *user = "root";
	char *password = "klaand"; /* set me first */
	char *database = "enno_dic";
	conn = mysql_init(NULL);
	if (conn == NULL) {
		fprintf(stderr, "Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		success = mysql_errno(conn);
	}
	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		fprintf(stderr, "Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		success = mysql_errno(conn);
	}
	printf("Skriv inn det engelske ordet du vil bytte ut: ");
	fgets(en_word, 95, stdin);
	int enw_length = strlen(en_word);
	if(en_word[strlen(en_word) -1] == '\n')
	{
		en_word[strlen(en_word) -1] = '\0';
	}
	if(enw_length >= 91)
	{
		fprintf(stderr, "Ordet du vil bytte, er for langt\n");
	}
	printf("Skriv inn det engelske ordet du vil sette inn for \"%s\"", en_word);
	fgets(new_en_word, 95, stdin);
	int new_enw_length = strlen(new_en_word);
	if(new_en_word[strlen(new_en_word) -1] == '\n')
	{
		new_en_word[strlen(new_en_word) -1] = '\0';
	}
	if(new_enw_length >= 91)
	{
		fprintf(stderr, "Erstatningsordet er for langt\n");
	}
	
	char update[200] = "UPDATE tbl_words SET en_word = \"";
	char *c = strcat(update,strcat(new_en_word, "\" WHERE en_word = \""));
	char *c2 = strcat(c, strcat(en_word, "\";"));
	if(mysql_query(conn, c2))
	{
		fprintf(stderr, "Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		success = mysql_errno(conn);
	}
	else 
	{
		printf("Ordlistetabellen ble oppdatert og %ld ord ble lagt til.\n", (long)mysql_affected_rows(conn));
	}
	mysql_close(conn);
	return success;
}