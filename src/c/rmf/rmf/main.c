#include <stdio.h>
#include <stdlib.h>
#include <removefile.h> //inkludert i Mac OS X 10.5 og nyere.
#include <sys/stat.h>

/*
 rmf har som mål å fungere som rm -i, men istedenfor at progarmmet
 spør brukeren for hver enkelt fil, skal det isteden spørre
 én gang for alle når selve programmet starter opp
 */

int isDir(const char *dname)
{
	struct stat sbuf;
	if(lstat(dname, &sbuf) == -1)
	{
		//fprintf(stderr, "lstat() Failed.\n");                         
		return 1;
	}
	if(S_ISDIR(sbuf.st_mode))
	{
		return 1;
	}
	return 0;
}

int removeFile(char *filename)
{
	//kode som skal kalle på funksjonen removefile().
	//removefile() er en funksjon som er definert i removefile.c og removefile.h som begge ble inkludert i Mac OS X 10.5.
	//denne funksjonen vil inntil videre ikke virke i andre UNIX-baserte opreativsystemer som Linux og BSD.
	int err = 0;
	removefile_state_t r;
	printf("Fjerner filer… Dette kan ta noen minutter");
	err = removefile(filename, r, REMOVEFILE_RECURSIVE | REMOVEFILE_STATE_ERRNO); //fjerner filene. Oppstår det en feil, får errCode den samme verdien som feilkoden.             
	removefile_state_free(r); //frigjør minnet..
	return err;
}

int main (int argc, const char * argv[]) 
{
	//sjekker om brukeren har angitt en fil eller mappe som parameter
	int errCode = 0;
	FILE *istream;
	char answer;
	if ( (istream = fopen (argv[1], "-r" ) ) == NULL )
	{
		if(!isDir(argv[1])) //hvis det brukeren sendte med, ikke er en mappe
		{
			printf ("Vil du virkelig slette filen \"%s\"? Du kan ikke angre på dette (j,n)!\n", argv[1] );
			//printf("%s", answer);
			scanf("%c", &answer);
			if(answer == 'j')
			{
				printf("Forbereder fjering av filer\n");
				errCode = removeFile(argv[1]);
			}
			else if(answer == 'n')
			{
				printf("Operasjonen ble avbrutt av brukeren");
				errCode = 0;
			}
			else
			{
				//printf("%s", answer);
				printf("Svar j for ja eller n for nei\n");
				errCode = 1;
			}
		}
		else
		{
			printf("Vil du virkelig slette mappen \"%s\" og hele dens innhold? Du kan ikke angre på dette(j,n)!\n", argv[1]);
			scanf("%c", &answer);
			//printf("%s", answer);
			if(answer == 'j')
			{
				errCode = removeFile(argv[1]);
				printf("Forbereder fjering av filer\n");
			}
			else if(answer == 'n')
			{
				printf("Operasjonen ble avbrutt av brukeren");
				errCode = 0;
			}
			else
			{
				printf("Svar j for ja eller n for nei\n");
				errCode = 1;
			}
		}
	}
	if(errCode != 0)
	{
		printf("Det har oppstått en feil og programmet avsluttes. Feilkoden er %d\n",errCode);
	}
	return errCode;
}
