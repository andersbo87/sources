#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
/**/

/*
gcc accepts const char argv[], but clang, the compiler used by default in
FreeBSD (and Mac OS X) only accepts const char **argv. Therefore I will
use const char **argv instead of const char argv[].
*/
int main(int argc, const char **argv)
{
  printf("Rask, brun rev.");
  int i;
  for (i=0; i < 9; i++)
    {
      printf("\b");
    }
  fprintf(stdout, "groenn rev.");
  sleep(10);
  fprintf(stdout, "\n");
  return 0;
}

