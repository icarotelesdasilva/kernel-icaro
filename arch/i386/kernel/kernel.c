/*
 * Kernel-Ícaro (vmicaro)
 * Copyright (c) 2026 Ícaro Teles da Silva (@icarotelesdasilva)
 *
 * Licensed under the MIT License.
 */
#include "../arch/i386/cpu/idt.h"
#include <stdint.h>
#include "../arch/i386/boot/multiboot.h"
void init_gdt(void);
extern void gdt_flush(uint32_t gdt_ptr_addr);
 extern void kernel_panic(char *str);
 extern void vga_print(const char* str);  










 void kmain(uint32_t magic, uint32_t mb_addr) {

if (magic != 0x2BADB002) {

kernel_panic("magic nao foi carregado pelo fato de estar errado");
return;

}

vga_print("\n[ok] multiboot detectado");
multiboot_init(mb_addr);
init_gdt();
vga_print("\n[ok] gdt iniciada");        
    idt_install();
    vga_print("\nidt iniciada.");
    vga_print("\nHello, Kernel!");

    while (1) {
asm volatile("hlt");

}
}






