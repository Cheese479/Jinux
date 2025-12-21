;;kernel.asm
bits 32			;nasm directive - 32 bit
section .text

; multiboot header
section .multiboot
align 4
dd 0x1BADB002              ; magic
dd 0x0                     ; flags
dd -(0x1BADB002 + 0x0)     ; checksum


global start
extern kmain	        ;kmain is defined in the c file

start:
  cli 			;block interrupts
  mov esp, stack_space	;set stack pointer
  call kmain
  hlt		 	;halt the CPU

section .bss
resb 8192		;8KB for stack
stack_space:
