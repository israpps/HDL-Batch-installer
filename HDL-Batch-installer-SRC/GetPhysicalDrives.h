#ifndef GETPHYSICALDRIVES_H
#define GETPHYSICALDRIVES_H
#include <windows.h>
#ifdef GetClassInfo
// <windows.h> defines GetClassInfo as a macro, which breaks wxDECLARE_*_CLASS in later wx headers
#undef GetClassInfo
#endif
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
