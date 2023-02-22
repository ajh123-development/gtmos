#include <stdio.h>

#if defined(__is_libk)
#include <gtmos/kernel/device/tty.h>
#include <gtmos/kernel/device/serial.h>
#endif

void putc(char c) {
    fputc(c, VFS_FD_STDOUT);
}

void debugc(char c) {
    fputc(c, VFS_FD_DEBUG);
}

void fputc(char c, fd_t file) {
#if defined(__is_libk)
	if (file == VFS_FD_STDOUT || file == VFS_FD_STDERR) {
		Term_Write(&c, sizeof(c));
	}
	if (file == VFS_FD_DEBUG) {
		serial_write(SERIAL_COM1_BASE, &c, sizeof(c));
	}
#else
	// TODO: Implement stdio and the write system call.
#endif
}