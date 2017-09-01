//main.c
//including standard header files:
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
//requires mysql to be installed (otherwise the compilation process will fail):
#include <mysql.h>

//including other special header files:
#include "add.h"
#include "createdb.h"
#include "remove.h"
#include "search.h"
#include "update.h"

int main(int argc, const char * argv[])
{
  int err = 0;
  //check if the mymovies database exists
  struct stat st;
  if(!stat("/usr/var/mymovies", &st) == 0)
  {
    //create the database
  }
  if(argc == 0)
  {
    err = printHelp();
  }
  return err;
}

int printHelp()
{
  fprintf(stderr, "moviecollection: usage: <text here>\n");
  return -1;
}
