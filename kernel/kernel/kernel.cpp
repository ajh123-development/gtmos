#include <stdio.h>

#include <gtmos/kernel/device/tty.h>
#include <gtmos/kernel/device/serial.h>
#include <gtmos/logging.h>
#include <gtmos/kernel/arch/arch.h>
#include <gtmos/kernel/gui/objects.h>
#include <stdlib.h>
// #include <kernel/device/device.h>

// DeviceManager* deviceManager = new DeviceManager();

static void done(void) {
    for (;;) {
        asm("hlt");
    }
}

extern "C" void kernel_main(void) {
	DisableInterrupts();
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

	Window window2 = WindowCreate(460, 60, 200, 200, "Hello 2!");
	window2.active = 0;
	WindowDraw(window2);
	Window window = WindowCreate(100, 100, 300, 500, "Hello!");
	WindowDraw(window);

	done();
}

// DeviceManager* GetDeviceManager() {
// 	return deviceManager;
// }