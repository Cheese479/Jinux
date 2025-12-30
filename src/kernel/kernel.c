//Jinux Kernel v0.02

#include "../drivers/vga/vga.h"
#include "../cpu/idt.h"
#include "../drivers/ps2/ps2.h"

void kmain(void) {
    clear_screen();
    print("Welcome to Jinux v0.02!\nType 'help' for a list of commands.\n");
    print("> ");
    idt_init();
    ps2_init();
    while (1);
}
