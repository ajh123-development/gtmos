#include <stdio.h>

int puts(const char* string) {
	return printf("%s\n", string);
}

int debug_puts(const char* string) {
	return debug_printf("%s\n", string);
}

int fputs(fd_t file, const char* string) {
	return fprintf(file, "%s\n", string);
}
