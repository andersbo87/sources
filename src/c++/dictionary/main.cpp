#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "add_word.h" //legge til et nytt ord i databasen
#include "database_operations.h" //opprette databasen, tabeller, etc
#include "delete_word.h" //fjerne et ord fra databasen
#include "update_word.h" //oppdatere et ord i databasen
#include <mysql.h>

using namespace std;
bool canDelete(int args);
void printHelp(char arg[]);
int main (int argc, char * const argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
	printHelp(argv[0]);
	if(canDelete(argc))
	{
		cout << "ja\n";
	}
	else 
	{
		cout << "nei\n";
	}
	cout << "Skriv inn en tekst: ";
	int msg;
	cin >> msg;
	addWord(msg);
    return 0;
}
/*Sjekke om det er angitt nok opsjoner til å kunne slette ordet*/
bool canDelete(int args)
{
	if(args!=3)
	{
		return false;
	}
	else 
	{
		return true;
	}
}
int deleteRecord(int idx)
{
	return deleteWord(idx);
}
void printHelp(char arg[])
{
	cout << "usage: " << arg[0] << " options\n\t-s | --search\tSøke etter ord i databasen\n\t-a | --add\tLegge til ord i databasen\n\t-c | --count\tTelle ord i databasen\n\t-d | --delete <word>\tSlette ord fra databasen\n\t-u | --update\tOppdatere ordet i databasen\n\t-h | --help\tSkriver ut denne hjelpen\n";
}

