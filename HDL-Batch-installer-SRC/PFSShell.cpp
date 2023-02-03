#include "PFSShell.h"
#include <wx/wx.h>
#include <wx/string.h>
#include <fcntl.h>
#include <cstring>
#include <errno.h>
#include <iostream>
#include "macro-vault.h"
PFSShell::PFSShell()
{
    //ctor
}

PFSShell::~PFSShell()
{
    //dtor
}

extern "C" {
extern void set_atad_device_path(const char *path);
extern void atad_close(void);
extern void init(void);
}

int PFSShell::SelectDevice(std::string device)
{
    COLOR(0d)
    std::cout << "accessing device " << device << "\n";
    set_atad_device_path(device.c_str());
    if (!libinit)
    {
        /* mandatory */
        std::cout << "Initializing APA:\n";
        int result = _init_apa(0, NULL);
        if (result < 0) {
            COLOR(0c)
            fprintf(stderr, "(!) init_apa: failed with %d (%s)\n", result,
                    std::strerror(-result));
            COLOR(07)
            return (1);
        }

        static const char *pfs_args[] =
            {
                "pfs.irx",
                "-m", "1",
                "-o", "1",
                "-n", "10",
                NULL};

        /* mandatory */
        std::cout << "Initializing PFS:\n";
        result = _init_pfs(7, (char **)pfs_args);
        if (result < 0) {
            COLOR(0c)
            fprintf(stderr, "(!) init_pfs: failed with %d (%s)\n", result,
                    strerror(-result));
            COLOR(07)
            return (1);
        }

        /* mandatory */
        std::cout << "Initializing HDLFS:\n";
        result = _init_hdlfs(0, NULL);
        if (result < 0) {
            COLOR(0c)
            fprintf(stderr, "(!) init_hdlfs: failed with %d (%s)\n", result,
                    strerror(-result));
            COLOR(07)
            return (1);
        }
        libinit = true;
    } else init();

    std::cout << "finished init\n";
    ctx.setup = 1;
    COLOR(07)
    return (0);
}

int PFSShell::CloseDevice()
{
    atad_close();
    return 0;
}

int PFSShell::FormatDevice()
{
    COLOR(0e)
    std::cout << "HDD format requested...n";
    COLOR(0d)
    int result = iomanX_format("hdd0:", NULL, NULL, 0);
    if (result >= 0) {
        std::cout << "\tFormat succeeded\n";
        result = mkpfs("__net");
        mkpfs("__system");
        mkpfs("__sysconf");
        mkpfs("__common");
    }
    if (result < 0)
    {
        COLOR(0c)
        fprintf(stderr, "(!) format error: %s (-%d).\n", strerror(-result), result);
        COLOR(07)
    }
    return (result);
}

int PFSShell::mkpfs(const char *mount_point)
{
#define PFS_ZONE_SIZE 8192
#define PFS_FRAGMENT  0x00000000
    COLOR(0d)
    int format_arg[] = {PFS_ZONE_SIZE, 0x2d66, PFS_FRAGMENT};
    int ret;
    std::cout << "creating PFS filesystem for '" << mount_point << "'\n";
    char tmp[256];
    strcpy(tmp, "hdd0:");
    strcat(tmp, mount_point);
    ret = iomanX_format("pfs:", tmp, (void *)&format_arg, sizeof(format_arg));
    COLOR(07)
    return ret;
}

int PFSShell::mkpart(const char *mount_point, long size_in_mb, int format)
{
    COLOR(0d)
    char tmp[256];
    if (size_in_mb >= 1024)
        sprintf(tmp, "%s,%ldG", mount_point, size_in_mb / 1024);
    else
        sprintf(tmp, "%s,%ldM", mount_point, size_in_mb);
    int result = iomanX_open(tmp, FIO_O_RDWR | FIO_O_CREAT, 0);
    if (result >= 0) {
        iomanX_close(result), result = 0;

        if (format)
            result = mkpfs(mount_point);
    }
    return (result);
    COLOR(07)
}

