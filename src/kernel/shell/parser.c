#include "../../drivers/vga/vga.h"
#include "parser.h"

/* defined in ps2.c */
extern char cmd[256];
char user[16] = "user";

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
        return;
    }

    //ver
    if (cmd[0] == 'v' && cmd[1] == 'e' && cmd[2] == 'r' && cmd[3] == '\0') {
        print("Jinux v0.03 by James Baum published with the MIT license on January 23rd 2026\n");
        return;
    }

    //help
    if (cmd[0] == 'h' && cmd[1] == 'e' && cmd[2] == 'l' && cmd[3] == 'p' && cmd[4] == '\0') {
        print("Available commands:\n");
        print("clear - clear the screen\n");
        print("shutdown - halt the cpu\n");
        print("ver - display the version of Jinux\n");
        print("help - display this help message\n");
        print("about - display information about Jinux!\n");
        print("echo - print text to the screen!\n");
        print("calc - simple calculator (format: calc A + B) (note: doesnt work if the result is greater than 9 and only works with integers)\n");
	print("un - change your username (format: un NEWNAME)\n");
        return;
    }

    //about
    if (cmd[0] == 'a' && cmd[1] == 'b' && cmd[2] == 'o' && cmd[3] == 'u' && cmd[4] == 't' && cmd[5] == '\0') {
        print("Jinux is an OS by me (James Baum) and aims to one day in the future become something great!\nBut right now it's not much, you can contribute by going to https://github.com/Cheese479/Jinux\n");
        return;
    }
    //echo
    if (cmd[0] == 'e' && cmd[1] == 'c' && cmd[2] == 'h' &&
        cmd[3] == 'o' && cmd[4] == ' ') {
        //print everything after "echo "
        int i = 5;
        while (cmd[i] != '\0') {
            print((const char[]){cmd[i], '\0'});
            i++;
        }
        print("\n");
        return;
    }
    //calc
    if (cmd[0] == 'c' && cmd[1] == 'a' && cmd[2] == 'l' &&
        cmd[3] == 'c' && cmd[4] == ' ') {
        int a = cmd[5] - '0';
        int b = cmd[9] - '0'; 
        int x;
        if (cmd[7] == '+') {
            int x = a + b;
            char out[2];
            out[0] = x + '0';
            out[1] = '\0';
            print(out);
            print("\n");
        }
        if (cmd[7] == '-') {
            int x = a - b;
            char out[2];
            out[0] = x + '0';
            out[1] = '\0';
            print(out);
            print("\n");
        }
        if (cmd[7] == '*') {
            int x = a * b;
            char out[2];
            out[0] = x + '0';
            out[1] = '\0';
            print(out);
            print("\n");
        }
        if (cmd[7] == '/') {
            int x = a / b;
            char out[2];
            out[0] = x + '0';
            out[1] = '\0';
            print(out);
            print("\n");
        }
        return;
    }
    //change username
    if (cmd [0] == 'u' && cmd[1] == 'n' && cmd[2] == ' ') {
        int i = 3;
        int j = 0;
        while (cmd[i] != '\0' && j < 15) {
            user[j] = cmd[i];
            i++;
            j++;
        }
        user[j] = '\0';
		return;
    }
    else {
        //print unknown command message
        if (!(cmd[0] == '\0')) {
            print("Unknown command. Type 'help' for a list of commands.\n");
        }
    }
}
