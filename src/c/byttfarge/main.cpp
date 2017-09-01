#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h> //for å kunne endre bakgrunnen
#include <curses.h>

int main (int argc, char * const argv[]) {
    //
	int i;
	initscr();
	start_color();
	assume_default_colors(COLOR_RED,COLOR_BLUE);
	printw("Standard skrift på blå bakgrunn");
	refresh();
	start_color();
	int y;
	int x;
	for(y =9; y < 16; y++)
	{
		for(x = 0; x < 65; x++)
		{
			init_pair(1, COLOR_WHITE, COLOR_GREEN);
			attron(COLOR_PAIR(1));
			printw(" hei ");
			attroff(COLOR_PAIR(1));
			refresh();
		}
	}
	sleep(60);
	endwin();
	
    return 0;
}
