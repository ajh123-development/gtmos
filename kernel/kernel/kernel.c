#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/serial.h>
#include <gtmos/logging.h>
#include <kernel/arch/arch.h>

void kernel_main(void) {
	serial_initialize(SERIAL_COM1_BASE);
	int ok = arch_init();
	if (ok == 1) {
		log_crit("CPU", "The cpu subsytem failed to load!");
		return;
	}

	terminal_initialize();
	terminal_movecursor(0x100);

	log_ok("Serial", "Welcome to GTMOS! The serial logging console has loaded!");
	printf("Hello, GTMOS World!\n");
}
