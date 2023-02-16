#ifndef _STDIO_H
#define _STDIO_H 1

#include <sys/cdefs.h>
#include <gtmos/vfs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

int fprintf(fd_t file, const char* __restrict, ...);
int fputchar(fd_t file, int);
int fputs(fd_t file, const char*);

int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);

int debug_printf(const char* __restrict, ...);
int debug_putchar(int);
int debug_puts(const char*);

#ifdef __cplusplus
}
#endif

#endif
