/*
 * Kernel-Ícaro (vmicaro)
 * Copyright (c) 2026 Ícaro Teles da Silva (@icarotelesdasilva)
 *
 * Licensed under the GPL v3 License.
 */

#include "gdt.h"   
#include "idt.h"   

extern void vga_print(const char* str);  

void kmain(void) {
    if (gdt_init() != 0) {
        vga_print("Kernel Panic!\nUnable to load GDT.");
        while(1);
    }

    if (inicializar_idt() != 0) {
        vga_print("Kernel Panic!\nUnable to load IDT.");
        while(1);
    }


    vga_print("Hello, Kernel!");

    while (1);
}
