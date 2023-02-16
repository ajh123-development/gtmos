#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/serial.h>

void kernel_main(void) {
	serial_initialize(SERIAL_COM1_BASE);
	terminal_initialize();
	terminal_movecursor(0x100);

	debug_printf("Welcome to GTMOS! The serial logging console has loaded!");
	printf("Hello, GTMOS World!\n");
}
