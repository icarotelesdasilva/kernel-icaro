# Kernel-Ícaro (vmicaro)
# Copyright (c) 2026 Ícaro Teles da Silva (@icarotelesdasilva)
# 
# This code is part of the Kernel-Ícaro project.
# Licensed under the GPL v3 License.
# 
# Copying, modification, or redistribution is prohibited without
# maintaining this copyright and authorship notice.


ASM    = nasm
CC     = gcc
LD     = ld -m elf_i386
CONVERT = convert

CFLAGS = -m32 -ffreestanding -nostdlib -fno-pic

boot.o: boot/boot.asm
	$(ASM) -f elf32 boot/boot.asm -o boot.o

kernel.o: src/kernel.c
	$(CC) $(CFLAGS) -c src/kernel.c -o kernel.o

vmicaro: boot.o kernel.o gdt.o gdt_asm.o mem.o
	$(LD) -T linker.ld boot.o kernel.o gdt.o gdt_asm.o mem.o -o vmicaro

gdt.o: system/gdt.c
	$(CC) $(CFLAGS) -c system/gdt.c -o gdt.o

gdt_asm.o: system/gdt.asm
	$(ASM) -f elf32 system/gdt.asm -o gdt_asm.o

mem.o: system/mem.c
	$(CC) $(CFLAGS) -c system/mem.c -o mem.o

all: vmicaro
	mkdir -p isodir/boot/grub
	cp vmicaro isodir/boot/vmicaro
	cp boot/grub/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o vmicaro.iso isodir/

clean:
	rm -f *.o vmicaro vmicaro.iso
	rm -rf isodir/