int PFSShell::ls(const char *mount_point, const char *path)
{
    COLOR(0d)
    int retval = 0;
    int result = iomanX_mount("pfs0:", mount_point, 0, NULL, 0);
    if (result >= 0) { /* mount successful */
        char dir_path[256];
        strcpy(dir_path, "pfs0:");
        strcat(dir_path, path);
        int dh = iomanX_dopen(dir_path);
        if (dh >= 0) { /* dopen successful */
#if 0
	  printf ("Directory of %s%s\n", mount_point, path);
#endif
            list_dir_objects(dh, 1);

            result = iomanX_close(dh);
            if (result < 0)
                printf("dclose: failed with %d\n", result), retval = -1;
        } else
            printf("dopen: \"%s\" failed with %d\n",
                   dir_path, dh),
                retval = -1;

        result = iomanX_umount("pfs0:");
        if (result < 0)
            printf("pfs0: umount failed with %d\n", result), retval = -1;
    } else
        printf("pfs0: mount of \"%s\" failed with %d\n",
               mount_point, result),
            retval = -1;
    return (retval);
    COLOR(07)
}

int PFSShell::copyto(const char *mount_point, const char *dest, const char *src)
{
    COLOR(0d)
    int retval = 0;
    int in_file = open(src, O_RDONLY | O_BINARY);
    if (in_file != -1) {
        int result = iomanX_mount("pfs0:", mount_point, 0, NULL, 0);
        if (result >= 0) { /* mount successful */
            char dest_path[256];
            strcpy(dest_path, "pfs0:");
            strcat(dest_path, dest);

            int fh = iomanX_open(dest_path,
                                 FIO_O_WRONLY | FIO_O_CREAT, 0666);
            if (fh >= 0) {
                char buf[4096 * 16];
                int len;
                while ((len = read(in_file, buf, sizeof(buf))) > 0) {
                    result = iomanX_write(fh, buf, len);
                    if (result < 0) {
                        printf("%s: write failed with %d\n", dest_path, result);
                        retval = -1;
                        break;
                    }
                }
                if (len < 0)
                    perror(src);
                result = iomanX_close(fh);
                if (result < 0)
                    printf("close: failed with %d\n", result), retval = -1;
            } else
                printf("%s: create failed with %d\n", dest_path, fh), retval = -1;

            result = iomanX_umount("pfs0:");
            if (result < 0)
                printf("pfs0: umount failed with %d\n", result), retval = -1;
        } else
            printf("pfs0: mount of \"%s\" failed with %d\n",
                   mount_point, result),
                retval = -1;
        close(in_file);
    } else
        perror(src), retval = -1;
    COLOR(07)
    return (retval);
}

int PFSShell::recoverfile(const char *mount_point, const char *src, const char *dest)
{
    COLOR(0d)
    int retval = 0;
    int out_file = open(dest, O_CREAT | O_WRONLY | O_BINARY, 0664);
    if (out_file != -1) {
        int result = iomanX_mount("pfs0:", mount_point, 0, NULL, 0);
        if (result >= 0) { /* mount successful */
            char src_path[256];
            strcpy(src_path, "pfs0:");
            strcat(src_path, src);

            int fh = iomanX_open(src_path, FIO_O_RDONLY);
            if (fh >= 0) {
                char buf[4096 * 16];
                int len;
                while ((len = iomanX_read(fh, buf, sizeof(buf))) > 0) {
                    result = write(out_file, buf, len);
                    if (result == -1) {
                        perror(dest);
                        retval = -1;
                        break;
                    }
                }
                if (len < 0)
                    printf("%s: read failed with %d\n",
                           src_path, len),
                        retval = -1;

                result = iomanX_close(fh);
                if (result < 0)
                    printf("close: failed with %d\n", result), retval = -1;
            } else
                printf("%s: open failed with %d\n", src_path, fh), retval = -1;

            result = iomanX_umount("pfs0:");
            if (result < 0)
                printf("pfs0: umount failed with %d\n", result), retval = -1;
        } else
            printf("pfs0: mount of \"%s\" failed with %d\n",
                   mount_point, result),
                retval = -1;
        if (close(out_file) == -1)
            perror(dest), retval = -1;
    } else
        perror(dest), retval = -1;
    COLOR(07)
    return (retval);
}

