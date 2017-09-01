#include <stdio.h>
#include <stdlib.h>
#include <removefile.h> //inkludert i Mac OS X 10.5 og nyere.
#include <sys/stat.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>

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
static struct timeval tv;
static void start_timer(const char* str) {
	fprintf(stderr, "%s... ", str);
	assert(gettimeofday(&tv, NULL) == 0);
}

static void stop_timer() {
	struct timeval tv2;
	assert(gettimeofday(&tv2, NULL) == 0);
	long sec = tv2.tv_sec - tv.tv_sec;
	long usec;
	if (sec == 0) {
		usec = tv2.tv_usec - tv.tv_usec;
	} else {
		usec = tv2.tv_usec + (1000000 - tv.tv_usec);
	}
	fprintf(stderr, "%ld.%03ld\n", sec, usec);
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
				//errCode = removeFile(argv[1]);
				removefile_state_t r;
				printf("Fjerner filer… Dette kan ta noen minutter\n");
				start_timer("removefile(argv[1])");
				errCode = removefile(argv[1], r, REMOVEFILE_RECURSIVE | REMOVEFILE_STATE_ERRNO); //fjerner filene. Oppstår det en feil, får errCode den samme verdien som feilkoden.             
				stop_timer();
				removefile_state_free(r); //frigjør minnet..
			}
			else if(answer == 'n')
			{
				printf("Operasjonen ble avbrutt av brukeren\n");
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
				printf("Forbereder fjerning av filer…\n");
				//errCode = removeFile(argv[1]);
				removefile_state_t r;
				printf("Fjerner filer… Dette kan ta noen minutter avhengig av hvor mange filer som skal fjernes.\n");
				start_timer("removefile(argv[1])");
				errCode = removefile(argv[1], r, REMOVEFILE_RECURSIVE | REMOVEFILE_STATE_ERRNO); //fjerner filene. Oppstår det en feil, får errCode den samme verdien som feilkoden.             
				removefile_state_free(r); //frigjør minnet..
				stop_timer();
			}
			else if(answer == 'n')
			{
				printf("Operasjonen ble avbrutt av brukeren\n");
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
