#ifndef PFSSHELL_H
#define PFSSHELL_H

#include <string>
#include <vector>

extern "C" {
#include "iomanX_port.h"
#include "hdlfs.h"
}

typedef struct
{
    int setup;
    char mount_point[256];
    int mount;
    char path[256]; /* "/" when root; not `/'-terminated */
} context_t;


class PFSShell
{
    public:
        PFSShell();
        virtual ~PFSShell();
        int SelectDevice(std::string device);
        int CloseDevice(void);
        int FormatDevice();
        int mkpfs(const char *mount_point);
        int mkpart(const char *mount_point, unsigned long size_in_mb, const char* part_typee);
        int pfs_mkdir(const char* partition, const char* path, const char* newdir);
        int pfs_rmdir(const char* partition, const char* path, const char* target);
        int pfs_rm(const char* partition, const char* path, const char* target);
        int pfs_rename(const char* partition, const char* path, const char* target, const char* newname);
        int ls(const char *mount_point, const char *path, std::vector <iox_dirent_t>* dirent_return);
        int lspart(int lsmode, std::vector <iox_dirent_t>* dirent_return);
        int copyto(const char *mount_point, const char *dest, const char *src);
        int recoverfile(const char *mount_point, const char *src, const char *dest);
        int RemovePartition(const char* part);
        int UMount(void);
        int Mount(const char* mnt);
        context_t ctx;

    protected:

    private:
        int list_dir_objects(int dh, int lsmode, std::vector <iox_dirent_t>* dirent_return);
        bool libinit = false;
        bool has_device_opened = false;
};

#endif // PFSSHELL_H
