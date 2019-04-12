# Kernel String Header

"kstring.h" to biblioteka łącząca funkcje do operacji na ciągach znaków.

Podpowiedź: każda funkcja zaczynająca się na "k" to funkcja z biblioteki jądra.

# Definicje

Brak.

# Funkcje

"kstring.h" jest plikiem pośrednim pliku "kstring.c".

- int kstrlen(unsigned char *x)

Funkcja licząca, ile litera ma dany ciąg znaków.

Argumenty: tablica znaków typu "char",

Zwraca: długość tablicy znaków, bez znaku NULL,

- unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count)

Funkcja kopiuje daną ilość bajtów z żródła do pamięci docelowej.

Argumenty: dest - pamięć docelowa, src - źródło, count - ilość danych do skopiowania,

Zwraca: adres pamięci docelowej,

- unsigned char *memset(unsigned char *dest, unsigned char val, int count)

Funkcja ustawia daną ilość pamięci docelowej w daną wartość.

Argumeny: dest - pamięć docelowa, val - wartość do ustawienia w pamięci, count - ilość danych do ustawienia,

Zwraca: adres pamięci docelowej,

- unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)

Funkcja działająca dokładnie tak samo, jak memset, lecz działająca na 16-bitowej wartości do ustawienia.

- char *kstrcpy(char *src, char *dest);

Funkcja kopiująca jeden ciąg znaków do drugiego, zastępując jego zawartość.

Argumenty: src - ciąg znaków źródłowy, dest - ciąg znaków docelowy,

Zwraca: adres pamięci docelowej,

- char *kstrcpyw(char *src)

Funkcja działająca dokładnie tak samo, jak kstrcpy, lecz zamiast kopiować napis do innego, usuwa ostatnią literę z ciągu znaków, podanego jako argument.
