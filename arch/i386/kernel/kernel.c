#include "../arch/i386/boot/multiboot.h"

void init_gdt(void);
extern void kernel_panic(char *str);
extern void vga_print(const char* str);
extern void idt_install(void);


















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
    vga_print("\n[ok] idt iniciada.");
    vga_print("\n Hello, Kernel!");
    while (1) {
        asm volatile("hlt");
    }
}





