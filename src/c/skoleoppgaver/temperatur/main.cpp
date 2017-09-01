#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h> //for å kunne endre bakgrunnen
#include <curses.h>
/*Et program som skal lese inn 7 temperaturer som brukeren angir.
 Programmet skal først skrive ut den største og minste temperaturen
 og deretter gjennomsnittstemperaturen.*/
int main (int argc, char * const argv[]) {
    // insert code here...
	
	int i;
	int teller;
	int temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0, temp5 = 0, temp6 = 0, temp7 = 0, highest = 0, lowest = 0,avg = 0;
	
	initscr();
	start_color();
	assume_default_colors(COLOR_RED, COLOR_BLUE);
	
	for (i=0; i < 7; i++)
	{
		printf("%d\n\r",i);
		printw("Skriv inn en temperatur: ");
		if(i == 0)
		{
			scanw("%d",&temp1);
			lowest = temp1;
			highest = temp1;
		}
		if(i == 1)
		{
			scanw("%d", &temp2);
			if(temp2 < lowest)
				lowest = temp2;
			if(temp2 > highest)
				highest = temp2;
		}
		if(i == 2)
		{
			scanw("%d", &temp3);
			if(temp3 < lowest)
				lowest = temp3;
			if(temp3 > highest)
				highest = temp3;
		}
		if(i == 3)
		{
			scanw("%d", &temp4);
			if(temp4 < lowest)
				lowest = temp4;
			if(temp4 > highest)
				highest = temp4;
		}
		if(i == 4)
		{
			scanw("%d", &temp5);
			if(temp5 < lowest)
				lowest = temp5;
			if(temp5 > highest)
				highest = temp5;
		}
		if(i == 5)
		{
			scanw("%d", &temp6);
			if(temp6 < lowest)
				lowest = temp6;
			if(temp6 > highest)
				highest = temp6;
		}
		if(i == 6)
		{
			scanw("%d", &temp7);
			if(temp7 < lowest)
				lowest = temp7;
			if(temp7 > highest)
				highest = temp7;
			}
		refresh();
	}
	int lines = 0;
	for(lines = 0; lines <= 20; lines++)
	{
		printw("\n");
	}
	avg = (temp1 + temp2 + temp3 + temp4 + temp5 + temp6 + temp7)/7;
	start_color();
	init_pair(1, COLOR_RED, COLOR_GREEN); /* create foreground / background combination */
	attron(COLOR_PAIR(1)); /* use the above combination */
	printw("Høyest: %d grader. \n",highest);
	printw("Lavest: %d grader. \n",lowest);
	printw("Gjennomsnitt: %d grader. \n",avg);
	attroff(COLOR_PAIR(1)); /* turn color off */
	refresh();
	printw("Sover");
	sleep(10); //lar maskinen sove i 10 sek...
	endwin();
			
    return 0;
}
