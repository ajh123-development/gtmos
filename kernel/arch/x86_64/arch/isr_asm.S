[bits 64]

extern ISR_Handler

%macro ISR_NOERRORCODE 1
global ISR%1
ISR%1:
    push 0              ; push dummy error code
    push %1             ; push interrupt number
    jmp isr_common
%endmacro

%macro ISR_ERRORCODE 1
global ISR%1
ISR%1:
                        ; cpu pushes an error code to the stack
    push %1             ; push interrupt number
    jmp isr_common
%endmacro

%include "arch/x86_64/arch/isrs_gen.inc"

isr_common:
    push rax            ; save caller-saved registers
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    ; xor eax, eax        ; push ds
    ; mov ax, ds
    ; push rax

    mov ax, 0x10        ; use kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push rsp            ; pass pointer to stack to C, so we can access all the pushed information
    call ISR_Handler
    add rsp, 8

    pop rax             ; restore old segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    pop r15             ; restore callee-saved registers
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax

    add rsp, 8          ; remove error code and interrupt number
    iretq               ; will pop: cs, rip, rflags, ss, rsp
