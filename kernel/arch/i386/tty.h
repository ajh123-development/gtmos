#ifndef ARCH_I386_TTY_H
#define ARCH_I386_TTY_H

#include <kernel/io.h>
#include <kernel/tty.h>
#include <stddef.h>

void terminal_clear();

void terminal_setcolor(uint8_t color);

void terminal_setpos(size_t y, size_t x);

void terminal_movecursor(unsigned short pos);

#endif /* _KERNEL_TTY_H */
