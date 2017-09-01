#include <mysql.h>
#include <iostream>

/*
 *  database_operations.cpp
 *  dictionary
 *
 *  Created by Anders Bolt-Evensen on 4/5/10.
 *  Copyright 2010 Høgskolen i Østfold. All rights reserved.
 *
 */

#include "database_operations.h"
using namespace std;
int createDatabase(char *user, char *password, char *database) //oppretter databasen hvis den ikke finnes fra før.
{
	MYSQL *conn;
	char *server;// = "localhost";
	/*char *user = "root";
	char *password = "klaand"; // set me first
	char *database = "dic_little_house";*/
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
	if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS dic_little_house  DEFAULT CHARACTER SET utf8 COLLATE UTF8_UNICODE_CI;"))
	{
		fprintf(stderr, "Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return mysql_errno(conn);
	}
	else
	{
		printf("Databasen dic_little_house ble opprettet\n");
	}
	
	mysql_close(conn);
	return 0;
}

int createTable(char *user, char *password, char *database) //oppretter tabellen hvis denne ikke finnes fra før
{
	MYSQL *conn;
	char *server;// = "localhost";
	//char user = "root";
	//char password = "klaand"; // set me first 
	//char database = "dic_little_house";
	conn = mysql_init(NULL);
	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) 
	{
		//fprintf(stderr,
		fprintf(stderr, "Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return mysql_errno(conn);
	}
	if (mysql_query(conn, "create table if not exists tbl_words(id int not null auto_increment, en_word varchar(150) unique not null, no_word varchar(150) not null, primary key(id, en_word));"))
	{
		fprintf(stderr, "Feil %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return mysql_errno(conn);
	}
	mysql_close(conn);
	return 0;
}

int searchDatabase(char *server, char *user, char *password, char *database, const std::string& tablename, const std::string& condition, const std::string& s)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int success;
	int times;
	conn = mysql_init(NULL);
	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		int isCreated = createDatabase(user, password, database);
		if(isCreated != 0)
		{
			cout << "Error: " << mysql_errno(conn) << mysql_error(conn);
			success = isCreated;
			return isCreated;
		}
	}
	if(times == 0)
	{
		int isTableCreated = createTable(user, password, database);
		if(isTableCreated != 0)
		{
			cout << "Error: " << mysql_errno(conn), mysql_error(conn);
			success = isTableCreated;
			return isTableCreated;
		}
		else 
		{
			cout << "Connected to database\n";
		}
		times = 1;
	}
	string read = s;
	string search = "SELECT * FROM " + tablename+ " WHERE " + condition = "\"" +s + "\"";
	if(mysql_query(conn, (char*)search)
	{
	}
	return 0;
}
int searchDatabase(char *server, char *user, char *password, char *database, const std::string& tablename, const std::string& s)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int success;
	int times;
	conn = mysql_init(NULL);
	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		int isCreated = createDatabase(user, password, database);
		if(isCreated != 0)
		{
			cout << "Error: " << mysql_errno(conn) << mysql_error(conn);
			success = isCreated;
			return isCreated;
		}
	}
	if(times == 0)
	{
		int isTableCreated = createTable(user, password, database);
		if(isTableCreated != 0)
		{
			cout << "Error: " << mysql_errno(conn), mysql_error(conn);
			success = isTableCreated;
			return isTableCreated;
		}
		else 
		{
			cout << "Connected to database\n";
		}
		times = 1;
	}
	string read = s;
	string search = "SELECT * FROM " + tablename;
	return 0;
}