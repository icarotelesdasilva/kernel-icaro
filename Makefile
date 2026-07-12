
# Kernel-Ícaro (vmicaro)
# Copyright (c) 2026 Ícaro Teles da Silva (@icarotelesdasilva)
# 
# Este arquivo é parte do projeto Kernel-Ícaro.
# Licenciado sob a licença GPL v3.



	ASM    = nasm
CC     = gcc
LD     = ld -m elf_i386

CFLAGS = -m32 -ffreestanding -nostdlib -fno-pic

boot.o: boot/boot.asm
	$(ASM) -f elf32 boot/boot.asm -o boot.o

icaro.o: src/icaro.c
	$(CC) $(CFLAGS) -c src/icaro.c -o icaro.o

vmicaro: boot.o icaro.o gdt.o gdt_asm.o
	$(LD) -T linker.ld boot.o icaro.o gdt.o gdt_asm.o -o vmicaro

gdt.o: system/gdt.c
	$(CC) $(CFLAGS) -c system/gdt.c -o gdt.o

gdt_asm.o: system/gdt.asm
	$(ASM) -f elf32 system/gdt.asm -o gdt_asm.o

all: vmicaro
	mkdir -p isodir/boot/grub
	cp vmicaro isodir/boot/vmicaro
	cp boot/grub/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o icaro.iso isodir/

clean:
	rm -f *.o vmicaro icaro.iso
	rm -rf isodir/
