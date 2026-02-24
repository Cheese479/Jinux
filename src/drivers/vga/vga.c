#include "vga.h"
#include "../../kernel/ports.h"

char *vidmem = (char*)0xB8000; //VGA text mode memory
int cursor = 0; // cursor

void clear_screen() {
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        vidmem[i] = ' ';
        vidmem[i+1] = 0x07;
    }
    cursor = 0;
}

void print(const char *str) {
    while (*str) {
        vga_putc(*str++);
    }
}

void vga_putc(char c) {
    if (c == '\n') { // newline
        if (cursor / 2 / 80 >= 24) {
            // scroll up
            for (int i = 0; i < (80 * 24 * 2); i++) {
                vidmem[i] = vidmem[i + (80 * 2)];
            }
            // clear last line
            for (int i = (80 * 24 * 2); i < (80 * 25 * 2); i += 2) {
                vidmem[i] = ' ';
                vidmem[i + 1] = 0x07;
            }
            cursor -= (80 * 2);
		}
        cursor += (80 * 2) - (cursor % (80 * 2));
        vga_update_cursor();
        return;
    }
 
    if (c == '\b') { // backspace
        if (cursor >= 2) {
            cursor -= 2;
            vidmem[cursor] = ' ';
            vidmem[cursor + 1] = 0x07;
        }
        vga_update_cursor();
        return;
    }

    if (c == '\t') { // tab
        for (int i = 0; i < 4; i++)
            vga_putc(' ');
        return;
    }

    if (c == 27) { // escape
        return;
    }


    vidmem[cursor++] = c;
    vidmem[cursor++] = 0x07;

    vga_update_cursor();

}

static void vga_update_cursor(void) {
    unsigned short pos = cursor / 2;

    write_port(0x3D4, 0x0F);
    write_port(0x3D5, pos & 0xFF);
    write_port(0x3D4, 0x0E);
    write_port(0x3D5, (pos >> 8) & 0xFF);

}

