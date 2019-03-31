# Kernel In/Out Header

Nagłówek "kio.h" to biblioteka łącząca wszystkie funkcje związane z standardowym strumieniem wejścia i wyjścia jądra Strayex Kernel.
Podpowiedź: każda funkcja zaczynająca się na "k" to funkcja z biblioteki jądra.

## Definicje

Brak.

## Funkcje

"kio.h" łączy funkcje z wielu plików mi.: "keyboard.c" czy "screen.c":

- void kprintch(char x)

Funkcja interpretująca jedną literę i wypisuje ją na ekranie,

Argumenty: znak typu char,

Zwraca: brak,

- void kprintf(const char *x, ...)

Funkcja wyświetlająca napis na ekranie.

Argumenty: Jądro nie obsługuje typu "string". kprintf przyjmuje jednowymiarową tablicę znaków typu "char".
Jako dodatkowe argumenty przyjmuje dane, które można napisać w miejscu kodu "%". Ta funkcja prawie całkowicie spełnia standard ANSI C.

Zwraca: brak,

- int kprintint(int x, int base)

Funkcja wypisuje na ekranie liczbę w danym systemie.
Uwaga! Eksperymentalna, może nie działać!

Argumenty: pierwszy to liczba do wypisania, drugi to baza systemu liczbowego, w którym wypisać liczbę,

Zwraca: zawsze 0,

- 
