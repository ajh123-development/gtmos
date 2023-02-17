#include <kernel/arch/arch.h>
#include <gtmos/logging.h>
#include <kernel/tty.h>
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"
#include "vga.h"
#include "tty.h"

int arch_init() {
    log_ok("i386", "Loading the i386 CPU subsytem...");
    GDT_Initialize();
    log_info("i386/GDT", "The Global Descriptor Table has loaded corectly!");
    IDT_Initialize();
    log_info("i386/IDT", "The Interrupt Descriptor Table has loaded corectly!");
    ISR_Initialize();
    log_info("i386/ISR", "The Interrupt Service Routines have loaded corectly!");
    IRQ_Initialize();
    log_info("i386/IRQ", "The Interrupt Requets have loaded corectly!");
    log_ok("i386", "The i386 subsytem has loaded corectly!");
    return 0;
}

void panic(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
 
    const char* header = "! GTMOS has suffered a crash !";
    int length = strlen(header);
    int x = (VGA_WIDTH / 2) - (length / 2);

    const char *intro = "There was an error which has cause the kernel to be suspended. "
                        "The system has been put into a safe state in order to protect your computer. "
                        "It is safe to power off your computer.\n"
                        "Cause:";

    log_crit("i386", header);
    debugf("%s\n", intro);
    vfprintf(VFS_FD_DEBUG, fmt, args);
    debugf("\n");

    terminal_setcolor(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_RED));
    terminal_clear();
    terminal_setcolor(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_DARK_GREY));
    terminal_movecursor(0x0000);
    terminal_setpos(0, x);
    printf("%s\n", header);
    terminal_setcolor(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_RED));
    printf("%s\n", intro);
    vfprintf(VFS_FD_STDOUT, fmt, args);

    va_end(args);
    asm("hlt");
}