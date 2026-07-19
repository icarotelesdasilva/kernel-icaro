#include "idt.h"

struct idt_entry idt[256];
struct idt_ptr idtp;

extern void idt_load();

void definir_porta_idt(uint8_t numero, uint32_t endereco_funcao, uint16_t seletor, uint8_t flags) {
    idt[numero].endereco_parte_baixa = (endereco_funcao & 0xFFFF);
    idt[numero].endereco_parte_alta = (endereco_funcao >> 16) & 0xFFFF;
    idt[numero].seletor_gdt = seletor;
    idt[numero].sempre_zero = 0;
    idt[numero].configuracoes = flags;
}

int inicializar_idt() {
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (uint32_t)&idt;

    if (idtp.base == 0) {
        return 1; 
    }

    for (int i = 0; i < 256; i++) {
        definir_porta_idt(i, 0, 0, 0);
    }

    idt_load();

    return 0;
}
