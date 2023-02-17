#ifndef _KERNEL_ARCH_H
#define _KERNEL_ARCH_H

int arch_init();

void panic(const char* fmt, ...);

#endif /* _KERNEL_ARCH_H */
