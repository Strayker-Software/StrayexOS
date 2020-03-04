;mov eax, 0x0 ; Strayex System Call number 0: test syscall,
;int 0x80 ; Rise interrupt

mov eax, 0x1 ; Strayex System Call number 1: print kernel version info,
int 0x80 ; Rise interrupt

mov eax, 0x2 ; Strayex System Call number 2: print data on screen,
int 0x80 ; Rise interrupt

mov eax, 0x3 ; Strayex System Call number 3: make new line
int 0x80 ; Rise interrupt

; Loop forever!
jmp $

; Data:
help_info db "Type 'help' to show command list!", 0
