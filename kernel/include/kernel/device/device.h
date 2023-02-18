#ifndef _KERNEL_DEVICE_H
#define _KERNEL_DEVICE_H

class DeviceRequet {};
class DeviceResponse {};


class Device {
private:
    int id;
    const char* name;
public:
    Device();
    Device(int id, const char* name);
    ~Device();
    void Write(DeviceRequet* request) {}
    DeviceResponse* Read() { return nullptr; }
};


class DeviceManager
{
private:
    Device* devices[10] = {};
public:
    DeviceManager();
    ~DeviceManager();
    int AddDevice(Device* device);
    Device* GetDevice(int id);
    Device* RemoveDevice(int id);
};


DeviceManager* GetDeviceManager();

#endif /* _KERNEL_DEVICE_H */