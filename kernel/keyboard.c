/*
 Strayex Kernel
 v1.0
 Kernel's PS/2 keyboard driver
 Copyright 2019 Daniel Strayker Nowak
 All rights reserved
*/

// Header files:
#include "klib/kdt.h"
#include "klib/kio.h"
#include "klib/kstdlib.h"
#include <stdbool.h>

// Variables:
bool if_enabled = true; // Used to turn off and on keyboard input,
bool if_buffer_enabled = true; // Used to determine, if handler have to push char to buffer,
int buf_lvl = 0; // Keeps track on buffer length, don't reset to zero in code, use kbflush() function,
char kb_buffer[100000]; // Kernel's keyboard buffer,

// US QWERTY keyboard layout:
unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

// Clears keyboard buffer:
void kbflush()
{
	for(int i = 0; i < buf_lvl; i++) kb_buffer[i] = '\0';
	buf_lvl = 0;
}

// Gets address to keyboard's buffer:
char *get_kb_buf() { return kb_buffer; }

// Returns status of keyboard driver:
bool kb_status() { return if_buffer_enabled; }

// Sets keyboard driver on or off:
void set_kb_status(bool x) { if_enabled = x; }

// Return status of keyboard buffer:
bool kb_buf_status() { return if_buffer_enabled; }

// Sets status of keyboard buffer:
void set_kb_buf_status(bool x) { if_buffer_enabled = x; }

// Default keyboard handler, printing chars on screen:
void keyboard_handler()
{
    if(if_enabled)
	{
		unsigned char scancode;

		/* Read from the keyboard's data buffer */
		scancode = kinportb(0x60);

		/* If the top bit of the byte we read from the keyboard is
		*  set, that means that a key has just been released */
		if (scancode & 0x80)
		{
			/* You can use this one to see if the user released the
			*  shift, alt, or control keys... */
		}
		else
		{
			unsigned char ch = kbdus[scancode]; // Make ASCII character from scancode,

			// Checks, if function have to push char to buffer:
			if(if_buffer_enabled)
			{
				kb_buffer[buf_lvl] = ch;
				buf_lvl++;
			}
			kprintch(ch); // Print ch on screen,
		}
	}
}

// On kernel start up, sets default KB handler:
void kb_init()
{
	irq_install_handler(1, keyboard_handler);
}
