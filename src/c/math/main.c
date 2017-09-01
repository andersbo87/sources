#include <stdio.h>

int main (int argc, const char * argv[]) {
    // insert code here...
	printf("Skriv et regnestykke: ");
	char stykke;
	int svar;
	scanf("%s",&stykke);
	svar = (int)stykke; 
	printf("%d\n", stykke);
}
