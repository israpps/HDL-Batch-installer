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
        int mkpart(const char *mount_point, long size_in_mb, int format);
        int ls(const char *mount_point, const char *path);
        int lspart(int lsmode, std::vector <iox_dirent_t>* dirent_return);
        int copyto(const char *mount_point, const char *dest, const char *src);
        int recoverfile(const char *mount_point, const char *src, const char *dest);
        int list_dir_objects(int dh, int lsmode);

    protected:

    private:
        context_t ctx;
        bool libinit = false;
};

#endif // PFSSHELL_H
