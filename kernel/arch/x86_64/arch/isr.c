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

#define MODULE          "x86_64/ISR"

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

void ISR_Initialize() {
    ISR_InitializeGates();
    for (int i = 0; i < 256; i++)
        IDT_EnableGate(i);

    IDT_DisableGate(0x80);
    log_debug(MODULE, "Gates have been initialized");
}

void ISR_Handler(Registers* regs) {
    log_debug(MODULE, "Enter ISR Handler");
    if (g_ISRHandlers[regs->int_num] != NULL)
        g_ISRHandlers[regs->int_num](regs);
    else if (regs->int_num >= 32)
        log_err(MODULE, "Unhandled interrupt %s!", regs->int_num);
    else 
    {
        const char *my_string = "  Unhandled exception %d (%s)\n"
                                "Technical information:"
                                "  r15=%x  r14=%x  r13=%x     r12=%x  r11=%x  r10=%x r9=%x r8=%x\n"
                                "  rdi=%x  rsi=%x  rbp=%x     rbx=%x  rdx=%x  rcx=%x rax=%x\n"
                                "  rip=%x  cs=%x   rflags=%x  rsp=%x  ss=%x\n"
                                "  int_num=%x  error_code=%x\n";

        panic(
            my_string, 
            regs->int_num, g_Exceptions[regs->int_num],
            regs->r15, regs->r14, regs->r13, regs->r12, regs->r11, regs->r10, regs->r9, regs->r8,
            regs->rdi, regs->rsi, regs->rbp, regs->rbx, regs->rdx, regs->rcx, regs->rax,
            regs->rip, regs->cs, regs->rflags, regs->rsp, regs->ss,
            regs->int_num, regs->error_code
        );
    }
}

void ISR_RegisterHandler(int interrupt, ISRHandler handler) {
    g_ISRHandlers[interrupt] = handler;
    IDT_EnableGate(interrupt);
    log_debug(MODULE, "Enabled interrupt %d", interrupt);
}