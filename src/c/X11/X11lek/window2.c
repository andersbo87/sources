/*
 *  window2.c
 *  X11lek
 *
 *  Created by Anders Bolt-Evensen on 5.5.11.
 *  Copyright 2011 Høgskolen i Østfold. All rights reserved.
 *
 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>

#define BORDER_WIDTH 2

/*Globale variabler som kan brukes overalt i programkoden*/
Display *theDisplay;
int theScreen;
int theDepth;


Window OpenWindow(int x, int y, int width, int height, int flag){
	XSetWindowAttributes theWindowAttributes;
	unsigned long theWindowMask;
	XSizeHints theSizeHints;
	Window theNewWindow;
	
	
	/*Setting the attributes*/
	theWindowAttributes.border_pixel
	=BlackPixel(theDisplay,theScreen);
	theWindowAttributes.background_pixel
	= WhitePixel(theDisplay,theScreen);
	theWindowAttributes.override_redirect = True;
	
	
	
	theWindowMask = CWBackPixel|CWBorderPixel|CWOverrideRedirect;
	
	
	theNewWindow = XCreateWindow( theDisplay,
								 RootWindow(theDisplay,theScreen),
								 x,y,width,height,
								 BORDER_WIDTH,theDepth,
								 InputOutput,
								 CopyFromParent,
								 theWindowMask,
								 &theWindowAttributes);
	
	theSizeHints.flags = PPosition | PSize;
	theSizeHints.x = x;
	theSizeHints.y = y;
	theSizeHints.width = width;
	theSizeHints.height = height;
	
	
	XSetNormalHints(theDisplay,theNewWindow,&theSizeHints);
	
	
	XMapWindow(theDisplay,theNewWindow);
	XFlush(theDisplay);
	
	
	return theNewWindow;
}


void main(void){
	Window theWindow;
	
	theDisplay = XOpenDisplay(NULL);
	if(theDisplay == NULL){
		fprintf(stderr,"Error::Given display cannot be opened");
		return;
	}
	theScreen = DefaultScreen(theDisplay);
	theDepth = DefaultDepth(theDisplay,theScreen);
	theWindow = OpenWindow(100,100,200,200,0);
	
	
	sleep(10);
	XCloseDisplay(theDisplay);
}