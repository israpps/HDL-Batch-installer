#include "GetPhysicalDrives.h"
#include <winioctl.h>


#if !(_WIN32_WINNT >= 0x0601)
#define BusTypeiScsi    0x9
#define BusTypeSas      0xA
#define BusTypeSata     0xB
#define BusTypeSd       0xC
#define BusTypeMmc      0xD
#endif

#if !(_WIN32_WINNT >= 0x0601)
#define BusTypeVirtual              0xE
#define BusTypeFileBackedVirtual    0xF
#endif

#ifndef BusTypeNVMe
#define BusTypeNVMe 17
#endif
#ifndef BusTypeSCM
#define BusTypeSCM 18
#endif
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
std::string GetBusTypeString(STORAGE_BUS_TYPE busType) {
    switch (busType) {
        case BusTypeScsi: return "SCSI";
        case BusTypeAtapi: return "ATAPI";
        case BusTypeAta: return "ATA";
        case BusType1394: return "FireWire";
        case BusTypeSsa: return "SSA";
        case BusTypeFibre: return "Fibre Channel";
        case BusTypeUsb: return "USB";
        case BusTypeRAID: return "RAID";
        case BusTypeiScsi: return "iSCSI";
        case BusTypeSas: return "SAS";
        case BusTypeSata: return "SATA";
        case BusTypeSd: return "SD";
        case BusTypeMmc: return "MMC";
        case BusTypeVirtual: return "Virtual";
        case BusTypeNVMe: return "NVMe";
        case BusTypeSCM: return "SCM";
        case BusTypeUnknown:
        default: return "Unknown";
    }
}
#pragma GCC diagnostic pop


std::vector<DiskInfo> GetPhysicalDrives() {
    std::vector<DiskInfo> drives;

    for (int i = 0; i < 25; i++) { // Máximo 10 discos físicos
        std::string devicePath = "\\\\.\\PhysicalDrive" + std::to_string(i);
        HANDLE hDevice = CreateFileA(devicePath.c_str(), 0, FILE_SHARE_READ | FILE_SHARE_WRITE,
                                     NULL, OPEN_EXISTING, 0, NULL);

        if (hDevice == INVALID_HANDLE_VALUE) {
            continue; // NotExist
        }

        char buffer[512] = {0};
        STORAGE_PROPERTY_QUERY query = {StorageDeviceProperty, PropertyStandardQuery};
        DWORD bytesReturned = 0;

        if (DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY, &query, sizeof(query),
                            buffer, sizeof(buffer), &bytesReturned, NULL)) {
            STORAGE_DEVICE_DESCRIPTOR *desc = (STORAGE_DEVICE_DESCRIPTOR *)buffer;
            std::string siz(std::to_string(desc->Size));
            std::string caption = "Unknown";
            std::string bus = GetBusTypeString(desc->BusType);
            if (desc->ProductIdOffset) {
                caption = (buffer + desc->ProductIdOffset);
            }
            drives.push_back({devicePath, caption, bus});
        }

        CloseHandle(hDevice);
    }

    return drives;
}
