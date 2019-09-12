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

#define PORT 0x3F8   /* COM 1 */
 
void init_serial() {
   koutportb(PORT + 1, 0x00);    // Disable all interrupts
   koutportb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   koutportb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   koutportb(PORT + 1, 0x00);    //                  (hi byte)
   koutportb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
   koutportb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   koutportb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

int is_transmit_empty() {
   return kinportb(PORT + 5) & 0x20;
}
 
void write_serial(char a) {
   while (is_transmit_empty() == 0);
 
   koutportb(PORT, a);
}

void DebugWrite(char *x)
{
	int n = kstrlen((unsigned char *)x);
	for(int i = 0; i < n; i++)
	{
		write_serial(x[i]);
	}
}