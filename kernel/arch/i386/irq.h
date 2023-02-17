#ifndef ARCH_IRQ_H
#define ARCH_IRQ_H

#include "isr.h"

typedef void (*IRQHandler)(Registers* regs);

void IRQ_Initialize();
void IRQ_RegisterHandler(int irq, IRQHandler handler);

#endif /* ARCH_IRQ_H */
