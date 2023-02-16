#include <stdio.h>

#if defined(__is_libk)
#include <kernel/tty.h>
#include <kernel/serial.h>
#endif

int putchar(int ic) {
	return fputchar(VFS_FD_STDOUT, ic);
}

int debug_putchar(int ic) {
	return fputchar(VFS_FD_DEBUG, ic);
}

int fputchar(fd_t file, int ic) {
#if defined(__is_libk)
	if (file == VFS_FD_STDOUT || file == VFS_FD_STDERR) {
		char c = (char) ic;
		terminal_write(&c, sizeof(c));
	}
	if (file == VFS_FD_DEBUG) {
		char c = (char) ic;
		serial_write(SERIAL_COM1_BASE, &c, sizeof(c));
	}
#else
	// TODO: Implement stdio and the write system call.
#endif
	return ic;
}