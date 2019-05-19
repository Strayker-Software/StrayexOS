# Kernel Stack Smash Protector

Plik "ssp.c" to kod dla odwołania dla ochrony przed "zmiażdżeniem" stosu. Działanie jest proste, funkcja zawieszająca system uruchamia się, gdy któraś z funkcji systemu przepełni pojemność stosu, lub wypcha na stos za dużą wartość.

SSP zapobiega dalszemu działaniu systemu, poprzez wejście w nieskończoną pętlę i powiadomienie użytkownika. Jedynym rozwiązaniem jest ponownie uruchomić system i znaleźć funkcję, która wywołała niestabilność systemu.

Jeśli problem będzie się powtarzał, zgłoś go w repozytorium.

## Definicje

Brak.

## Funkcje

- void attribute((noreturn)) __stack_chk_fail(void)

Funkcja zwieszająca system z powodu wykrycia niestabilności stosu.

Argumenty: brak,

Zwraca: funkcja nie wraca do wywołującego, zapętla się,
