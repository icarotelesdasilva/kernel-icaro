/*
 * Kernel-Ícaro (vmicaro)
 * Copyright (c) 2026 Ícaro Teles da Silva (@icarotelesdasilva)
 */

extern char *vga;
extern int coluna;
extern int linha;

void kernel_panic(char *str) {
    int i = 0;

    coluna = 0;
    linha++; 

    while(str[i] != '\0') {
        if(str[i] == '\n') {
            coluna = 0;
            linha++;
        }
        else {
            int pos = (linha * 80 + coluna) * 2;
            vga[pos]   = str[i];
            vga[pos+1] = 0x4F; 
            coluna++;
        }

        if(coluna >= 80) {
            coluna = 0;
            linha++;
        }
        i++;
    }

    while(1) {
        __asm__("hlt"); 
    }
}
