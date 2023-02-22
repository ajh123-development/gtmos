#include "isr.h"
#include "idt.h"
#include "gdt.h"
#include "../io/vga.h"
#include <gtmos/kernel/device/tty.h>
#include <gtmos/kernel/arch/arch.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <gtmos/logging.h>

#define MODULE          "ISR"

ISRHandler g_ISRHandlers[256];

static const char* const g_Exceptions[] = {
    "Divide by zero error",
    "Debug",
    "Non-maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "",
    "x87 Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception ",
    "",
    "",
    "",
    "",
    "",
    "",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    ""
};

void ISR_InitializeGates();

void ISR_Initialize()
{
    ISR_InitializeGates();
    for (int i = 0; i < 256; i++)
        IDT_EnableGate(i);

    IDT_DisableGate(0x80);
}

void ISR_Handler(Registers* regs)
{
    if (g_ISRHandlers[regs->interrupt] != NULL)
        g_ISRHandlers[regs->interrupt](regs);
    else if (regs->interrupt >= 32)
        log_err(MODULE, "Unhandled interrupt %s!", regs->interrupt);
    else 
    {
        const char *my_string = "  Unhandled exception %d (%s)\n"
                                "Technical information:"
                                "  eax=%x  ebx=%x  ecx=%x  edx=%x  esi=%x  edi=%x\n"
                                "  esp=%x  ebp=%x  eip=%x  eflags=%x  cs=%x  ds=%x  ss=%x\n"
                                "  interrupt=%x  errorcode=%x\n";

        panic(
            my_string, 
            regs->interrupt, g_Exceptions[regs->interrupt],
            regs->eax, regs->ebx, regs->ecx, regs->edx, regs->esi, regs->edi,
            regs->esp, regs->ebp, regs->eip, regs->eflags, regs->cs, regs->ds, regs->ss,
            regs->interrupt, regs->error
        );
    }
}

void ISR_RegisterHandler(int interrupt, ISRHandler handler)
{
    g_ISRHandlers[interrupt] = handler;
    IDT_EnableGate(interrupt);
}