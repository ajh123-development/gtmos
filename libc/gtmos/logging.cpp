#include <gtmos/logging.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>

static const char* const g_LogSeverityColors[6] = {
    "\033[2;37m",   // LVL_DEBUG
    "\033[37m",     // LVL_INFO
    "\033[32m",     // LVL_OK
    "\033[1;33m",   // LVL_WARN
    "\033[1;31m",   // LVL_ERROR
    "\033[1;37;41m" // LVL_CRITICAL
};

static const char* const g_ColorReset = "\033[0m";

void logf(const char* module, DebugLevel level, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    if (level < MIN_LOG_LEVEL)
        return;

    fputs(g_LogSeverityColors[level], VFS_FD_DEBUG);    // set color depending on level
    fprintf(VFS_FD_DEBUG, "[%s] ", module);             // write module
    vfprintf(VFS_FD_DEBUG, fmt, args);                  // write text
    fputs(g_ColorReset, VFS_FD_DEBUG);                  // reset format
    fputc('\n', VFS_FD_DEBUG);                          // newline

    va_end(args);  
}