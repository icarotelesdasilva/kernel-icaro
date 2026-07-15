
/*
 * Kernel-Ícaro (vmicaro)
 * Copyright (c) 2026 Ícaro Teles da Silva (@icarotelesdasilva)
 */


#include "drivers/vga.c"
#include "../GDT/gdt.h" 
#include "../memory/pmm.h"

int inicializar_filtro();
int limpar_memoria();

unsigned char bitmap[5] = {0, 0, 0, 0, 0};
void  alocar_memoria() {
for (int i =  0; i < 5;  i++) {

if (bitmap[i] == 0) {

bitmap[i] = 1;

break;

}
}
}

int  limpar_memoria() {

for (int i = 0; i < 5; i++) {
	
if (bitmap[i] == 1) {

bitmap[i] = 0;

break;

}
}
}

int criar_filtro();
int inicializar_filtro();



void kmain(void)  {

if (gdt_init() !=0) {

vga_print("Kernel Panic!");
vga_print("\nUnable to load gdt.");
while(1);

}


if (inicializar_filtro() !=0) {
vga_print("Kernel Panic!");  
vga_print("\nUnable to load inicializar_filtro."); 
while(1);
}



if (limpar_memoria() !=0) {


vga_print("Kernel Panic!");    
vga_print("\nUnable to load alocar_memoria.");
while(1);

}


    pmm_init(); 

    void* memoria = pmm_alocar_pagina(); 

    if (memoria == 0) {
        vga_print("Kernel Panic!");      
        vga_print("\nUnable to load alocar_memoria.");
        while(1);
    }


vga_print("Hello, Kernel!");




while(1) {

}

}
