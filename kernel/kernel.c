/*
 * Kernel-Ícaro (vmicaro)
 * Copyright (c) 2026 Ícaro Teles da Silva (@icarotelesdasilva)
 *
 * Licensed under the MIT License.
 */


 #include "gdt.h"   
 #include "idt.h"
 extern void pic_init(void);   
 extern void pmm_init(void);
 extern void* pmm_alloc_page(void);
 extern void kernel_panic(char *str);
 extern void vga_print(const char* str);  
 void kmain(uint32_t magic, uint32_t mb_addr) {
    (void) mb_addr;

    if (magic != 0x2BADB002) {

    kernel_panic("kernel panic magic is wrong!");


    return;
    } 

 vga_print("carregado 0x2BADB002! ");

    if (gdt_init() != 0) {
        kernel_panic("Kernel Panic!\nUnable to load GDT.");
        while(1);
    }

    if (inicializar_idt() != 0) {
        kernel_panic("Kernel Panic!\nUnable to load IDT.");
        while(1);
    }
pmm_init();
void* pagina_teste = pmm_alloc_page();
pic_init();
    vga_print("\nHello, Kernel!");
asm volatile("sti");

    while (1);
}
