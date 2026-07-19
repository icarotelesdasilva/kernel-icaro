# Kernel-Ícaro (vmicaro)
# Copyright (c) 2026 Ícaro Teles da Silva (@icarotelesdasilva)
.PHONY: all run clean

ASM     = nasm
CC      = gcc
LD      = ld -m elf_i386
CONVERT = convert

CFLAGS = -m32 -ffreestanding -nostdlib -fno-pic -Iinclude

OBJ = arch/i386/boot/boot.o \
      arch/i386/cpu/gdt_asm.o \
      arch/i386/cpu/gdt.o \
      arch/i386/cpu/idt_asm.o \
      arch/i386/cpu/idt.o \
      arch/i386/drivers/vga.o \
      arch/i386/drivers/kernel_panic.o \
      arch/i386/mm/pmm.o \
	arch/i386/cpu/pic.o \
      kernel/kernel.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

arch/i386/boot/boot.o: arch/i386/boot/boot.asm
	$(ASM) -f elf32 arch/i386/boot/boot.asm -o arch/i386/boot/boot.o

arch/i386/cpu/gdt_asm.o: arch/i386/cpu/gdt.asm
	$(ASM) -f elf32 arch/i386/cpu/gdt.asm -o arch/i386/cpu/gdt_asm.o

arch/i386/cpu/idt_asm.o: arch/i386/cpu/idt.asm
	$(ASM) -f elf32 arch/i386/cpu/idt.asm -o arch/i386/cpu/idt_asm.o

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

run: vmicaro.iso
	qemu-system-x86_64 -cdrom vmicaro.iso
.PHONY: all run clean

