bits 32
section .text
global load_idt
global keyboard_handler
extern ps2_handler_main

load_idt:
    mov edx, [esp + 4]
    lidt [edx]
    sti
    ret

keyboard_handler:
    call ps2_handler_main
    iretd
