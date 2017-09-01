/*
 *  xwindow.h
 *  X11lek
 *
 *  Created by Anders Bolt-Evensen on 5.5.11.
 *  Copyright 2011 Høgskolen i Østfold. All rights reserved.
 *
 */

#include <X11/X.h>
#include <X11/Xlib.h>
#include <stdlib.h>

int main(void)
{
	Display *display;
	Window window, rootwindow;
	int screen;
	
	display = XOpenDisplay(NULL);
	screen = DefaultScreen(display);
	rootwindow = RootWindow(display, screen);
	window = XCreateSimpleWindow(display, rootwindow, 0, 0, 1024, 768, 1, 0, 0);
	XMapWindow(display, window);
	XFlush(display);
	
	//får programmet til å sove i 10 sekunder:
	sleep(10);
	XCloseDisplay(display);
	return 0;
}