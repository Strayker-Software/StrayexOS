/*
 Strayex Kernel
 v1.0.0
 Screen VGA driver and printing functions
 Copyright 2019 Daniel Strayker Nowak
 All rights reserved
*/

// Header files:
#include "klib/kio.h"
#include "klib/kstring.h"
#include "klib/kstdlib.h"
#include <stdarg.h>

// Variables for basic screen's operations:
unsigned short *videomem = (unsigned short *)0xB8000; // Memory address,
int attrib = 0x0F; // Color attribute,
int px = 0, py = 0; // X and Y coordinates for cursor,

// Moves cursor to position pointed by args:
void kmove_cursor(int x, int y)
{
    unsigned temp;
    temp = y * 80 + x; // Calculate where move cursor to,
	px = x; py = y; // Updates cursor's coordinates,

	// Performing move by writting to I/O ports:
    koutportb(0x3D4, 14);
    koutportb(0x3D5, temp >> 8);
    koutportb(0x3D4, 15);
    koutportb(0x3D5, temp);
}

// Gets cursor X coordinate:
int get_cursor_x() { return px; }

// Gets cursor Y coordinate:
int get_cursor_y() { return py; }

// Sets active colors for printing characters:
void ksetattrib(char font, char bg) { attrib = (bg << 4) | (font & 0x0F); }

// Scrolls screen down, like in TTY in Linux:
void kscroll()
{
	// If there is end of screen:
	if(py >= 25)
	{
		unsigned space = 0x20 | (attrib << 8), temp = py - 25 + 1;
		memcpy((unsigned char *)videomem, (const unsigned char *)(videomem + temp * 80), (25 - temp) * 80 * 2); // Move all other lines,
		// Set the last line into spaces:
		memsetw(videomem + (25 - temp) * 80, space, 80);
		py = 24;
	}
}

// Identifies character and prints it on screen:
void kprintch(char x)
{
	// Backspace
	if(x == 0x08)
	{
		if(px > 0)
		{
			px--;
			unsigned att = attrib << 8;
			unsigned short *where = videomem + (py * 80 + px);
			*where = ' ' | att;
		}
		else if(px < 0)
		{
			py--;
		}
		else if(px == 0)
		{
			py--;
		}
	}
	// TAB
	else if(x == 0x09)
	{
		px = (px + 8) & ~(8 - 1);
	}
	// Carriage return
	else if(x == '\r')
	{
		px = 0;
	}
	// New line
	else if(x == '\n')
	{
		px = 0;
		py++;
	}
	// Printable character
	else if(x >= ' ')
	{
		unsigned att = attrib << 8;
		unsigned short *where = videomem + (py * 80 + px);
		*where = x | att;
		px++;
	}

	// If cursor hit end of line:
	if(px >= 80)
	{
		px = 0;
		py++;
	}

	kscroll();
	kmove_cursor(px, py);
}

// Prints integer on screen:
int kprintint(int x, int base)
{
	char help[] = { };
	kitoa(x, help, base);
	int n = kstrlen((unsigned char *)help);
	for(int i = 0; i < n; i++) kprintch(help[i]);
	return 0;
}

// Prints args into x and puts it all on screen:
int vkprintf(const char *x, va_list args)
{
	for(int i = 0; x[i] != '\0'; i++)
	{
		if(x[i] == '%')
		{
			char help[] = { };
			switch(x[i + 1])
			{
				case '%': kprintch('%'); i++; break;
				case 'i': ;
					int help1 = va_arg(args, int);
					if(help1)
					{
						kitoa(help1, help, 10);
						int n = kstrlen((unsigned char *)help);
						for(int j = 0; j < n; j++) kprintch(help[j]);
						i++;
					}
					else
					{
						kprintch('?');
						i++;
					}
				break;
				case 'x': ;
					int help2 = va_arg(args, int);
					if(help2)
					{
						kitoa(help2, help, 16);
						int n = kstrlen((unsigned char *)help);
						for(int j = 0; j < n; j++) kprintch(help[j]);
						i++;
					}
					else
					{
						kprintch('?');
						i++;
					}
				break;
				case 'c': ;
					char *help4 = va_arg(args, char *);
					int l = kstrlen((unsigned char *)help4);
					for(int k = 0; k < l; k++) kprintch(help4[k]);
					i++;
				break;
				default: kprintch('?'); i++; break;
			}
		}
		else
		{
			kprintch(x[i]);
		}
	}
	
	return 0;
}

// Similar to ANSI C printf, but not so powerful:
void kprintf(const char *x, ...)
{
	va_list args;
	va_start(args, x);
	
	vkprintf(x, args);
	
	va_end(args);
}

// Clears screen:
void kcls()
{
	for(int i = 0; i < 25; i++)
	{
		for(int j = 0; j < 80; i++) kprintch(' ');
	}

	px = 0;
	py = 0;

	kmove_cursor(px, py);
}

// Sends data to I/O ports to unhide cursor and move it to pointed position:
void enable_cursor(unsigned char cursor_start, unsigned char cursor_end)
{
	koutportb(0x3D4, 0x0A);
	koutportb(0x3D5, (kinportb(0x3D5) & 0xC0) | cursor_start);
 
	koutportb(0x3D4, 0x0B);
	koutportb(0x3D5, (kinportb(0x3D5) & 0xE0) | cursor_end);
}

// Turns off cursor:
void disable_cursor()
{
	koutportb(0x3D4, 0x0A);
	koutportb(0x3D5, 0x20);
}
