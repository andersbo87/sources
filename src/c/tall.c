#include <stdlib.h>
#include <stdio.h>
int regnut(int x, int y);

int main()
{
  regnut(10, 1);
}

int regnut(int x, int y)
{
  if(x == y)
  {
    printf("Ferdig\n");
  }
  else
  {
    printf("x = %d, y = %d\n", x, y);
    regnut(x -1, y);
  }
}
