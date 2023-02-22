#ifndef _KERNEL_VFS_H
#define _KERNEL_VFS_H

#include <stdint.h>
#include <stddef.h>
#include <gtmos/kernel/vfs/vfs_types.h>

int vfs_write(fd_t file, uint8_t* data, size_t size);


#endif /* _KERNEL_VFS_H */
