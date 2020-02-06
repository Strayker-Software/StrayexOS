/*
 Strayex Kernel
 v1.1.0
 Screen VGA driver and printing functions
 Copyright 2019-2020 Daniel Strayker Nowak
 All rights reserved
*/

// Header files:
#include "klib/kio.h"
#include "klib/kstring.h"
#include "klib/kstdlib.h"
#include <stdarg.h>
#include <stdbool.h>

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
	// Escape button
	else if(x == 0x1B)
	{
		kprintf("Escape pressed");
	}
	// Printable character
	else if(x >= ' ')
	{
		bool Caps = getCapsStatus();
		
		// If caps lock is on and user typed letters:
		if((x >= 'a' && x <= 'z') && (Caps == true)) x -= 32;
		
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

// Prints args into x and puts it all on screen:
int vkprintf(const char *x, va_list args)
{
	for(int i = 0; x[i] != '\0'; i++)
	{
		if(x[i] == '%')
		{
			char string[128];
			int value = -1;
			switch(x[i + 1])
			{
				case '%': kprintch('%'); i++; break;
				case 'i': ; // Integer decimal:
					value = va_arg(args, int);
					if(value != -1)
					{
						kitoa(value, string, 10);
						for(int j = 0; string[j] != '\0'; j++) kprintch(string[j]);
						i++;
					}
					else
					{
						kprintch('?');
						i++;
					}
				break;
				case 'x': ; // Integer hexadecimal:
					value = -1;
					value = va_arg(args, int);
					if(value != -1)
					{
						kitoa(value, string, 16);
						for(int j = 0; string[j] != '\0'; j++) kprintch(string[j]);
						i++;
					}
					else
					{
						kprintch('?');
						i++;
					}
				break;
				case 'c': ; // Character:
					char *value_char = va_arg(args, char *);
					for(int k = 0; value_char[k] != '\0'; k++) kprintch(value_char[k]);
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
		for(int j = 0; j < 80; j++) kprintch(' ');
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
