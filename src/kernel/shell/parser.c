#include "../../drivers/vga/vga.h"
#include "parser.h"

/* defined in ps2.c */
extern char cmd[256];

void parser(void) {

    //shutdown
    if (cmd[0] == 's' && cmd[1] == 'h' && cmd[2] == 'u' &&
        cmd[3] == 't' && cmd[4] == 'd' && cmd[5] == 'o' &&
        cmd[6] == 'w' && cmd[7] == 'n' && cmd[8] == '\0') {

        __asm__ volatile (
            "cli\n\t"     // Disable maskable interrupts
            "hlt"         // Halt the CPU
            ::: "memory"
        );
    }

    //clear
    if (cmd[0] == 'c' && cmd[1] == 'l' && cmd[2] == 'e' &&
        cmd[3] == 'a' && cmd[4] == 'r' && cmd[5] == '\0') {

        clear_screen();
    }

    //ver
    if (cmd[0] == 'v' && cmd[1] == 'e' && cmd[2] == 'r' && cmd[3] == '\0') {
        print("Jinux v0.01 by James Baum published with the MIT license on December 21st 2025\n");
    }

    //help
    if (cmd[0] == 'h' && cmd[1] == 'e' && cmd[2] == 'l' && cmd[3] == 'p' && cmd[4] == '\0') {
        print("Available commands:\n");
        print("clear - clear the screen\n");
        print("shutdown - halt the cpu\n");
        print("version - display the version of Jinux\n");
        print("help - display this help message\n");
        print("about - display information about Jinux!\n");
    }

    //about
    if (cmd[0] == 'a' && cmd[1] == 'b' && cmd[2] == 'o' && cmd[3] == 'u' && cmd[4] == 't' && cmd[5] == '\0') {
        print("Jinux is an OS by me (James Baum) and aims to one day in the future become something great!\nBut right now it's not much, you can contribute by going to https://github.com/Cheese479/Jinux\n");
    }
}
