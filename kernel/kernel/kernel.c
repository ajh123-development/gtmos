#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/serial.h>

void kernel_main(void) {
	serial_initialize(SERIAL_COM1_BASE);
	serial_writestring(SERIAL_COM1_BASE, "Welcome to GTMOS! The serial logging console has loaded!");

	terminal_initialize();
	terminal_movecursor(0x100);
	printf("Hello, GTMOS World!\n");
}
