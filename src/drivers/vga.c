/*
 * Kernel-Ícaro (vmicaro)
 * Copyright (c) 2026 Ícaro Teles da Silva (@icarotelesdasilva)
 * 
 * Este código é parte do projeto Kernel-Ícaro.
 * Licenciado sob a licença GPL v3.
 * 
 * É proibida a cópia, modificação ou redistribuição sem 
 * a manutenção deste aviso de copyright e autoria.
 */


char *vga  = (char*)0xB8000;
int coluna = 0;
int linha  = 0;

void vga_print(char *str) {

    int i = 0;

    while(str[i] != '\0') {

        if(str[i] == '\n') {
            coluna = 0;
            linha++;
        }
        else {
            int pos = (linha * 80 + coluna) * 2;
            vga[pos]   = str[i];
            vga[pos+1] = 0x03;
            coluna++;
        }

        if(coluna >= 80) {
            coluna = 0;
            linha++;
        }

        i++;
    }
}
