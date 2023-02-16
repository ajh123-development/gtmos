#include <gtmos/logging.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>

static const char* const g_LogSeverityColors[] =
{
    [LVL_DEBUG]        = "\033[2;37m",
    [LVL_INFO]         = "\033[37m",
    [LVL_OK]           = "\033[32m",
    [LVL_WARN]         = "\033[1;33m",
    [LVL_ERROR]        = "\033[1;31m",
    [LVL_CRITICAL]     = "\033[1;37;41m",
};

static const char* const g_ColorReset = "\033[0m";

void logf(const char* module, DebugLevel level, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    if (level < MIN_LOG_LEVEL)
        return;

    fputs(VFS_FD_DEBUG,  g_LogSeverityColors[level]);    // set color depending on level
    fprintf(VFS_FD_DEBUG, "[%s] ", module);             // write module
    fprintf(VFS_FD_DEBUG, fmt, args);                  // write text
    fputs(VFS_FD_DEBUG, g_ColorReset);                  // reset format
    // fputchar(VFS_FD_DEBUG, '\n');                          // newline

    va_end(args);  
}