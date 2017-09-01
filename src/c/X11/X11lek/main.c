#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>

int main()
{
	Display *display_name;
	int depth, screen, connection;
	
	//åpner displayet og setter standardverdier
	display_name = XOpenDisplay(NULL);
	screen = DefaultScreen(display_name);
	depth = DefaultDepth(display_name, screen);
	connection = ConnectionNumber(display_name);
	
	//skriver ut innsamlet informasjon
	fprintf(stdout, "Displayet er: %s\n", XDisplayName((char*)display_name));
	fprintf(stdout, 
			"Bredde: %d\tHøyde: %d\n",DisplayWidth(display_name,screen),DisplayHeight(display_name,screen));
	fprintf(stdout, "Forbindelsesnummeret er: %d\n", connection);
	
	if(depth == 1)
	{
		fprintf(stdout, "Du lever i en prehistorisk tid.\n");
	}
	else 
	{
		fprintf(stdout, "Du har en fargemonitor med dybde %d\n", depth);
	}
	
	//lukker displayet
	XCloseDisplay(display_name);

	return 0;
}

