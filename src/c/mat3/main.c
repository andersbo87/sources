#include <stdio.h>
#include <stdlib.h>
int main (int argc, const char * argv[]) {
    // insert code here...
	
    int svar;
	printf("%s", argv[1]);
	svar = atoi(argv[1]);
	printf("Svar: %d", svar);
    return 0;
}
