//Jinux Kernel v0.03

#include "../drivers/vga/vga.h"
#include "../cpu/idt.h"
#include "../drivers/ps2/ps2.h"
#include "shell/parser.h"

void kmain(void) {
    clear_screen();
    print("Welcome to Jinux v0.03!\nType 'help' for a list of commands.\n");
    print(user);
    print("@jinux> ");
    idt_init();
    ps2_init();
    while (1);
}
