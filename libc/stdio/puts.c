#include <stdio.h>

void fputs(const char* str, fd_t file)
{
    while(*str)
    {
        fputc(*str, file);
        str++;
    }
}

void puts(const char* str)
{
    fputs(str, VFS_FD_STDOUT);
}

void debugs(const char* str)
{
    fputs(str, VFS_FD_DEBUG);
}