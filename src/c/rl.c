#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main(void)
{
  char *navn = NULL;
  navn = readline("Hva heter du? ");
  printf("Hei på deg, %s\n", navn);
  free(navn);
}
