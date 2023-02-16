#include <kernel/arch/arch.h>
#include <gtmos/logging.h>
#include "gdt.h"
#include "idt.h"
#include "isr.h"

int arch_init() {
    log_ok("CPU", "Loading the i386 subsytem...");
    GDT_Initialize();
    log_info("CPU/GDT", "The Global Descriptor Table has loaded corectly!");
    IDT_Initialize();
    log_info("CPU/IDT", "The Interrupt Descriptor Table has loaded corectly!");
    ISR_Initialize();
    log_info("CPU/ISR", "The Interrupt Service Routines have loaded corectly!");
    log_ok("CPU", "The i386 subsytem has loaded corectly!");
    return 0;
}