#ifndef _STDIO_H
#define _STDIO_H 1

#include <sys/cdefs.h>
#include <gtmos/kernel/vfs/vfs.h>
#include <limits.h>
#include <stdarg.h>
#include <stdint.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

void fputc(char c, fd_t file);
void fputs(const char* str, fd_t file);
void vfprintf(fd_t file, const char* fmt, va_list args);
void fprintf(fd_t file, const char* fmt, ...);
void fprint_buffer(fd_t file, const char* msg, const void* buffer, uint32_t count);

void putc(char c);
void puts(const char* str);
void printf(const char* fmt, ...);
void print_buffer(const char* msg, const void* buffer, uint32_t count);

void debugc(char c);
void debugs(const char* str);
void debugf(const char* fmt, ...);
void debug_buffer(const char* msg, const void* buffer, uint32_t count);

#ifdef __cplusplus
}
#endif

#endif
