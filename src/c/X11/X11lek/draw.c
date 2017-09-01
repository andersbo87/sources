/*
 *  draw.c
 *  X11lek
 *
 *  Created by Anders Bolt-Evensen on 5.5.11.
 *  Copyright 2011 Høgskolen i Østfold. All rights reserved.
 *
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>
#define BORDER_WIDTH 2
//variabler som kan brukes overalt i programkoden
Display *theDisplay;
int theScreen;
int theDepth;
unsigned long theBlackPixel;
unsigned long theWhitePixel;


/*void initX(void){
}


void drawLine(Window theWindow,GC theGC,int x1,int y1,int x2,int y2){
	XDrawLine(theDisplay,theWindow,theGC,x1,y1,x2,y2);
	
	
}


void drawRectangle(Window theWindow,GC theGC,int x,int y,int width,int height){
	XDrawRectangle(theDisplay,theWindow,theGC,x,y,width,height);
}


int createGC(Window theNewWindow,GC *theNewGC){
	XGCValues theGCValues;
	
	
	*theNewGC = XCreateGC(theDisplay,theNewWindow,(unsigned long) 0,&theGCValues);
	if(*theNewGC == 0)
		return 0;
	else{
		XSetForeground(theDisplay,*theNewGC,theWhitePixel);
		XSetBackground(theDisplay,*theNewGC,theBlackPixel);
		return 1;
	}
}


Window OpenWindow(int x, int y, int width, int height, int flag,GC *theNewGC){
	XSetWindowAttributes theWindowAttributes;
	unsigned long theWindowMask;
	XSizeHints theSizeHints;
	XWMHints theWMHints;
	Window theNewWindow;
	
	
	//Setting the attributes
	theWindowAttributes.border_pixel
	=BlackPixel(theDisplay,theScreen);
	theWindowAttributes.background_pixel
	= WhitePixel(theDisplay,theScreen);
	theWindowAttributes.override_redirect = False;
	
	
	
	theWindowMask = CWBackPixel|CWBorderPixel|CWOverrideRedirect;
	
	
	theNewWindow = XCreateWindow( theDisplay,
								 RootWindow(theDisplay,theScreen),
								 x,y,width,height,
								 BORDER_WIDTH,theDepth,
								 InputOutput,
								 CopyFromParent,
								 theWindowMask,
								 &theWindowAttributes);
	
	
	theWMHints.initial_state = NormalState;
	theWMHints.flags = StateHint;
	
	
	XSetWMHints(theDisplay,theNewWindow,&theWMHints);
	
	theSizeHints.flags = PPosition | PSize;
	theSizeHints.x = x;
	theSizeHints.y = y;
	theSizeHints.width = width;
	theSizeHints.height = height;
	
	
	XSetNormalHints(theDisplay,theNewWindow,&theSizeHints);
	
	
	if( createGC(theNewWindow,theNewGC) == 0){
		XDestroyWindow(theDisplay,theNewWindow);
		return( (Window) 0);
	}
	
	
	XMapWindow(theDisplay,theNewWindow);
	XFlush(theDisplay);
	
	
	return theNewWindow;
}


int main(void){
	Window theWindow;
	GC theGC;
	
	theDisplay = XOpenDisplay(NULL);
	
	theScreen = DefaultScreen(theDisplay);
	theDepth = DefaultDepth(theDisplay,theScreen);
	theBlackPixel = WhitePixel(theDisplay,theScreen);
	theWhitePixel = BlackPixel(theDisplay,theScreen);
	
	theWindow = OpenWindow(100,100,300,300,0,&theGC);
	drawLine(theWindow,theGC,1,1,10,10);
	drawRectangle(theWindow,theGC,10,10,10,10);
	XFlush(theDisplay);
	
	sleep(10);
	XDestroyWindow(theDisplay,theWindow);
	return 0;
}*/
//definerer en "tom" funksjon initX:
void initX(void)
{}

void drawLine(Window theWindow, GC theGC, int x1, int y1, int x2, int y2)
{
	XDrawLine(theDisplay, theWindow, theGC, x1, y1, x2, y2);
}

void drawRectangle(Window theWindow, GC theGC, int x, int y, int width, int height)
{
	XDrawRectangle(theDisplay, theWindow, theGC, x, y, width, height);
}

int createGC(Window theNewWindow, GC *theNewGC)
{
	XGCValues theGCValues;
	
	*theNewGC = XCreateGC(theDisplay, theNewWindow, (unsigned long) 0, &theGCValues);
	if(*theNewGC == 0)
	{
		return 0;
	}
	else 
	{
		XSetForeground(theDisplay, *theNewGC, theWhitePixel);
		XSetBackground(theDisplay, *theNewGC, theBlackPixel);
		return 1;
	}

}

Window OpenWindow(int x, int y, int width, int height, int flag, GC *theNewGC)
{
	XSetWindowAttributes theWindowAttributes;
	unsigned long theWindowMask;
	XSizeHints theSizeHints;
	XWMHints theWMHints;
	Window theNewWindow;
	
	theWindowAttributes.border_pixel = BlackPixel(theDisplay, theScreen);
	theWindowAttributes.border_pixel = WhitePixel(theDisplay, theScreen);
	theWindowAttributes.override_redirect = False;
	
	theWindowMask = CWBackPixel|CWBorderPixel|CWOverrideRedirect;
	
	theNewWindow = XCreateWindow(theDisplay,
								 RootWindow(theDisplay, theScreen),
								 x,y,width,height,
								 BORDER_WIDTH, theDepth,
								 InputOutput,
								 CopyFromParent,
								 theWindowMask,
								 &theWindowAttributes);
	theWMHints.initial_state = NormalState;
	theWMHints.flags = StateHint;
	
	XSetWMHints(theDisplay, theNewWindow, &theWMHints);
	
	theSizeHints.flags = PPosition | PSize;
	theSizeHints.x = x;
	theSizeHints.y = y;
	theSizeHints.width = width;
	theSizeHints.height = height;
	
	XSetNormalHints(theDisplay, theNewWindow, &theSizeHints);
	
	if(createGC(theNewWindow, theNewGC) == 0)
	{
		XDestroyWindow(theDisplay, theNewWindow);
		return((Window)0);
	}
	XMapWindow(theDisplay, theNewWindow);
	XFlush(theDisplay);
	
	return theNewWindow;
}

int main(void)
{
	Window theWindow;
	GC theGC;
	
	theDisplay = XOpenDisplay(NULL);
	theScreen = DefaultScreen(theDisplay);
	theDepth = DefaultDepth(theDisplay, theScreen);
	theBlackPixel = WhitePixel(theDisplay, theScreen);
	theWhitePixel = BlackPixel(theDisplay, theScreen);
	
	theWindow = OpenWindow(100, 100, 300, 300, 0, &theGC);
	drawLine(theWindow, theGC, 10, 10, 100, 100);
	drawRectangle(theWindow, theGC, 100, 100, 100, 100);
	XFlush(theDisplay);
	
	sleep(10);
	XDestroyWindow(theDisplay, theWindow);
	return 0;
}






















