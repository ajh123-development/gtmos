# void __attribute__((cdecl)) GDT_Load(GDTDescriptor* descriptor, uint16_t 
.global GDT_Load
GDT_Load:
    # make new call frame
    pushl %ebp           # save old call frame
    movl %esp,%ebp       # initialize new call frame

    # load gdt
    movl 8(%ebp),%eax
    lgdt (%eax)

    # reload code segment
    movl 12(%ebp),%eax
    pushl %eax
    call reload_cs
    lret

reload_cs:
    # reload data segments
    movw 16(%ebp),%ax
    movw %ax,%ds
    movw %ax,%es
    movw %ax,%fs
    movw %ax, %gs
    movw %ax,%ss

    # restore old call frame
    movl %ebp,%esp
    popl %ebp
    ret