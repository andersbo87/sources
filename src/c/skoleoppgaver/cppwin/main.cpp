#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char * const argv[]) 
{
    // insert code here...
	printf("Skriv inn et antall sekunder: ");
	int secs;
	int seconds;
	int hours;
	int mins;
	scanf("%d", &secs);
	hours = secs /3600;
	secs -= hours * 3600;
	mins = secs / 60;
	seconds = secs - mins * 60;
	if (hours == 1) 
	{
		if(mins == 1)
		{
			if(seconds == 1)
			{
				printf("%d time %d minutt %d sekund\n",hours, mins, seconds);
			}
			else {
				printf("%d tim %d minutt %d sekunder\n",hours, mins, seconds);
			}
		}
		else 
		{
			if(seconds == 1)
			{
				printf("%d time %d minutter %d sekund\n",hours, mins, seconds);
			}
			else 
			{
				printf("%d time %d minutter %d sekunder\n",hours, mins, seconds);
			}
		}
	}
	else 
	{
		if(mins == 1)
		{
			if(seconds == 1)
			{
				printf("%d timer %d minutt %d sekund\n",hours, mins, seconds);
			}
			else 
			{
				printf("%d timer %d minutt %d sekunder\n",hours, mins, seconds);
			}
		}
		else 
		{
			if(seconds == 1)
			{
				printf("%d timer %d minutter %d sekund\n",hours, mins, seconds);
			}
			else 
			{
				printf("%d timer %d minutter %d sekunder\n",hours, mins, seconds);
			}
		}
	}
	return 0;
}
