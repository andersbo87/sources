/*
testlibpq3.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <libpq-fe.h>
#include <netinet/in.h>
#include <arpa/inet.h>

static void exit_nicely(PGconn *conn)
{
  PQfinish(conn);
  exit(1);
}

void show_binary_results(PGresult *res)
{
  int i, j;
  int i_fnum, t_fnum, b_fnum;
  i_fnum = PQfnumber(res, "i");
  t_fnum = PQfnumber(res, "t");
  b_fnum = PQfnumber(res, "b");
  for(i = 0; i < PQntuples(res); i++)
  {
    char *iptr, *tptr, *bptr;
    int blen, ival;
    iptr = PQgetvalue(res, i, i_fnum);
    tptr = PQgetvalue(res, i, t_fnum);
    bptr = PQgetvalue(res, i, b_fnum);
    
    ival = ntohl(*((uint32_t *) iptr));
    
    blen = PQgetlength(res, i, b_fnum);
    fprintf(stdout, "tuple %d: got\n", i);
    fprintf(stdout, "i = (%d bytes) %d\n",PQgetlength(res, i, i_fnum), ival);
    fprintf(stdout, "t = (%d bytes) '%s'\n", PQgetlength(res, i , t_fnum), tptr);
    fprintf(stdout, "b = (%d bytes) ", blen);
    for(j = 0; j < blen; j++)
    {
      fprintf(stdout, "\\%03o",bptr[j]);
    }
    fprintf(stdout, "\n\n");
  }
}

int
main(int argc, char **argv)
{
  const char *conninfo;
  PGconn     *conn;
  PGresult   *res;
  const char *paramValues[1];
  int         paramLengths[1];
  int         paramFormats[1];
  uint32_t    binaryIntVal;

  /*
   * If the user supplies a parameter on the command line, use it as the
   * conninfo string; otherwise default to setting dbname=postgres and using
   * environment variables or defaults for all other connection parameters.
   */
  if (argc > 1)
    conninfo = argv[1];
  else
    conninfo = "dbname = postgres";

  /* Make a connection to the database */
  conn = PQconnectdb(conninfo);

  /* Check to see that the backend connection was successfully made */
  if (PQstatus(conn) != CONNECTION_OK)
    {
      fprintf(stderr, "Connection to database failed: %s",
	      PQerrorMessage(conn));
      exit_nicely(conn);
    }

  /*
   * The point of this program is to illustrate use of PQexecParams() with
   * out-of-line parameters, as well as binary transmission of data.
   *
   * This first example transmits the parameters as text, but receives the
   * results in binary format.  By using out-of-line parameters we can
   * avoid a lot of tedious mucking about with quoting and escaping, even
   * though the data is text.  Notice how we don't have to do anything
   * special with the quote mark in the parameter value.
   */

  /* Here is our out-of-line parameter value */
  paramValues[0] = "joe's place";
  char selectStatement[100] = "SELECT * from ";
  char ans[7];
  //fgets(ans, 5, stdin);
  fprintf(stdout, "Enter the database you wish to search in: ");
  fgets(ans, 6, stdin);
  if(ans[strlen(ans) -1] == '\n')
  {
    ans[strlen(ans) -1] = '\0';
  }
  strcat(selectStatement, ans);
  strcat(selectStatement, " WHERE t = $1");
  res = PQexecParams(conn,
		     selectStatement,
		     //"SELECT * FROM test1 WHERE t = $1",
		     1,       /* one param */
		     NULL,    /* let the backend deduce param type */
		     paramValues,
		     NULL,    /* don't need param lengths since text */
		     NULL,    /* default to all text params */
		     1);      /* ask for binary results */

  if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
      fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
      PQclear(res);
      exit_nicely(conn);
    }

  show_binary_results(res);

  PQclear(res);

  /*
   * In this second example we transmit an integer parameter in binary
   * form, and again retrieve the results in binary form.
   *
   * Although we tell PQexecParams we are letting the backend deduce
   * parameter type, we really force the decision by casting the parameter
   * symbol in the query text.  This is a good safety measure when sending
   * binary parameters.
   */

  /* Convert integer value "2" to network byte order */
  binaryIntVal = htonl((uint32_t) 2);

  /* Set up parameter arrays for PQexecParams */
  paramValues[0] = (char *) &binaryIntVal;
  paramLengths[0] = sizeof(binaryIntVal);
  paramFormats[0] = 1;        /* binary */

  res = PQexecParams(conn,
		     "SELECT * FROM test1 WHERE i = $1::int4",
		     1,       /* one param */
		     NULL,    /* let the backend deduce param type */
		     paramValues,
		     paramLengths,
		     paramFormats,
		     1);      /* ask for binary results */

  if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
      fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
      PQclear(res);
      exit_nicely(conn);
    }
  int counter;
  for(counter = 0; counter < 7; counter++)
  {
    ans[counter] = '\0';
  }
  fprintf(stdout, "heisann %s\n", ans);
  show_binary_results(res);
fprintf(stdout, "heisann %s\n", ans);
  PQclear(res);

  /* close the connection to the database and cleanup */
  PQfinish(conn);

  return 0;
}
