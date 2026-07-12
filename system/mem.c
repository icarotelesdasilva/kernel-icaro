#include <stdint.h>
typedef enum {
    ZONA_RESERVADA = 0, 
    ZONA_KERNEL = 1,    
    ZONA_LIVRE = 2      
} TipoZona;

typedef struct {
    uint32_t endereco_inicial; 
    uint32_t endereco_final;   
    TipoZona tipo;             
} ZonaMemoria;

ZonaMemoria filtro_memoria[5];

extern uint32_t _fim_do_kernel;

void inicializar_filtro() {
    
    filtro_memoria[0].endereco_inicial = 0x00000000; 
    filtro_memoria[0].endereco_final   = 0x000FFFFF; 
    filtro_memoria[0].tipo             = ZONA_RESERVADA;

    filtro_memoria[1].endereco_inicial = 0x00100000;     
    filtro_memoria[1].endereco_final   = (uint32_t)&_fim_do_kernel; 
    
    filtro_memoria[1].tipo             = ZONA_KERNEL;   
}

TipoZona verificar_endereco(uint32_t endereco_para_testar) {
    
    for (int i = 0; i < 2; i++) {
        
        if (endereco_para_testar >= filtro_memoria[i].endereco_inicial && 
            endereco_para_testar <= filtro_memoria[i].endereco_final) {
return filtro_memoria[i].tipo;
            
        }
    }
    
    return ZONA_RESERVADA; 
}
