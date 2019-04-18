# Kernel In/Out Header

Header "kio.h" is library connecting all functions connected with standard input and output streams of Strayex Kernel.
Hint: every function with name starting with "k" is function from klib.

## Definitions

None.

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

Returns: none,

- int kprintint(int x, int base)

Function prints integer on screen in requested number system.
Watch out! Experimental, it can not work!

Arguments: first is integer to write, second is base of number system, in which to write integer on screen,

Returns: always 0,

- void kmove_cursor(int x, int y)

Function moves cursor on screen to given position.

Arguments: first is X coordinate, second is Y coordinate,

Returns: none,

- void ksetattrib(char font, char bg)

Function sets color attributes for font and background.

Arguments: first is font color, second is background color. Colors' codes are the same as in VGA standard.

Returns: none,

- void kcls()

Function clears whole screen.

Arguments: none,

Returns: none,

- void kb_init()

Function installs default keyboard driver in IRQ1.

Arguments: none,

Returns: none,

- void kb_install(int x)

Function installs choosen keyboard driver (from available).

Agruments: integer specifying, which driver to install,

Returns: none,

- void enable_cursor(unsigned char cursor_start, unsigned char cursor_end)

Function enables cursor of terminal in choosen place.

Arguments: cursor's coordinates,

Returns: none,

- void disable_cursor()

Function hides (disables) cursor on the screen.

Arguments: none,

Returns: none,

- void kbflush()

Function clears keyboard's data, buffer and last button pressed.

Arguments: none,

Returns: none,

- char *get_kb_buf()

Function returns address to keyboard's buffer.

Arguments: none,

Returns: address in memory (to save it in pointer),

- bool kb_status()

Function checks, if keyboard driver is on.

Arguments: none,

Returns: logical value, true or false,

- void set_kb_status(bool x)

Function turns on or off keyboard driver,

Arguments: logical value, true or false,

Returns: none,

- bool kb_buf_status()

Function checks, if keyboard driver have to write characters from screen to keyboard's buffer too.

Arguments: none,

Returns: logical value, true or false,

- void set_kb_buf_status(bool x)

Function turns on or off saving characters to keyboard's buffer.

Arguments: logical value, true or false,

- int get_cursor_x()

Function returns cursor's X coordinate.

Arguments: none,

Returns: number of type "int",

- int get_cursor_y()

Function returns cursor's Y coordinate.

Arguments: none,

Returns: number of type "int",

- unsigned char *get_layout()

Functions returns address to characters' table of type "unsigned char" from keyboard's driver.

Arguments: none,

Returns: address to char table, variable type is "unsigned char *",

- char get_last_char()

Function returns last character from keyboard's buffer.

Arguments: none,

Returns: character of type "char",
