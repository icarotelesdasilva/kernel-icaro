; interrupts.asm
[bits 32]

global isr0
extern isr_handler

section .text

%macro ISR_NOERRCODE 1
  global isr%1
  isr%1:
    cli          
    push dword 0 
    push dword %1
    jmp isr_common_stub
%endmacro

ISR_NOERRCODE 0

isr_common_stub:
    pusha        

    mov ax, ds          
    push eax

    mov ax, 0x10        
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler    

    pop eax             
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa                
    add esp, 8          
    sti  
iret
