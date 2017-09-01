#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//et lite program som skal kunne regne ut regnestykker med
//operatorene +, -, *, / og % (modulus).
//som standard gir ikke systemet noen feilmeldinger dersom en tallvariabel får en bokstav som verdi.
//int i;
//scanf("%d", i);
//skriver brukeren inn "a", blir verdien til i = 0.
float add(float,float);//addisjon
float sub(float,float);//subtraksjon
float product(float,float);//multiplikasjon
float divide(float,float);//divisjon
long mod(long, long);//modulus
void fakultet(int);
void displayHelp();
float sinus(double s);
float cosinus(float c);
float tangens(float t);
double radians(double d);//radianere
double degrees(double r);//grader
float ans; //variabel som skal lagre svaret… 

double radians (double d) 
{
	return d * M_PI / 180;
}
double degrees (double r) //konverterer fra radianere til grader
{
	return r * 180/ M_PI; //180 delt på pi
}

int main(int argc, const char * argv[], int runs)
{
	if(argc >= 3)
	{
		printf("%s: usage\n%s -f for factorial function\n%s --help to display a simple information.\n",argv[0], argv[0], argv[0]);
		return 1;
	}
	if(argc == 2)
	{
		if(strcmp("--help", argv[1]) == 0)
		{
			displayHelp();
			return 0;
		}
		if(strcmp("-f", argv[1]) == 0)
		{
			int n1;
			if(runs == 1)
				printf("Du er nå inne i den delen av mat som brukes til å regne ut fakuluteten av n. For å gå tilbake til den basiske delen, trykk ctrl+c på tastaturet og skriv mat uten -f\n");
			printf("mat: ");
			scanf("%d",&n1);
			fakultet(n1);
			//runs++;
			//main(2,"-f",runs);
		}
		if(strcmp("-v", argv[1]) == 0)
		{
			int n1;
			char sym;
			scanf("%s %d",&sym,&n1);
			if(sym == 's') //sinus
			{
				printf("Sinus\n");
				//printf("%d", n1);
				printf("%g\n", sinus(n1));
				return 0;
			}
			else if(sym == 'c') //cosinus
			{
				printf("%g", cosinus(n1));
				return 0;
			}
			else if(sym == 't') //tangens
			{
				printf("%g\n", tangens(n1));
			}
			printf("");
			return 0;
		}
	}
    while(1)
	{
		//const int invalid_value = -1000000000;
		float n1,n2;
		char sym,choice;
		if(runs == 1)
			printf("Dette er en enkel kalkulator.\nSkriv a+b for å regne ut a+b\na-b for å regne ut a-b\na*b for å regne ut a*b\na/b for å regne ut a/b\nder a og b 2 er 2 tall\neller a %c b for a mod b\nder a og b er 2 heltall\n",'%');
		printf("mat: ");
		scanf("%f%c%f",&n1,&sym,&n2);
		
		if(sym=='+')
		{
			printf("\n%f\n",add(n1,n2));
			runs++;
			//printf("mat: ");
			main(1,"",runs);
		}
		else if(sym=='-')
		{
			printf("\n%f\n",sub(n1,n2));
			runs++;
			//printf("mat: ");
			main(0,"",runs);
		}
		else if(sym=='*')
		{
			printf("\n%f\n",product(n1,n2));
			runs++;
			//printf("mat: ");
			main(0,"",runs);
		}
		else if(sym=='/')
		{   
			printf("%f\n",divide(n1,n2));
			runs++;
			//printf("mat: ");
			main(0,"",runs);
		}
		else if(sym == '%')
		{
			printf("%ld\n",mod(n1,n2));
			runs++;
			//printf("mat: ");
			main(0,"",runs);
		}
		/*else if(sym == '!' && n2 == invalid_value)
		{
			printf("%d fakultet er %d\n", n1, fakultet(n1));
			runs++;
			main(0,"",runs);
		}*/
		else if(sym == ' ')
		{
			runs++;
			//printf("mat: ");
			main(0,"",runs);
		}
		else 
		{
			printf("En feil har oppstått: \"%c\" er en uygldig operator.\n", sym);
			break;
		}
		printf("n1 er %f", n1);
		scanf("%s",&choice);
	}
	return 0;
}

long mod(long m1, long m2)
{
  ans = m1%m2;
  return (m1%m2);
}

float add(float m1,float m2)
{
  ans = m1+m2;
    return(m1+m2);
}

float sub(float m1,float m2)
{
  ans = m1-m2;
    return(m1-m2);
}

float product(float m1,float m2)
{
  ans = m1*m2;
    return(m1*m2);
}
float sinus(double s)
{
  ans = sin(radians(s));
  return sin(radians(s));
}
float cosinus(float c)
{
  ans = cos(radians(c));
  return cos(radians(c));
}
float tangens(float t)
{
  ans = tan(radians(t));
  return tan(radians(t));
}
float f(float x)
{
  ans = cosinus(x);
  return cosinus(x);
}
float secant(float xn_1, float xn, float e, int m)
{
	int n;
	float d;
	for(n = 1; n <= m; n++)
	{
		d = (xn - xn_1) /(f(xn) - f(xn_1) * f(xn));
	}
	ans = xn;
	return xn;
}
float divide(float m1,float m2)
{
  ans = m1/m2;
  return(m1/m2);
}
void fakultet(int value)
{
	int i, j;
	j=1;
	for(i=1;i<=value; i++)
	{
		j=j*i;
	}
	printf("%d! = %d\n",value, j);
	exit(0);
}

void displayHelp()
{
	printf("Simple information\n");
	printf("mat er et enkelt regneprogram som kan regne ut enkle addisjoner, subtraksjoner, multiplikasjoner, divisjoner og finne rester etter en heltallsdivisjon.\nLegger du til opsjonen -f, kan du også regne ut sinus, cosinus, tangens og n-fakultet (n!).\n");
}