int PFSShell::list_dir_objects(int dh, int lsmode)
{
    COLOR(0d)
    int result;
    iox_dirent_t dirent;
    char end_symbol[2];
    end_symbol[1] = '\0';
    while ((result = iomanX_dread(dh, &dirent)) && result != -1) {
        char mode[10 + 1] = {'\0'}; /* unix-style */
        const int m = dirent.stat.mode;
        switch (m & FIO_S_IFMT) { /* item type */
            case FIO_S_IFLNK:
                mode[0] = 'l';
                end_symbol[0] = '@';
                break;
            case FIO_S_IFREG:
                mode[0] = '-';
                end_symbol[0] = '\0';
                break;
            case FIO_S_IFDIR:
                mode[0] = 'd';
                end_symbol[0] = '/';
                break;
            default:
                mode[0] = '?';
                break;
        }
        mode[1] = m & FIO_S_IRUSR ? 'r' : '-';
        mode[2] = m & FIO_S_IWUSR ? 'w' : '-';
        mode[3] = m & FIO_S_IXUSR ? 'x' : '-';
        mode[4] = m & FIO_S_IRGRP ? 'r' : '-';
        mode[5] = m & FIO_S_IWGRP ? 'w' : '-';
        mode[6] = m & FIO_S_IXGRP ? 'x' : '-';
        mode[7] = m & FIO_S_IROTH ? 'r' : '-';
        mode[8] = m & FIO_S_IWOTH ? 'w' : '-';
        mode[9] = m & FIO_S_IXOTH ? 'x' : '-';
        mode[10] = '\0'; /* not really necessary */

        const ps2fs_datetime_t *mtime =
            (ps2fs_datetime_t *)dirent.stat.mtime;
        char mod_time[16 + 1]; /* yyyy-mm-dd hh:mi */
        sprintf(mod_time, "%04d-%02d-%02d %02d:%02d",
                mtime->year, mtime->month, mtime->day,
                mtime->hour, mtime->min);
        if (lsmode == 0)
            printf("%s%s\n",
                   dirent.name, end_symbol);
        else if (lsmode == 1)
            printf("%s %10u  %s  %s%s\n",
                   mode, dirent.stat.size, mod_time, dirent.name, end_symbol);
    }
    COLOR(07)
    return (result);
}

int PFSShell::lspart(int lsmode, std::vector <iox_dirent_t>* dirent_return)
{
    if (dirent_return != NULL)
        dirent_return->clear();
    COLOR(0d)
    const char *dir_path = "hdd0:";
    char end_symbol[2];
    end_symbol[1] = '\0';
    int retval = 0;
    int dh = iomanX_dopen(dir_path);
    if (dh >= 0) { /* dopen successful */
#if 0
        printf("Partitions of %s, dh = %d\n", dir_path, dh);
#endif
        int result;
        iox_dirent_t dirent;
        if (lsmode == 1)
            printf("Start (sector)  Code      Size         Timestamp  Name\n");
        while ((result = iomanX_dread(dh, &dirent)) && result != -1) {
            if (dirent_return != NULL)
                dirent_return->push_back(dirent);
            // Equal to, but avoids overflows of: size * 512 / 1024 / 1024;
            uint32_t size = dirent.stat.size / 2048;

            if (dirent.stat.mode == 0x0000) /* empty partition */
                end_symbol[0] = '%';
            else if (dirent.stat.attr == 1) /* sub-partition */
                end_symbol[0] = '@';
            else if (dirent.stat.mode == 0x0100)
                end_symbol[0] = '/';
            else if (dirent.stat.mode == 0x1337)
                end_symbol[0] = '*';
            else
                end_symbol[0] = '\0';

            const ps2fs_datetime_t *mtime =
                (ps2fs_datetime_t *)dirent.stat.mtime;
            char mod_time[16 + 1]; /* yyyy-mm-dd hh:mi */
            sprintf(mod_time, "%04d-%02d-%02d %02d:%02d",
                    mtime->year, mtime->month, mtime->day,
                    mtime->hour, mtime->min);
            if (lsmode == 0)
                printf("%s%s\n",
                       dirent.name, end_symbol);
            else if (lsmode == 1)
                printf("%#8x        %04X %7uMB  %s  %s%s\n",
                       dirent.stat.private_5, dirent.stat.mode, size, mod_time, dirent.name, end_symbol);
        }

        result = iomanX_close(dh);
        if (result < 0)
            {
                COLOR(0c)
                fprintf(stderr, "dclose: failed with %d\n", result), retval = -1;
            }
    } else
    {
        COLOR(0c)
        fprintf(stderr, "dopen: \"%s\" failed with %d\n",
               dir_path, dh),
                retval = dh;
    }
    COLOR(07)
    return (retval);
}

int PFSShell::RemovePartition(const char* part)
{
    std::cout << "removing "<<part << "\n";
    char tmp[256];
    strcpy(tmp, "hdd0:");
    strcat(tmp, part);
    int result = iomanX_remove(tmp);
    if (result < 0)
    {
        COLOR(0c)
        fprintf(stderr, "(!) %s: %s.\n", tmp, strerror(-result));
        COLOR(07)
    }
    return (result);
}

