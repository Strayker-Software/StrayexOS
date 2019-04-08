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

- void kmove_cursor(int x, int y)

Funkcja przesuwa kursor na ekranie w podane koordynaty.

Argumenty: pierwszy to współżędna X, drugra Y,

Zwraca: brak,

- void ksetattrib(char font, char bg)

Funkcja ustawia atrybuty koloru czcionki i tła dla ekranu.

Argumenty: pierwszy to kolor czcionki, drugi tła. Kody kolorów według standardu VGA.

Zwraca: brak,

- void kcls()

Funkcja czyści cały ekran.

Argumenty: brak,

Zwraca: brak,

- void kb_init()

Funkcja instaluje domyślny sterownik klawiatury w IRQ1.

Argumenty: brak,

Zwraca: brak,

- void kb_install(int x)

Funkcja instaluje wybrany sterownik klawiatury (z dostępnych).

Agrumenty: cyfra określająca, który sterownik zainstalować,

Zwraca: brak,

- void enable_cursor(unsigned char cursor_start, unsigned char cursor_end)

Funkcja uruchamia kursor terminala ekranu w wyznaczonym miejscu.

Argumenty: współżędne kursora,

Zwraca: brak,

- void disable_cursor()

Funkcja wyłącza (ukrywa) kursor na ekranie.

Argumenty: brak,

Zwraca: brak,

- void kbflush()

Funkcja czyszcząca dane klawiatury, bufor i ostatni wciśnięty przycisk.

Argumenty: brak,

Zwraca: brak,

- char *get_kb_buf()

Funkcja zwraca adres do bufora klawiatury.

Argumenty: brak,

Zwraca: adres w pamięci (do zapisania w wskaźniku),

- bool kb_status()

Funkcja sprawdza, czy sterownik klawiatury jest włączony.

Argumenty: brak,

Zwraca: wartość logiczna, prawda lub fałsz,

- void set_kb_status(bool x)

Funkcja włącza lub wyłącza sterownik klawiatury,

Argumenty: wartość logiczna, prawda lub fałsz,

Zwraca: brak,

- bool kb_buf_status()

Funkcja sprawdza, czy sterownik klawiatury podczas pisania ma zapisywać litery do bufora w pamięci.

Argumenty: brak,

Zwraca: wartośc logiczna, prawda lub fałsz,

- void set_kb_buf_status(bool x)

Funkcja włącza lub wyłącza zapis do bufora pisanych liter.

Argumenty: wartość logiczna, prawda lub fałsz,

- int get_cursor_x()

Funkcja zwracająca wartość współżędnej X kursora.

Argumenty: brak,

Zwraca: liczbę współżędnej typu "int",

- int get_cursor_y()

Funkcja zwracająca wartość współżędnej Y kursora.

Argumenty: brak,

Zwraca: liczbę współżędnej typu "int",

- unsigned char *get_layout()

Funkcja zwraca adres do tablicy znaków typu "unsigned char" ze sterownika klawiatury.

Argumenty: brak,

Zwraca: adres do tablicy znaków, do zmiennej typu "unsigned char *",

- char get_last_char()

Funkcja zwraca ostatnią literę z bufora klawiatury.

Argumenty: brak,

Zwraca: znak typu "char",
