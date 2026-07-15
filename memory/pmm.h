/*
 * Kernel-Ícaro (vmicaro)
 * Copyright (c) 2026 Ícaro Teles da Silva (@icarotelesdasilva)
 * 
 */


#ifndef PMM_H
#define PMM_H

#include <stdint.h>

void pmm_init(void);
void pmm_marcar_ocupado(uint32_t pagina_id);
void pmm_marcar_livre(uint32_t pagina_id);
int pmm_testar_pagina(uint32_t pagina_id);
void* pmm_alocar_pagina(void); 


#endif
