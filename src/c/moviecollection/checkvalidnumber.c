#include<stdio.h>
#include<stdlib.h>   /* header file for function 'strtol()' */
 
int main()
{
  char input[BUFSIZ], *p;
  long result;
 
  printf("Please enter a positive integer : ");
 
  for(;;){        /* infinite "for" loop */
 
    fgets(input , sizeof(input), stdin);
 
    result = strtol(input , &p, 10);
 
    if(input[0] != '\n' && result > 0 && (*p == '\n' || *p == '\0'))
      break;
    else
      printf("Invalid input !\n\nPlease enter a positive integer : ");
    result = 0;
 
  }
 
  printf("You've entered the number %ld", result);
 
  return 0;
}
