#ifndef VGA_H
#define VGA_H

void print(const char *str);
void vga_putc(char c);
void clear_screen(void);
static void vga_update_cursor(void);

#endif
