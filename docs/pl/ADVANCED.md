# Zaawansowane informacje o Strayex

## Rozbudowa Strayex Kernel

By Strayex Kernel wykonało dodatkowe zadania dla użytkownika, w pliku "main.c" w funkcji "kmain()" trzeba dodać kod.
Aby skompilować jądro i uruchomić je, w folderze repozytorium, uruchom komendą "make" pełną kompilację i debugowanie w QEMU.
Poczekaj aż system się zbuduje i gotowe, twoje zmiany zostaną wykonane przez Strayex Kernel!

## Tryb Debugowania (Debug Mode)

Na potrzeby prac nad systemem, Strayex Kernel uruchamia się w trybie debugowania (Debug Mode).
Aby przełączyć jądro w zwykły tryb pracy, w pliku "main.c" znajdź linijkę ze zmienną typu logicznego "bool" o nazwie "if_debug" i zmień jej wartość na "false".
Aby skompilować jądro i uruchomić je, w folderze repozytorium, uruchom komendą "make" pełną kompilację i debugowanie w QEMU.
Poczekaj aż system się zbuduje i gotowe, Strayex Kernel uruchomi się według zmian!
