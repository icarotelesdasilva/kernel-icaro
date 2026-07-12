# Kernel-Ícaro (vmicaro)
# Copyright (c) 2026 Ícaro Teles da Silva (@icarotelesdasilva)
#
# Este arquivo é parte do projeto Kernel-Ícaro.
# Licenciado sob a licença GPL v3.

ASM    = nasm
CC     = gcc
LD     = ld -m elf_i386
CONVERT = convert

CFLAGS = -m32 -ffreestanding -nostdlib -fno-pic

boot.o: boot/boot.asm
	$(ASM) -f elf32 boot/boot.asm -o boot.o

icaro.o: src/icaro.c
	$(CC) $(CFLAGS) -c src/icaro.c -o icaro.o

vmicaro: boot.o icaro.o gdt.o gdt_asm.o mem.o
	$(LD) -T linker.ld boot.o icaro.o gdt.o gdt_asm.o mem.o -o vmicaro

gdt.o: system/gdt.c
	$(CC) $(CFLAGS) -c system/gdt.c -o gdt.o

gdt_asm.o: system/gdt.asm
	$(ASM) -f elf32 system/gdt.asm -o gdt_asm.o

mem.o: system/mem.c
	$(CC) $(CFLAGS) -c system/mem.c -o mem.o

isodir/boot/grub/background.png: boot/grub/background.png
	mkdir -p isodir/boot/grub
	$(CONVERT) boot/grub/background.png -interlace none -depth 8 -resize 1024x768! isodir/boot/grub/background.png

all: vmicaro isodir/boot/grub/background.png
	mkdir -p isodir/boot/grub
	cp vmicaro isodir/boot/vmicaro
	cp boot/grub/grub.cfg isodir/boot/grub/grub.cfg
	cp -r boot/grub/themes isodir/boot/grub/
	grub-mkrescue -o icaro.iso isodir/
clean:
	rm -f *.o vmicaro icaro.iso
	rm -rf isodir/
