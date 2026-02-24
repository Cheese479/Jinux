#include "stdio.h"

void putchar(char c) {
    vga_putc(c);
}

void puts(const char *str) {
    while (*str) {
        putchar(*str++);
    }
    putchar('\n');
}