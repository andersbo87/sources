/*
 *  search.c
 *  lh
 *
 *  Created by Anders Bolt-Evensen on 18.06.10.
 *  Copyright 2010 Høgskolen i Østfold. All rights reserved.
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <mysql.h>
#include <readline/readline.h>
#include "search.h"
#include <string.h>
#include <signal.h>
static char *line_read = (char *)NULL;

#ifdef SIGINFO
void catch_siginfo(int sig_num)
{
    signal(SIGINFO, catch_siginfo);
    fprintf(stdout, "lh: A database app about Little House on the Prairie.\n");
}
#endif

void catch_int5(int sig_num)
{
	signal(SIGQUIT, catch_int5);
	printf("\n***Caught ctrl-D signal***\n");
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
	printf("\n***Caught ctrl-\\ signal***\n");
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
    printf("Quitting...\n");
	//code to save the contents of readline's history...
	exit(0);
}
void searchHelp()
{
	fprintf(stdout, "Here you can browse the Little House movies and TV series database.\nYou can enter\n\ta) an episode number (0-186) or an episode title to display information\n\t   about a given episode, or\n\tb) a season number (s0-s10) to display information about the given\n\t   season.\n");
}
int searchEpisodesByTitle(char *search)
{
	int hits = 0;
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *server = "localhost";
	char *user = "root";
	char *password = "klaand"; /* set me first */
	char *database = "little_house";
	conn = mysql_init(NULL);
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
	if (mysql_query(conn, search))
	{
		fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return mysql_errno(conn);
	}
	
	res = mysql_use_result(conn);
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		hits++;
		fprintf(stdout, "episode id: \t%s\n\nepisode name: \t%s\n\nseason id: %s\n\nnotes: %s\n\n", row[0],row[1], row[3], row[4]);
	}
	mysql_close(conn);
	return hits;
}
int searchEpisode(char *search)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *server = "localhost";
	char *user = "root";
	char *password = "klaand"; /* set me first */
	char *database = "little_house";
	conn = mysql_init(NULL);
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
	if (mysql_query(conn, search))
	{
		fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return mysql_errno(conn);
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
	return 0;
}

int searchSeason(char *search)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *server = "localhost";
	char *user = "root";
	char *password = "klaand"; /* set me first */
	char *database = "little_house";
	conn = mysql_init(NULL);
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
	
	if (mysql_query(conn, search))
	{
		fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return mysql_errno(conn);
	}

	res = mysql_use_result(conn);
	if((row = mysql_fetch_row(res)) != NULL)
	{
		fprintf(stdout, "season id: \t%s\n\nseason: \t%s\n\ndescription: \t%s\n\n", row[0],row[1],row[2]);
	}
	mysql_close(conn);
	return 0;
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
	/*
	en funksjon som skal søke etter episodeinformasjon:
	navnet til episoden
	beskrivelsen som "følger med" episoden
	sesongen episoden er i (f. eks. sesong 1)
	*/
	//printf("lh$ ");
//#ifdef SIGINFO
    printf("SIGINFO\n");
    signal(SIGINFO, catch_siginfo);
//#endif
	signal(SIGINT, catch_int);
	signal(SIGTSTP, catch_int2);
	signal(SIGABRT, catch_int3);
	signal(SIGHUP, catch_int4);
	signal(SIGQUIT, catch_int5);
	if(line_read)
	{
		free(line_read);
		line_read = (char *)NULL;
	}
	line_read = readline("lh$ ");
	if(line_read && *line_read)
	{
		add_history(line_read);
	}
	char *noe = line_read;
	int noeIntS = strspn("s", noe);
	//printf("%d", noeIntS);
	int noeIntE = strspn("e", noe);
	//printf("%d\n", noeIntE);
	if(noeIntS == 1)
	{
		char *new_string;
		while ((new_string =strchr(noe, 's')) != NULL) 
		{
			strcpy(new_string,new_string+1);
			char searchString[150] = "SELECT * FROM tbl_season WHERE seasonID = ";
			char ns = strcat(searchString,strcat(new_string, ";"));
			searchSeason(searchString);
		}
	}

	else if(noeIntE == 1)
	{
		char *new_string;
		while ((new_string =strchr(noe, 'e')) != NULL) 
		{
			strcpy(new_string,new_string+1);
			char searchString[150] = "SELECT episodeID, episodeName, episodeDescription, season, notes FROM qry_episodes WHERE episodeID = ";
			char ns = strcat(searchString,strcat(new_string, ";"));
			searchEpisode(searchString);
		}
	}
	else 
	{
		fprintf(stderr, "Invalid search.\n");
	}

	/*else 
	{
		char searchString[150] = "SELECT episodeID, episodeName, episodeDescription, season, notes FROM qry_episodes WHERE episodeName LIKE \"%";
		char ns = strcat(searchString,strcat(noe, "%\";"));
		int res = searchEpisodesByTitle(searchString);
		if(res == 0)
		{
			fprintf(stdout, "No matches.\n");
		}
		else
		{
			fprintf(stdout, "Found %d hits. To search for the episode description, enter e + episode ID, i.e. e185\n", res);
		}
	}*/
	search();
	return 0;
}
