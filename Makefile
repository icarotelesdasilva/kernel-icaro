# Kernel-Ícaro (vmicaro)
# Copyright (c) 2026 Ícaro Teles da Silva (@icarotelesdasilva)

ASM     = nasm
CC      = gcc
LD      = ld -m elf_i386
CONVERT = convert

CFLAGS = -m32 -ffreestanding -nostdlib -fno-pic -Iinclude

OBJ = arch/i386/boot.o \
      arch/i386/gdt_asm.o \
      arch/i386/gdt.o \
      arch/i386/idt_asm.o \
      arch/i386/idt.o \
      drivers/vga.o \
      kernel/kernel.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

arch/i386/boot.o: arch/i386/boot.asm
	$(ASM) -f elf32 arch/i386/boot.asm -o arch/i386/boot.o

arch/i386/gdt_asm.o: arch/i386/gdt.asm
	$(ASM) -f elf32 arch/i386/gdt.asm -o arch/i386/gdt_asm.o

arch/i386/idt_asm.o: arch/i386/idt.asm
	$(ASM) -f elf32 arch/i386/idt.asm -o arch/i386/idt_asm.o

vmicaro: $(OBJ)
	$(LD) -T arch/i386/linker.ld $(OBJ) -o vmicaro

all: vmicaro
	mkdir -p isodir/boot/grub
	cp vmicaro isodir/boot/vmicaro
	cp grub/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o vmicaro.iso isodir/

clean:
	rm -f $(OBJ) vmicaro vmicaro.iso
	rm -rf isodir/
