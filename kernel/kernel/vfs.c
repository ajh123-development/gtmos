#include <kernel/vfs/vfs.h>
#include <kernel/tty.h>
#include <kernel/serial.h>

int vfs_write(fd_t file, uint8_t* data, size_t size)
{
    switch (file)
    {
    case VFS_FD_STDIN:
        return 0;
    case VFS_FD_STDOUT:
    case VFS_FD_STDERR:
        for (size_t i = 0; i < size; i++)
            terminal_putchar(data[i]);
        return size;

    case VFS_FD_DEBUG:
        for (size_t i = 0; i < size; i++)
            serial_putchar(SERIAL_COM1_BASE, data[i]);
        return size;

    default:
        return -1;
    }
}