#include "isr.h"
#include "idt.h"
#include "gdt.h"
#include "vga.h"
#include "tty.h"
#include <kernel/tty.h>
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

void __attribute__((cdecl)) ISR_Handler(Registers* regs)
{
    if (g_ISRHandlers[regs->interrupt] != NULL)
        g_ISRHandlers[regs->interrupt](regs);
    else if (regs->interrupt >= 32)
        log_err(MODULE, "Unhandled interrupt %s!", regs->interrupt);
    else 
    {
        const char* header = "! GTMOS has suffered a crash !";
        int length = strlen(header);
        int x = (VGA_WIDTH / 2) - (length / 2);

        log_crit(MODULE, header);
        log_crit(MODULE, "Unhandled exception %d %s", regs->interrupt, g_Exceptions[regs->interrupt]);
        log_crit(MODULE, "  eax=%x  ebx=%x  ecx=%x  edx=%x  esi=%x  edi=%x",
               regs->eax, regs->ebx, regs->ecx, regs->edx, regs->esi, regs->edi);
        log_crit(MODULE, "  esp=%x  ebp=%x  eip=%x  eflags=%x  cs=%x  ds=%x  ss=%x",
               regs->esp, regs->ebp, regs->eip, regs->eflags, regs->cs, regs->ds, regs->ss);
        log_crit(MODULE, "  interrupt=%x  errorcode=%x", regs->interrupt, regs->error);

        terminal_setcolor(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_RED));
        terminal_clear();
        terminal_setcolor(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_DARK_GREY));
        terminal_movecursor(0x0000);
        terminal_setpos(0, x);
        printf("%s\n", header);
        terminal_setcolor(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_RED));
        printf("Unhandled exception %d %s\n", regs->interrupt, g_Exceptions[regs->interrupt]);
        printf("  eax=%x  ebx=%x  ecx=%x  edx=%x  esi=%x  edi=%x\n",
               regs->eax, regs->ebx, regs->ecx, regs->edx, regs->esi, regs->edi);
        printf("  esp=%x  ebp=%x  eip=%x  eflags=%x  cs=%x  ds=%x  ss=%x\n",
               regs->esp, regs->ebp, regs->eip, regs->eflags, regs->cs, regs->ds, regs->ss);
        printf("  interrupt=%x  errorcode=%x\n", regs->interrupt, regs->error);

        asm("hlt");
    }
}

void ISR_RegisterHandler(int interrupt, ISRHandler handler)
{
    g_ISRHandlers[interrupt] = handler;
    IDT_EnableGate(interrupt);
}