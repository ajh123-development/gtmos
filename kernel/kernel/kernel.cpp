#include <stdio.h>

extern "C" {
#include <kernel/tty.h>
#include <kernel/serial.h>
#include <gtmos/logging.h>
#include <kernel/arch/arch.h>
#include <stdlib.h>
}

extern "C" void kernel_main(void) {
	serial_initialize(SERIAL_COM1_BASE);
	int ok = arch_init();
	if (ok == 1) {
		log_crit("CPU", "The cpu subsytem failed to load!");
		panic("The cpu subsytem failed to load!");
		return;
	}

	terminal_initialize();

	log_ok("Serial", "Welcome to GTMOS! The serial logging console has loaded!");
	printf("Hello, GTMOS World!\n");

	// *(int*)0=0; // cause a crash
	// abort(); // abort the kernel
}
