# Wie fange ich an mit Strayex zu arbeiten?

Wie es in README.md geschrieben steht, gibt es drei Wege.
Erstens, Lade die vorgefertigte ISO Datei mit Kernel und Bootloader herunter
Zweitens, Lade die vorgefertigte Binärdatei des Kernels mit dem Namen "skern-(wersja).bin" herunter und füge sie enem Gerät mit installierten Bootloader hinzu
Drittens, Baue den Kernel selbst und füge ihn einem Gerät mit installierten Bootloader hinzu.
Viertens, führe den Kernel im QEMU mit dem Parameter -kernel aus

## Strayex ausführen

Wählst du einer dieser Möglichkeiten aus ist das Betriebssystem nun bereit auf Virtuellen Maschinen wie QEMU, VirtualBox or VMWare zu laufen. Du brauchst einfach nur eine VM mit der ISO zu starten und schon bist du fertig!

Es ist gut daran zu erinnern, das Strayex ein vollwertiges Betriebssystem ist das auf echter Hadware laufen kann. Ich rate allerdings davon ab. Um eine Virtuelle Maschine zu konfigurieren kannst du folgende Spezefikationen benutzen:
- 32-bit Prozessor, i386 kompatibel,
- mindestens 32 MB RAM,
- Monitor 80x25 VGA Verbindung, intigrierte Grafikeinheit,
- PS/2 Tastatur,
- Massenspeicher wird in dieser Version nicht benötigt,
Strayex ist mit einen Monolitischen Singletasking Kernel ausgestattet. Der Strayex Kernel benötigt Informationen vom Bootloader damit er funktionert.

Der Kerlnel des Betriebsystems ist kompatibel mit [Multiboot Specification](https://www.gnu.org/software/grub/manual/multiboot/multiboot.html) in der Version 2.0.
Der mit dieser Version kompatible Bootloader lädt eine sogenannte Multiboot Informations Struktur in den Speicher und lässt die Machine im defienierten Zustand

Wenn du nach dem Start des Systems eine Textzeile mit dem Inhalt "Strayex Kernel" und eine leere Debug Mode Zeile siehst bedeutet dass du das Betriebsystem erfolgreich gestartet hast.
## Die Ersten Schritte in Strayex
StrayexOS Pretorian, ist in einer sehr frühen Phase der Entwicklung und hat keine Shell
Das hat einen simplen Grund - Der Strayex Kernel kann die Shell noch nicht ausführen 
Grundlegende Dinge wie auf dem Bildschirm schreiben, können allerdings reibungslos ausgeführt werden (:

Um zusätzliche Aufgaben auszuführen, muss der Code des Kernels erst bearbeitet und neu kompiliert werden.

## Was kommt als nächstes?

Wie bereits erwähnt, ist Strayex in einer sehr frühen Entwicklungsphase und hat noch keine richtigen Funktionen.
Wenn du wissen möchtest welche Funktionen als nächstes zum Projekt hinzugefügt werden sollen kannst du dir das ansehen:  [TODO.md](https://github.com/StraykerPL/StrayexOS/blob/master/docs/TODO.md)

Jetzt weißt du über die Grundlagen von Strayex bescheid! Gehe zu [BASIC.md](https://github.com/StraykerPL/StrayexOS/blob/master/docs/pl/BASIC.md) um fortzufahren.
