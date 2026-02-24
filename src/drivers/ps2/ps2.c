#include "ps2.h"
#include "ps2_map.h"
#include "../../kernel/ports.h"
#include "../vga/vga.h"

#define DATA   0x60
#define STATUS 0x64

static int shift_pressed = 0;
static int caps_lock = 0;

extern char user[16]; // defined in parser.c

char cmd[256];
int x = 0;

extern void parser(void);

void ps2_init(void) {
    write_port(0x21, 0xFD); // enable IRQ1
}

void ps2_handler_main(void) {
    unsigned char key;
    char c;

    write_port(0x20, 0x20); // EOI

    if (!(read_port(STATUS) & 1))
        return;

    key = read_port(DATA); //read data from PS/2 keyboard

    if (key == 0x2A || key == 0x36) { // shift press
        shift_pressed = 1;
        return;
    }

    if (key == 0xAA || key == 0xB6) { // shift release
        shift_pressed = 0;
        return;
    }

    if (key == 0x3A) { // caps lock
        caps_lock ^= 1;
        return;
    }

    // ignore key release
    
    if (key & 0x80)
        return;

    // enter

    if (key == 0x1C) {
        cmd[x] = '\0';
        vga_putc('\n');
        parser();
        x = 0;
        print(user);
        print("@jinux> ");
        return;
    }

    if (key == 0x0E) { // backspace
        if (x > 0) {
            x--;
            vga_putc('\b');
        }
        else {
            return;
        }
        return;
    }

    // normal keys

    if (shift_pressed ^ caps_lock)
        c = ps2_map_shift[key];
    else
        c = ps2_map[key];

    if (!c)
        return;

    if (x < sizeof(cmd) - 1) {
        cmd[x++] = c;
        vga_putc(c);
    }
}
