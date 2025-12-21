#include "idt.h"
#include "../kernel/ports.h"

extern void keyboard_handler(void);
extern void load_idt(unsigned long *idt_ptr);

static struct IDT_entry IDT[IDT_SIZE];

void idt_init(void) {
    unsigned long handler = (unsigned long)keyboard_handler;
    unsigned long idt_ptr[2];

    IDT[0x21].offset_low  = handler & 0xFFFF;
    IDT[0x21].selector   = 0x08;
    IDT[0x21].zero       = 0;
    IDT[0x21].type_attr  = 0x8E;
    IDT[0x21].offset_high = handler >> 16;

    write_port(0x20, 0x11);
    write_port(0xA0, 0x11);
    write_port(0x21, 0x20);
    write_port(0xA1, 0x28);
    write_port(0x21, 0x00);
    write_port(0xA1, 0x00);
    write_port(0x21, 0x01);
    write_port(0xA1, 0x01);

    write_port(0x21, 0xFF);
    write_port(0xA1, 0xFF);

    idt_ptr[0] = (sizeof(struct IDT_entry) * IDT_SIZE) |
    ((unsigned long)IDT << 16);
    idt_ptr[1] = (unsigned long)IDT >> 16;

    load_idt(idt_ptr);
}
