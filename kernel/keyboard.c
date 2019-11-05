/*
 Strayex Kernel
 v1.0.1
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
char last_key; // Last character from buffer,

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
    0,	/* 72 - Up Arrow */
    0,	/* 73 - Page Up */
  '-', // 74
    0,	/* 75 - Left Arrow */
    0, // 76
    0,	/* 77 - Right Arrow */
  '+', // 78
    0,	/* 79 - End key*/
    0,	/* 80 - Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

/*
int kbdusysh[128] =
{
0,  0, '!', '"', '£', '$', '%', '^', '&', '*',   // 9
  '(', ')', '_', '+', '\b', '\t',
  'Q', 'W', 'E', 'R',
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',      // Enter key
    0,         //29   - Control
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';',   // 39
'|', '¬',   42,      // Left shift
'\\', 'Z', 'X', 'C', 'V', 'B', 'N',         // 49
  'M', '<', '>', '?',   0,               // Right shift
  0,
    0,   // Alt
  ' ',   // Space bar
    58,   // Caps lock
    0,   // 59 - F1 key ... >
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   // < ... F10
    0,   // 69 - Num lock
    0,   // Scroll Lock
    0,   // Home key
    0,   // Up Arrow
    0,   // Page Up
  '-',
    0,   // Left Arrow
    0,
    0,   // Right Arrow
  '+',
    0,   // 79 - End key
    0,   // Down Arrow
    0,   // Page Down
    0,   // Insert Key
    0,   // Delete Key
    0,   0,   0,
    0,   // F11 Key
    0,   // F12 Key
    0,   // All other keys are undefined
};
*/

// Clears keyboard buffer:
void kbflush()
{
	for(int i = 0; i < buf_lvl; i++) kb_buffer[i] = '\0';
	buf_lvl = 0;
}

// Gets address to keyboard's buffer:
char *get_kb_buf() { return kb_buffer; }

// Returns status of keyboard driver:
bool kb_status() { return if_enabled; }

// Sets keyboard driver on or off:
void set_kb_status(bool x) { if_enabled = x; }

// Return status of keyboard buffer:
bool kb_buf_status() { return if_buffer_enabled; }

// Sets status of keyboard buffer:
void set_kb_buf_status(bool x) { if_buffer_enabled = x; }

// Gets address to default layout:
unsigned char *get_layout() { return kbdus; }

// Gets last character from keyboard buffer:
char get_last_char()
{
	last_key = kb_buffer[buf_lvl];
	return last_key;
}

/*
 Notepad keyboard handler, printing chars on screen, moves cursor through all screen.
 Useful in for example notepad application.
*/
void keyboard_handler_notepad()
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
			//if(scancode & 0x1C)
			/* You can use this one to see if the user released the
			*  shift, alt, or control keys... */
		}
		else
		{
			unsigned char ch = kbdus[scancode]; // Make ASCII character from scancode,
			
			int cx = get_cursor_x();
			int cy = get_cursor_y();
			
			// Up arrow
			if(scancode == 'H')
			{
				--cy;
				kmove_cursor(cx, cy);
				return;
			}
			// Left arrow
			else if(scancode == 'K')
			{
				--cx;
				kmove_cursor(cx, cy);
				return;
			}
			// Right arrow
			else if(scancode == 'M')
			{
				++cx,
				kmove_cursor(cx, cy);
				return;
			}
			// Down arrow
			else if(scancode == 'P')
			{
				++cy;
				kmove_cursor(cx, cy);
				return;
			}
			
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

// CLI handler, moves cursor only in one line:
void keyboard_handler_cli()
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
			//if(scancode & 0x1C)
			/* You can use this one to see if the user released the
			*  shift, alt, or control keys... */
		}
		else
		{
			unsigned char ch = kbdus[scancode]; // Make ASCII character from scancode,
			
			int cx = get_cursor_x();
			int cy = get_cursor_y();
			
			// Up arrow
			if(scancode == 'H')
			{
				return;
			}
			// Left arrow
			else if(scancode == 'K')
			{
				--cx;
				kmove_cursor(cx, cy);
				return;
			}
			// Right arrow
			else if(scancode == 'M')
			{
				++cx,
				kmove_cursor(cx, cy);
				return;
			}
			// Down arrow
			else if(scancode == 'P')
			{
				return;
			}
			
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

// Development keyboard handler, prints scancodes on screen:
void keyboard_handler_scancode()
{
	if(if_enabled)
	{
		unsigned int scancode;

		scancode = kinportb(0x60);

		if (!(scancode & 0x80))
		{
			kprintch(scancode);
		}
	}
}

// Installs requested handler:
void kb_install(int x)
{
	if(x == 0) irq_install_handler(1, keyboard_handler_cli);
	else if(x == 1) irq_install_handler(1, keyboard_handler_scancode);
	else if(x == 2)  irq_install_handler(1, keyboard_handler_notepad);
}

// On kernel start up, sets default KB handler:
void kb_init()
{
	irq_install_handler(1, keyboard_handler_cli);
}
