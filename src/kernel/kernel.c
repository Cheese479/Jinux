//Jinux Kernel v0.01

#include "../drivers/vga/vga.h"
#include "../cpu/idt.h"
#include "../drivers/ps2/ps2.h"

void kmain(void) {
    clear_screen();
    print("Welcome to Jinux!\nType 'help' for a list of commands.\n");

    idt_init();
    ps2_init();

    while (1);
}