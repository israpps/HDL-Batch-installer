#ifndef GETPHYSICALDRIVES_H
#define GETPHYSICALDRIVES_H
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

struct DiskInfo {
    std::string deviceID;
    std::string caption;
    std::string bustype;
};
std::vector<DiskInfo> GetPhysicalDrives();

#endif // GETPHYSICALDRIVES_H
