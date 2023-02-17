#ifndef _KERNEL_DEVICE_H
#define _KERNEL_DEVICE_H

typedef struct Device {
    int (*someFunction)();
} Device;

#endif /* _KERNEL_DEVICE_H */