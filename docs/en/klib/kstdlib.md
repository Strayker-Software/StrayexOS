# Kernel Standard Library Header

"kstdlib.h" is library to connect functions of general use, both for loading kernel and it's standard work.

Hint: every function with name starting with "k" is function from klib.

# Definitions

None.

# Functions

"kstdlib.h" is file wich mediate between"kstdlib.c" and other files. All functions are in it, except "pit_init()", wich is in "pit.c" file.

- unsigned char kinportb (unsigned short _port)

Function reads I/O port value.

Arguments: _port - port's number,

Returns: value from I/O port of type "unsigned char",

- void koutportb (unsigned short _port, unsigned char _data)

Function writes I/O port value.

Arguments: _port - port's number, _data - value to write,

Returns: none,

- void kswap(int* a, int* b)

Function swaps values in memory.

Arguments: a i b - adresses to values,

Returns: none,

- void kreverse(char str[])

Function reverses char table, character under 0 index is first, etc.

Arguments: character table of type "char",

Return: none,

- char *kitoa(int value, char *str, int base)

Function changes integer to character string in given number system. It's work is to change integer, for example: 10  of type "int", to character string with values: "1 0 \0", in decimal system.

Exampleof use:

```c
char str[3];
kitoa(10, str, 10);
// After this function, the content of array will be like this:
// "1 0 \0"!
```

Arguments: value - "int" to project, str - character array of type"char", base - base of number system [2 - 32],

Returns: address of destination's char array,

- void pit_init()

Functio installs function, that handles time to IRQ.

Arguments: none,

Return: none,

- void Int_on()

Function turns on interrupts, including system's, hardware's and software's interrupts.

Arguments: none,

Return: none,

- void Int_off()

Function turns off interrupts, including system's, hardware's and software's interrupts.

Arguments: none,

Return: none,
