#!/bin/bash
set -e

BUILD=build
SRC=src

mkdir -p $BUILD

echo "[1] Compiling C files..."

gcc -m32 -ffreestanding -nostdlib -I$SRC -c \
$SRC/kernel/kernel.c -o $BUILD/kernel.o

gcc -m32 -ffreestanding -nostdlib -I$SRC -c \
$SRC/cpu/idt.c -o $BUILD/idt.o

gcc -m32 -ffreestanding -nostdlib -I$SRC -c \
$SRC/drivers/vga/vga.c -o $BUILD/vga.o

gcc -m32 -ffreestanding -nostdlib -I$SRC -c \
$SRC/drivers/ps2/ps2.c -o $BUILD/ps2.o

gcc -m32 -ffreestanding -nostdlib -I$SRC -c \
$SRC/kernel/shell/parser.c -o $BUILD/parser.o

echo "[2] Assembling ASM files..."

nasm -f elf32 $SRC/kernel/kernel.asm -o $BUILD/kernel_asm.o
nasm -f elf32 $SRC/kernel/interrupts.asm -o $BUILD/interrupts.o
nasm -f elf32 $SRC/kernel/ports.asm -o $BUILD/ports.o

echo "[3] Linking..."

ld -m elf_i386 -T $SRC/link.ld \
-o $BUILD/kernel.bin \
$BUILD/kernel.o \
$BUILD/idt.o \
$BUILD/vga.o \
$BUILD/ps2.o \
$BUILD/kernel_asm.o \
$BUILD/interrupts.o \
$BUILD/ports.o \
$BUILD/parser.o \

echo "[4] Running in QEMU..."
qemu-system-i386 -kernel $BUILD/kernel.bin
