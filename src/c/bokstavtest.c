#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main(int argc, char** argv)
{
  wint_t letter = L'\0';
  setlocale(LC_ALL, "no_NO.UTF8"); /* Initialize locale, to get the correct conversion to/from wchars */
  while(1)
    {
      if(!letter)
	printf("Type a letter to get its position: ");

      letter = fgetwc(stdin);
      if(letter == WEOF) {
        putchar('\n');
        return 0;
      } else if(letter == L'\n' || letter == L'\r') { 
        letter = L'\0'; /* skip newlines - and print the instruction again*/
      } else {
        printf("%d\n", letter); /* print the character value, and don't print the instruction again */
      }
    }
  return 0;
}
