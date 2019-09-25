/*
 Strayex Kernel
 v1.0.1
 Kernel Debug Functions
 Copyright 2019 Daniel Strayker Nowak
 All rights reserved
*/

#include "klib/kstdlib.h"
#include "klib/kdebug.h"
#include "klib/kstring.h"
#include <stdarg.h>

#define PORT 0x3F8  /* COM 1 */
 
// Prepare the COM1 serial port for writting:
void init_serial() {
   koutportb(PORT + 1, 0x00);    // Disable all interrupts
   koutportb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   koutportb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   koutportb(PORT + 1, 0x00);    //                  (hi byte)
   koutportb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
   koutportb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   koutportb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

// Checks if serial port is ready for input:
int is_transmit_empty() {
   return kinportb(PORT + 5) & 0x20;
}

// Write single character to port:
void write_serial(char a) {
   while (is_transmit_empty() == 0);
 
   koutportb(PORT, a);
}

// Help function for DebugWrite, givs int args in every %x position:
int vDebugWrite(const char *x, va_list args)
{
	for(int i = 0; x[i] != '\0'; i++)
	{
		if(x[i] == '%')
		{
			if(x[i + 1] == 'x')
			{
				int temp = -1;
				temp = va_arg(args, int);
				
				if(temp != -1)
				{ // TODO: Something' wrong!
					char Holder[] = {};
					kitoa(temp, Holder, 10);
					int HoldLen = kstrlen((unsigned char *)Holder);
					
					for(int a = 0; a < HoldLen; a++) write_serial(Holder[a]);
					
					i++;
				}
			}
			else write_serial(x[i]);
		}
		else write_serial(x[i]);
	}
	
	return 0;
}

// Write string to port:
void DebugWrite(const char *x, ...)
{
	va_list args;
	va_start(args, x);
	
	vDebugWrite(x, args);
	
	va_end(args);
}