#ifndef ARCH_IRQ_H
#define ARCH_IRQ_H

#include "isr.h"

#define PIC_REMAP_OFFSET        0x20

typedef void (*IRQHandler)(Registers* regs);

void IRQ_Initialize();
void IRQ_RegisterHandler(int irq, IRQHandler handler);

#endif /* ARCH_IRQ_H */
