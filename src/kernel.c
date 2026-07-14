
/*
 * Kernel-Ícaro (vmicaro)
 * Copyright (c) 2026 Ícaro Teles da Silva (@icarotelesdasilva)
 * 
 * This code is part of the Kernel-Ícaro project.
 * Licensed under the GPL v3 License.
 * 
 * Copying, modification, or redistribution is prohibited without
 * maintaining this copyright and authorship notice.
 */


#include "drivers/vga.c"
#include "../system/gdt.h" 

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
vga_print("\nUnable to load limpar_memoria."); 
while(1);
}

if (limpar_memoria() !=0) {


vga_print("Kernel Panic!");    
vga_print("\nUnable to load alocar_memoria.");
while(1);
}

vga_print("Hello, Kernel!");




while(1) {

}
}

