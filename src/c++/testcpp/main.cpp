#include <iostream>
using namespace std;
int main (int argc, char * const argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
	int nr = 0;
	char ans = printf("Skriv inn et tall: ");
	scanf("%d", &nr);
	try {
		//nr = (int)ans;
		printf("Du skrev inn %d.", nr);
	}
	catch (char e) {
		printf("Kan ikke konvertere tallet.");
	}
    return 0;
}
