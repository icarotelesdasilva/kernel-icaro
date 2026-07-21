.PHONY: all run dev clean

ASM     = nasm
CC      = gcc
LD      = ld -m elf_i386
CONVERT = convert

CFLAGS = -m32 -ffreestanding -nostdlib -fno-pic -Iinclude

OBJ = arch/i386/boot/boot.o \
      arch/i386/drivers/vga.o \
      arch/i386/drivers/kernel_panic.o \
      arch/i386/cpu/gdt.o \
      arch/i386/cpu/gdt_flush.o \
      kernel/kernel.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

arch/i386/boot/boot.o: arch/i386/boot/boot.asm
	$(ASM) -f elf32 arch/i386/boot/boot.asm -o arch/i386/boot/boot.o

arch/i386/cpu/gdt_flush.o: arch/i386/cpu/gdt_flush.s
	$(CC) -m32 -c arch/i386/cpu/gdt_flush.s -o arch/i386/cpu/gdt_flush.o

vmicaro: $(OBJ)
	$(LD) -T arch/i386/linker.ld $(OBJ) -o vmicaro

vmicaro.iso: vmicaro
	mkdir -p isodir/boot/grub
	cp vmicaro isodir/boot/vmicaro
	cp grub/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o vmicaro.iso isodir/

all: vmicaro.iso

dev: vmicaro.iso
	qemu-system-x86_64 \
		-cdrom vmicaro.iso \
		-d int,cpu_reset,guest_errors \
		-D logs_completos.txt \
		-no-reboot -no-shutdown

run: vmicaro.iso
	qemu-system-x86_64 -cdrom vmicaro.iso

clean:
	rm -f $(OBJ) vmicaro vmicaro.iso
	rm -rf isodir/
