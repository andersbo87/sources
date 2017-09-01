#include <stdlib.h>
#include <stdio.h>

int main(void)
{
  int *tabell, *peker;
  int i, antall = 100;
  tabell = calloc(antall, sizeof(int));
  for(i = 0; i < antall; i++)
  {
    tabell[i] = random();
  }
  peker = tabell;
  for(i = 0; i < antall/2; i++)
  {
    printf("%d\n", *peker);
    peker = peker + 2;
  }
  free(tabell);
  return 0;
}
