#include <kernel/arch/arch.h>
#include <gtmos/logging.h>
#include <kernel/tty.h>
#include <kernel/framebuffer.h>
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"
#include "vga.h"

int arch_init() {
    log_ok("x86_64", "Loading the x86_64 CPU subsytem...");
    GDT_Initialize();
    log_debug("x86_64/GDT", "The Global Descriptor Table has loaded corectly!");
    IDT_Initialize();
    log_debug("x86_64/IDT", "The Interrupt Descriptor Table has loaded corectly!");
    ISR_Initialize();
    log_debug("x86_64/ISR", "The Interrupt Service Routines have loaded corectly!");
    IRQ_Initialize();
    log_debug("x86_64/IRQ", "The Interrupt Requets have loaded corectly!");
    log_ok("x86_64", "The x86_64 subsytem has loaded corectly!");
    return 0;
}

void panic(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
 
    const char* header = "! GTMOS has suffered a crash !";
    const char *intro = "There was an error which has cause the kernel to be suspended. "
                        "The system has been put into a safe state in order to protect your computer. "
                        "It is safe to power off your computer.\n"
                        "Cause:";

    log_crit("x86_64", header);
    debugf("%s\n", intro);
    vfprintf(VFS_FD_DEBUG, fmt, args);
    debugf("\n");

    Term_Setpos(0, 0);
    Buffer_FillColor(VGA_COLOR_RED);
    Buffer_SetTextColor(VGA_COLOR_CYAN);
    printf("%s\n", header);
    Buffer_SetTextColor(VGA_COLOR_WHITE);
    printf("%s\n", intro);
    vfprintf(VFS_FD_STDOUT, fmt, args);

    va_end(args);
    asm("hlt");
}