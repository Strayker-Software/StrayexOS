/*
 Strayex Kernel C Library "klib"
 v1.0
 Kernel Standard Library file, access through "kstdlib.h"
 Copyright 2019 Daniel Strayker Nowak
 All rights reserved
 
 Code added to file from:
 https://www.geeksforgeeks.org/implement-itoa/
 https://stackoverflow.com/questions/3835922/simple-swap-function-why-doesnt-this-one-swap
*/

#include <stdbool.h>
#include "kstdlib.h"
#include "kstring.h"

// Reading from I/O ports:
unsigned char kinportb (unsigned short _port)
{
	unsigned char rv;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
	return rv;
}

// Writting from I/O ports:
void koutportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

// Swapping integers in memory:
void kswap(int* a, int* b)
{
 int temp = *a;
 *a = *b;
 *b = temp;
}

// Reversing strings:
void kreverse(char str[])
{
    int start = 0;
	int length = kstrlen((unsigned char *)str);
    int end = length -1;
    while (start < end)
    {
        kswap((int *)(str+start), (int *)(str+end));
        start++;
        end--;
    }
}

// Converting integer to char table:
char *kitoa(int num, char* str, int base)
{ 
	int i = 0; 
    bool isNegative = false; 
  
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0) 
    { 
        str[i++] = '0'; 
        str[i] = '\0'; 
        return str; 
    } 
  
    // In standard itoa(), negative numbers are handled only with  
    // base 10. Otherwise numbers are considered unsigned. 
    if (num < 0 && base == 10) 
    { 
        isNegative = true; 
        num = -num; 
    } 
  
    // Process individual digits 
    while (num != 0) 
    { 
        int rem = num % base; 
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
        num = num/base; 
    } 
  
    // If number is negative, append '-' 
    if (isNegative) 
        str[i++] = '-'; 
  
    str[i] = '\0'; // Append string terminator 
  
    // Reverse the string 
    kreverse(str); 
  
    return str; 
}

// Interrupt management:

// Enable interrupts:
void Int_on()
{
	asm("sti");
}

// Disable interrupts:
void Int_off()
{
	asm("cli");
}
