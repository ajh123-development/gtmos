#include "isr.h"
#include "irq.h"
#include "pic.h"
#include "i8259_pic.h"
#include <gtmos/kernel/arch/io.h>
#include <gtmos/kernel/arch/arch.h>
#include <stddef.h>
#include <stdio.h>
#include <gtmos/logging.h>
#include <gtmos/utils/arrays.h>

#define MODULE                  "x86_64/IRQ"

IRQHandler g_IRQHandlers[16];
static const PICDriver* g_Driver = NULL;

void IRQ_Handler(Registers* regs) {
    int irq = regs->int_num - PIC_REMAP_OFFSET;
    log_debug(MODULE, "Enter IRQ Handler2");
    
    if (g_IRQHandlers[irq] != NULL)
    {
        // handle IRQ
        g_IRQHandlers[irq](regs);
    }
    else
    {
        log_warn(MODULE, "Unhandled IRQ %d...", irq);
    }

    // send EOI
    g_Driver->SendEndOfInterrupt(irq);
}

void IRQ_Initialize() {
    const PICDriver* drivers[] = {
        i8259_GetDriver(),
    };

    for (unsigned int i = 0; i < SIZE(drivers); i++) {
        if (drivers[i]->Probe()) {
            g_Driver = drivers[i];
        }
    }

    if (g_Driver == NULL) {
        log_warn(MODULE, "No PIC found!");
        return;
    }

    log_debug(MODULE, "Found `%s` PIC.", g_Driver->Name);
    g_Driver->Initialize(PIC_REMAP_OFFSET, PIC_REMAP_OFFSET + 8, false);

    // register ISR handlers for each of the 16 irq lines
    for (int i = 0; i < 16; i++) {
        ISR_RegisterHandler(PIC_REMAP_OFFSET + i, IRQ_Handler);
    }

    // enable interrupts
    EnableInterrupts();

    // g_Driver->Unmask(0);
    // g_Driver->Unmask(1);
}

void IRQ_RegisterHandler(int irq, IRQHandler handler) {
    g_IRQHandlers[irq] = handler;
    log_debug(MODULE, "Registered IRQ Handler %d", irq);
}