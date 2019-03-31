# Advanced info about Strayex

## Strayex Kernel expansion

To make Strayex Kernel execute additional work for user, in file "main.c" in function "kmain()" user have to add code.
To compile and run code, in repository's directory, run command "make", it will start full compiling and debugging in QEMU.
Wait while system is building and ready, yout changed will be executed by Strayex Kernel!

## Debug Mode

Because of working on system process, Strayex Kernel starts in Debug Mode by default.
To switch kernel to normal working mode, in file "main.c" find line with logical "bool" value called "if_debug" and change it's value "false".
To compile and run code, in repository's directory, run command "make", it will start full compiling and debugging in QEMU.
Wait while system is building and ready, Strayex Kernel will start with changed mode!
