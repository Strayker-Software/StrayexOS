# Fortgeschrittene Informationen über Strayex

## Strayex Kernel Erweiterung

Um den Strayex Kernel zusätzliche Aufgaben ausführen zu lassen, muss der Benutzer Code in Datei "main.c" zur Funktion "kmain()" einfügen.
Um den Code zu kompilieren und auszuführen, führe im Quell Verzeichniss den  Befehl "make" aus, dies wird das kompileren und debuggen in Qemu starten.
Warte bis das Betriebssystem fertig gebaut ist. Deine Änderung wird nun vom Strayex Kernel ausgeführt!

## Debug Mode

Weil am Betriebssystemfortschritt gearbeitet wird, startet der  Strayex Kernel standardmäßig im Debug Mode.
Um den Kernel in den normalen Arbeitsmodus zu versetzen, finde die Zeile mit dem logischen "Bool" Wert "if_debug" in der Datei "main.c" und ändere seinen Wert zu "false".
Um den Code zu kompilieren und auszuführen, führe im Quell Verzeichniss den  Befehl "make" aus, dies wird das kompileren und debuggen in Qemu starten.
Warte bis das Betriebsysstem fertig gebaut ist. Der Strayex Kernel wird nun im Veränderten Modus starten
