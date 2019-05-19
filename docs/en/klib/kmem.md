# Kernel Memory Header

"kmem.h" is header, that connects all memory manager's functions. In this file are links to two main memory management functions - "kmalloc" and "kfree".

Memory manager is so called "Waterflow mark". It's reserves memory, from the lowest address to the highest, releases inversely.

## Definitions

None.

## Functions

- bool mem_init(unsigned int ram_in_kb)

Sets value of how many memory can manager use.

Arguments: unsigned integer, how many RAM has computer,

ReturnsL always true,

- void *kmalloc(int size)

Function allocates given amount of bytes in memory.

Argumenty: integer, amount bytes to reserve,

Returns: address to allocated memory,

- void kfree(void *addr)

Function releases memory under given address.

Arguments: address to memory to be free,

Returns: none,
