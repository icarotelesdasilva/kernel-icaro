/*
 * Kernel-Ícaro (vmicaro)
 * Copyright (c) 2026 Ícaro Teles da Silva (@icarotelesdasilva)
 * 
 */


#include <stdint.h>
#include <stddef.h>

#define PAGE_SIZE 4096
#define BITMAP_SIZE 1024

#include <stdint.h>
#include <stddef.h>

#define PAGE_SIZE 4096
#define BITMAP_SIZE 1024

uint32_t pmm_bitmap[BITMAP_SIZE];

void pmm_marcar_ocupado(uint32_t pagina_id);
void pmm_marcar_livre(uint32_t pagina_id);
int pmm_testar_pagina(uint32_t pagina_id);
void* pmm_alocar_pagina(void);
void pmm_init(void);


void pmm_init(void) {
    for (int i = 0; i < BITMAP_SIZE; i++) {
        pmm_bitmap[i] = 0;
    }
    pmm_marcar_ocupado(0); 
}

void pmm_marcar_ocupado(uint32_t pagina_id) {
    uint32_t folha = pagina_id / 32;
    uint32_t bit = pagina_id % 32;
    pmm_bitmap[folha] |= (1 << bit);
}

void pmm_marcar_livre(uint32_t pagina_id) {
    uint32_t folha = pagina_id / 32;
    uint32_t bit = pagina_id % 32;
    pmm_bitmap[folha] &= ~(1 << bit);
}

int pmm_testar_pagina(uint32_t pagina_id) {
    uint32_t folha = pagina_id / 32;
    uint32_t bit = pagina_id % 32;
    return (pmm_bitmap[folha] & (1 << bit)) != 0;
}

void* pmm_alocar_pagina(void) {
    for (uint32_t pagina_id = 0; pagina_id < (BITMAP_SIZE * 32); pagina_id++) {
        if (pmm_testar_pagina(pagina_id) == 0) {
            pmm_marcar_ocupado(pagina_id);
            return (void*)(pagina_id * PAGE_SIZE);
        }
    }
    return NULL;
}
