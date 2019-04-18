# Kernel String Header

"kstring.h" is library, that connects functions to operate on characters' strings.

Hint: every function with name starting with "k" is function from klib.

# Definitions

None.

# Functions

"kstring.h" is mediate file of "kstring.c".

- int kstrlen(unsigned char *x)

Function counts how many letters have got given char array.

Arguments: character array of type"char",

Returns: length of char array, without NULL char,

- unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count)

Function copies given amount of bytes from given source memory to given destination memory.

Arguments: dest - destination memory, src - source, count - amount of bytes to copy,

Returns: destination's mamory address,

- unsigned char *memset(unsigned char *dest, unsigned char val, int count)

Function sets given memory space in given value.

Argumeny: dest - destination memory, val - value to set in dest, count - amount of bytes to set,

Returns: destination's mamory address,

- unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)

Function works the same as memset, but it works on 16-bit value to set.

- char *kstrcpy(char *src, char *dest);

Function copies one string to another, replaces the second one.

Arguments: src - source char array, dest - destination char array,

Returns: destination's mamory address,

- char *kstrcpyw(char *src)

Function works the same as kstrcpy, but it deletes the last char form given string.
