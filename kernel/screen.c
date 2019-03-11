/*
 Strayex Kernel
 v1.0
 Screen VGA driver
 Copyright 2019 Daniel Strayker Nowak
 All rights reserved
*/

#include "klib/kio.h"
#include "klib/kstring.h"
#include "klib/kstdlib.h"

unsigned short *videomem = (unsigned short *)0xB8000;
int attrib = 0x0F;
int px = 0, py = 0;

void kmove_cursor()
{
    unsigned temp;
    temp = py * 80 + px;

    koutportb(0x3D4, 14);
    koutportb(0x3D5, temp >> 8);
    koutportb(0x3D4, 15);
    koutportb(0x3D5, temp);
}

void ksetattrib(char font, char bg)
{
	attrib = (bg << 4) | (font & 0x0F);
}

void kprintch(unsigned char x)
{
	// Backspace
	if(x == 0x08)
	{
		if(px >= 0)
		{
			ps--;
			unsigned att = attrib << 8;
			unsigned short *where = videomem + (py * 80 + px);
			*where = ' ' | att;
		}
		else if(px < 0)
		{
			px = 0;
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

	if(px >= 80)
	{
		px = 0;
		py++;
	}

	if(px < 0) px = 0;
	if(py < 0) py = 0;

	kmove_cursor();
}

void kcls()
{
	for(int i = 0; i < 25; i++)
	{
		for(int j = 0; j < 80; i++) kprintch(' ');
	}

	px = 0;
	py = 0;

	kmove_cursor();
}

void kprintf(char *x)
{
	int n = kstrlen((unsigned char *)x);
	for(int i = 0; i < n; i++) kprintch(x[i]);
}
