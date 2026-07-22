#include "multiboot.h"

extern void vga_print(const char *str);


void multiboot_init(uint32_t mb_addr)
{
    multiboot_info_t *mb = (multiboot_info_t *)mb_addr;


    if (mb->flags & 0x1)
    {
        vga_print("\n[ok] memoria encontrada");
    }
    else
    {
        vga_print("\n[erro] memoria nao encontrada");
    }
}
