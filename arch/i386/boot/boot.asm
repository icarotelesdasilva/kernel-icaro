; Kernel-Ícaro (vmicaro)
; Copyright (c) 2026 Ícaro Teles da Silva (@icarotelesdasilva)

 bits 32

section .multiboot

align 4

dd 0x1BADB002
dd 0x00000003

dd -(0x1BADB002 + 0x00000003)

section .bss 

align 16
stack_bottom:
resb 16384
stack_top:

section .text
global _start
extern kmain

_start:

mov esp, stack_top
push ebx
push eax
call kmain
cli

.hang:

hlt 

jmp .hang 

