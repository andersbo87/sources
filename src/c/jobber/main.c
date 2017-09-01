#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
PGresult* innsettPostNummer(PGconn* conn, int id, int data_size, const char* const data);
static void exit_nicely(PGconn *conn)
{
  PQfinish(conn);
  exit(1);
}

int main(int argc, char **argv)
{
  const char *conninfo;
  PGconn     *conn;
  PGresult   *res;
  int        nFields;
  int        i, j;
  conninfo = "dbname = jobber";
  conn = PQconnectdb(conninfo);
  if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "Connection to database failed: %s",
                PQerrorMessage(conn));
        exit_nicely(conn);
    }
  innsettPostNummer(conn, 1700, 9, "Grålum");
  return 0;
}

PGresult* innsettPostNummer(PGconn* conn, int id, int data_size, const char* const data)
{
  PGresult* result;
  const int id_big_endian = htonl((int)id);
  const char* const paramValues[] = { &id_big_endian, data };
  const int nParams = sizeof(paramValues) / sizeof(paramValues[0]);
  const int paramLenghts[] = { sizeof(id_big_endian), data_size };
  const int paramFormats[] = { 1, 256 }; /* binary */
  const int resultFormat = 0; /* text */

  result = PQexecParams(
    conn,
    "insert into tbl_postnr_sted(postnr, poststed) values ($1::integer, $2::varchar)",
    nParams,
    NULL, /* Types of parameters, unused as casts will define types */
    paramValues,
    paramLenghts,
    paramFormats,
    resultFormat
  );
  return result;
}
