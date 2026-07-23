#include "interrupt.h"

void isr_handler(registers_t regs) {
switch (regs.int_no) {

case 0:
break;
default:
break;
}
for (;;) {

__asm__  __volatile__("hlt");

}
}
