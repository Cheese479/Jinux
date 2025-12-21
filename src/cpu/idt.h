#ifndef IDT_H
#define IDT_H

#define IDT_SIZE 256

struct IDT_entry {
    unsigned short offset_low;
    unsigned short selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short offset_high;
} __attribute__((packed));

void idt_init(void);

#endif
