#include <kernel/arch/arch.h>
#include <gtmos/logging.h>
#include "gtd.h"

int arch_init() {
    loadGDT();
    log_ok("CPU", "The i386 subsytem has loaded corectly!");
    return 0;
}