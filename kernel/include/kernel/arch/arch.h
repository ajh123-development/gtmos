#ifndef _KERNEL_ARCH_H
#define _KERNEL_ARCH_H

#include <stdint.h>

int arch_init();
uint8_t EnableInterrupts();
uint8_t DisableInterrupts();

void panic(const char* fmt, ...);

#endif /* _KERNEL_ARCH_H */
