#include <iostream>
#include <stdlib.h>
#include <stdio.h>

float add(float, float);
float sub(float, float);
float product(float, float);
float divide(float, float);
long mod(long, long);

using namespace std;

int main (int runs) 
{
    while(true)
	{
		float n1, n2;
		char sym;
		if(runs == 1)
			printf("Dette er en enkel kalkulator.\nSkriv a+b for å regne ut a+b\na-b for å regne ut a-b\na*b for å regne ut a*b\na/b for å regne ut a/b\nder a og b 2 er 2 tall\neller a %c b for a mod b\nder a og b er 2 heltall\n",'%');
		printf("mat: ");
		scanf("%f%c%f",&n1,&sym,&n2);
		cin >> n1;
		//sjekke om n1 virkelig er et tall:
		if (!cin || cin.gcount() != 1)
			printf("Skriv inn et gyldig tall");
		//sjekke om n2 virkelig er et tall:
		cin >> n2;
		if (!cin || cin.gcount() != 1)
			printf("Skriv inn et gyldig tall");
		if(sym=='+')
		{
			printf("\n%f\n",add(n1,n2));
			runs++;
			//printf("mat: ");
			main(runs);
		}
		if(sym=='-')
		{
			printf("\n%f\n",add(n1,n2));
			runs++;
			//printf("mat: ");
			main(runs);
		}
		if(sym=='*')
		{
			printf("\n%f\n",add(n1,n2));
			runs++;
			//printf("mat: ");
			main(runs);
		}
		if(sym=='/')
		{
			printf("\n%f\n",add(n1,n2));
			runs++;
			//printf("mat: ");
			main(runs);
		}
		if(sym=='%')
		{
			printf("\n%f\n",add(n1,n2));
			runs++;
			//printf("mat: ");
			main(runs);
		}
		else {
			printf("En feil har oppstått: %c er en uygldig operator.\n", sym);
			break;
		}
		/*char choise;
		scanf("%s",&choice);*/
	}
	return 0;
}
long mod(long m1, long m2)
{
	return (m1%m2);
}

float add(float m1,float m2)
{
    return(m1+m2);
}

float sub(float m1,float m2)
{
    return(m1-m2);
}

float product(float m1,float m2)
{
    return(m1*m2);
}

float divide(float m1,float m2)
{
    return(m1/m2);
}

