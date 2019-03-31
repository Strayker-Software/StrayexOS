# Kernel In/Out Header

Header "kio.h" is library connecting all functions connected with standard input and output streams of Strayex Kernel.
Hint: every function with name starting with "k" is function from klib.

## Definitions

Brak.

## Functions

"kio.h" connects functions from many files, for example: "keyboard.c" or "screen.c":

- void kprintch(char x)

Function interprets single character and writes it on screen,

Arguments: character of type char,

Returns: none,

- void kprintf(const char *x, ...)

Functions prints string on screen.

Arguments: Kernel doesn't support "string" type. kprintf takes as argument one-dimensional character table of type "char".
As additional arguments it accepts data, taht can be inserted in place "%" char. This function is almost full ANSI C standard function.

Returns: brak,

- int kprintint(int x, int base)

Function prints integer on screen in requested number system.
Watch out! Experimental, it can not work!

Arguments: first is integer to write, second is base of number system, in which to write integer on screen,

Returns: always 0,

- 
