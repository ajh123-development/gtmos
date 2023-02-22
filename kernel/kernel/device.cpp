#include <gtmos/kernel/device/device.h>
#include <gtmos/logging.h>

DeviceManager::DeviceManager() {
    log_debug("DeviceManager", "Device Manager initialised.");
}

int DeviceManager::AddDevice(Device* device) {
    int length = (sizeof(this->devices)/sizeof(*this->devices));
    if (length == 10) { return -1; }
    this->devices[length-1] = device;
    return length -1;
}

Device* DeviceManager::RemoveDevice(int index) {
    Device* device = this->devices[index];
    delete this->devices[index];
    return device;
}

Device* DeviceManager::GetDevice(int index) {
    return this->devices[index];
}