#include <kernel/arch/arch.h>
#include <gtmos/logging.h>

int arch_init() {
    log_ok("CPU", "The i386 subsytem has loaded corectly!");
    return 0;
}