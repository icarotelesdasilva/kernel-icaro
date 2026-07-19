#include <stdint.h>
#include <stddef.h>

#define TAM_PAGINA 4096
#define QUAN_PAGINA 4096

extern void kernel_panic(char *str);
static uint8_t pmm_panel[QUAN_PAGINA]; 

void* pmm_init() {
 for (uint32_t i = 0; i < QUAN_PAGINA; i++) { 
 pmm_panel[i] = 1;
}
    
 for (uint32_t i = 256; i < 1000; i++) {
 pmm_panel[i] = 0; 
 }
} 

void*  pmm_alloc_page() {
for (uint32_t i = 0; i < QUAN_PAGINA; i++) {
if (pmm_panel[i] == 0) { 
pmm_panel[i] = 1;
return (void*)(i * TAM_PAGINA);
 }
}

 kernel_panic("Kernel Panic!\nOut of memory: PMM failed to allocate page.");
 return NULL; 
}

void  pmm_free_page(void* endereco) {
uint32_t i = ((uint32_t)endereco) / TAM_PAGINA;
if (i < QUAN_PAGINA) {
pmm_panel[i] = 0;   
}
}
