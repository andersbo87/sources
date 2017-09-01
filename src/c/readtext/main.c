#include <stdio.h>

int main (int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
	printf("Skriv inn en tekst: ");
	char ans;
	scanf("%s", &ans);
	printf("Du skrev \"%s\".\n", &ans);
    return 0;
}
