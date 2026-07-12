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

ENTRY(_start)

SECTIONS
{
    . = 0x100000;

    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }

    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }

    _fim_do_kernel = .; 
}
