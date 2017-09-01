//createdb.c
#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

int createDatabase()
{
  int err = 0;
  MYSQL ccnn;
  char *server = "localhost";
  char *user = "root";
  char password = "passwd";
  //char database = "mymovies";
  conn = mysql_init(NULL);
  
  if(conn == NULL)
  {
    fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
    return mysql_errno(conn);
  }

  if(!mysql_real_connect(conn, server, user, password, NULL, 0, NULL, 0))
  {
    fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
    return mysql_errno(conn);
  }

  if(mysql_query(conn, "CREATE DATABASE IF NOT EXISTS mymovies DEFAULT CHARACHTER SET utf-8 COLLATE UTF8_UNICODE_CI;"))
  {
    fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
    return mysql_errno(conn);
  }
  mysql_close(conn);
  return 0;
}
