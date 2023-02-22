#include <gtmos/kernel/arch/io.h>
#include <stdint.h>

#define UNUSED_PORT         0x80

// sends data to a IO port
void outb(uint16_t port, uint8_t value) {
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

// receives data from a IO port
uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %1, %0"
                 : "=a"(ret)
                 : "Nd"(port));

    return ret;
}

void iowait() {
    outb(UNUSED_PORT, 0);
}