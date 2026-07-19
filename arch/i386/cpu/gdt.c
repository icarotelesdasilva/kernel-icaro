/*
 * Kernel-Ícaro (vmicaro)
 * Copyright (c) 2026 Ícaro Teles da Silva (@icarotelesdasilva)
 */


int  gdt_flush(unsigned int);

struct gdt_entry {
    unsigned short limite_baixo;
    unsigned short base_baixa;
    unsigned char  base_media;
    unsigned char  acesso;
    unsigned char  granularidade;
    unsigned char  base_alta;
};

struct gdtr {
    unsigned short tamanho;
    unsigned int   base;
} __attribute__((packed));

struct gdt_entry gdt[3];
struct gdtr gdtr;

int  gdt_init()
{
    gdt[0].limite_baixo  = 0x0000;
    gdt[0].base_baixa    = 0x0000;
    gdt[0].base_media    = 0x00;
    gdt[0].acesso        = 0x00;
    gdt[0].granularidade = 0x00;
    gdt[0].base_alta     = 0x00;

    gdt[1].limite_baixo  = 0xFFFF;
    gdt[1].base_baixa    = 0x0000;
    gdt[1].base_media    = 0x00;
    gdt[1].acesso        = 0x9A;
    gdt[1].granularidade = 0xCF;
    gdt[1].base_alta     = 0x00;

    gdt[2].limite_baixo  = 0xFFFF;
    gdt[2].base_baixa    = 0x0000;
    gdt[2].base_media    = 0x00;
    gdt[2].acesso        = 0x92;
    gdt[2].granularidade = 0xCF;
    gdt[2].base_alta     = 0x00;

    gdtr.tamanho = (sizeof(struct gdt_entry) * 3) - 1;
    gdtr.base    = (unsigned int)&gdt;

    gdt_flush((unsigned int)&gdtr);

return 0;
}
