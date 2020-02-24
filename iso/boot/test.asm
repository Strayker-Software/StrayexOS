moje:
    mov eax, 0x2
    mov edx, help_info
    int 0x80

twoje:
    mov eax, 0x0
    int 0x80

jmp $

help_info db "Type 'help' to show command list!", 0
