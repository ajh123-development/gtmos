#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/serial.h>
#include <gtmos/logging.h>
#include <kernel/arch/arch.h>
#include <stdlib.h>
// #include <kernel/device/device.h>

// DeviceManager* deviceManager = new DeviceManager();

static void done(void) {
    for (;;) {
        asm("hlt");
    }
}

extern "C" void kernel_main(void) {
	serial_initialize(SERIAL_COM1_BASE);
	int ok = arch_init();
	if (ok == 1) {
		log_crit("CPU", "The cpu subsytem failed to load!");
		panic("The cpu subsytem failed to load!");
		return;
	}

	Term_Initialize();

	log_ok("Serial", "Welcome to GTMOS! The serial logging console has loaded!");
	printf("Hello, GTMOS World!\n");

	done();
}

// DeviceManager* GetDeviceManager() {
// 	return deviceManager;
// }