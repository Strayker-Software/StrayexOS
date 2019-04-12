# Kernel Standard Library Header

"kstdlib.h" to biblioteka łącząca funkcje ogólnego użytku, zarówno przy ładowaniu jądra oraz przy jego zwykłej pracy.

Podpowiedź: każda funkcja zaczynająca się na "k" to funkcja z biblioteki jądra.

# Definicje

Brak.

# Funkcje

"kstdlib.h" jest plikiem pośredniczącym pliku "kstdlib.c". Wszystkie funkcje są w nim zawarte, oprócz "pit_init()", która znajduje się w pliku "pit.c".

- unsigned char kinportb (unsigned short _port)

Funkcja odczytuje zawartość portu I/O.

Argumenty: _port - numer portu,

Zwraca: wartośc z portu I/O typu "unsigned char",

- void koutportb (unsigned short _port, unsigned char _data)

Funkcja zapisuje dane do portu I/O.

Argumenty: _port - numer portu, _data - wartość do zapisania,

Zwraca: brak,

- void kswap(int* a, int* b)

Funkcja zamienia ze sobą wartości w pamięci.

Argumenty: a i b - adresy do wartości,

Zwraca: brak,

- void kreverse(char str[])

Funkcja odwraca ciąg znaków, litera pod indeksem 0 jest ostatnia, itd.

Argumenty: tablica znaków typu "char",

Zwraca: brak,

- char *kitoa(int value, char *str, int base)

Funkcja zamienia wartość liczbową całkowitą na ciąg znaków w danym systemie liczbowym. Jej działanie to zmiana wartości np. 10  w zmiennej typu "int", na ciąg znaków z wartościami: "1 0 \0", w systemie dziesiętnym.

Przykład użycia:

```int x = 10;
char str[3];
kitoa(10, str, 10);
// Po tej funkcji, zawartość str będzie wyglądać tak: "1 0 \0"!
```

Argumenty: value - "int" do zrzutowania, str - tablica znaków typu "char", base - baza systemu liczbowego [2 - 32],

Zwraca: adres docelowej tablicy znaków,

- void pit_init()

Funkcja instaluje funkcję obsługującą czas w jądrze do IRQ.

Argumenty: brak,

Zwraca: brak,

- void Int_on()

Funkcja włącza przerwania, w tym przerwania systemowe, sprzętowe i programowe.

Argumenty: brak,

Zwraca: brak,

- void Int_off()

Funkcja wyłącza przerwania, w tym przerwania systemowe, sprzętowe i programowe.

Argumenty: brak,

Zwraca: brak,
