#ifndef ARCH_ISR_H
#define ARCH_ISR_H

#include <stdint.h>

typedef struct {
    /* The stack grows downward, so these fields are listed in reverse order */

    /* Saved registers */
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;
    uint64_t rdi;
    uint64_t rsi;
    uint64_t rbp;
    uint64_t rbx;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t rax;

    /* Interrupt information */
    uint64_t int_num;
    uint64_t error_code;

    /* Processor state */
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
} __attribute__((packed)) Registers;

typedef void (*ISRHandler)(Registers* regs);

void ISR_Initialize();
void ISR_RegisterHandler(int interrupt, ISRHandler handler);

#endif /* ARCH_ISR_H */
