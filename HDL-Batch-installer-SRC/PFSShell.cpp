#include "PFSShell.h"
#include <wx/wx.h>
#include <wx/string.h>
#include <fcntl.h>
#include <cstring>
#include <errno.h>
#include <iostream>
#include "macro-vault.h"


#define PFS_ZONE_SIZE 8192
#define PFS_FRAGMENT  0x00000000

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
    COLOR(0e)
    std::cout << " - accessing device " << device << "\n";
    COLOR(0d)
    if (has_device_opened)
        CloseDevice();
    set_atad_device_path(device.c_str());
    if (!libinit)
    {
        /* mandatory */
        COLOR(0e)
        std::cout << " - Initializing APA:\n";
        COLOR(0d)
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
        COLOR(0e)
        std::cout << " - Initializing PFS:\n";
        COLOR(0d)
        result = _init_pfs(7, (char **)pfs_args);
        if (result < 0) {
            COLOR(0c)
            fprintf(stderr, "(!) init_pfs: failed with %d (%s)\n", result,
                    strerror(-result));
            COLOR(07)
            return (1);
        }

        /* mandatory */
        COLOR(0e)
        std::cout << " - Initializing HDLFS:\n";
        COLOR(0d)
        result = _init_hdlfs(0, NULL);
        if (result < 0) {
            COLOR(0c)
            fprintf(stderr, "PFSShell: (!) init_hdlfs: failed with %d (%s)\n", result,
                    strerror(-result));
            COLOR(07)
            return (1);
        }
        std::cout << "PFSShell: finished init\n";
        libinit = true;
    } else init();
    has_device_opened = true;
    ctx.setup = 1;
    COLOR(07)
    return (0);
}

int PFSShell::CloseDevice()
{
    if (has_device_opened)
    {
        atad_close();
        has_device_opened = false;
        COLOR(0e)
        std::cout << "PFSShell: Closing device\n";
        COLOR(07)
    }
    return 0;
}

int PFSShell::FormatDevice()
{
    COLOR(0e)
    std::cout << " -- HDD format requested -- \n";
    COLOR(0d)
    int result = iomanX_format("hdd0:", NULL, NULL, 0);
    if (result >= 0) {
        std::cout << "\t- Format succeeded\n";
        result = mkpfs("__net");
        mkpfs("__system");
        mkpfs("__sysconf");
        mkpfs("__common");
    }
    if (result < 0)
    {
        COLOR(0c)
        fprintf(stderr, "PFSShell: (!) format error: %s (-%d).\n", strerror(-result), result);
        COLOR(07)
    }
    return (result);
}

int PFSShell::mkpfs(const char *mount_point)
{
    COLOR(0d)
    int format_arg[] = {PFS_ZONE_SIZE, 0x2d66, PFS_FRAGMENT};
    int ret;
    COLOR(0e)
    std::cout << "creating PFS filesystem for '" << mount_point << "'\n";
    COLOR(0d)
    char tmp[256];
    strcpy(tmp, "hdd0:");
    strcat(tmp, mount_point);
    ret = iomanX_format("pfs:", tmp, (void *)&format_arg, sizeof(format_arg));
    COLOR(07)
    return ret;
}

int PFSShell::mkpart(const char *mount_point, unsigned long size_in_mb, const char* part_typee)
{
    COLOR(0f)
    std::cout << " -- \tcreating partition ["<<mount_point<<"] of "<<size_in_mb<<"Mb in size.\n\t  filesystem ID is: '" <<part_typee<<"'\n";
    const static char *sizesString[9] = {
        "128M",
        "256M",
        "512M",
        "1G",
        "2G",
        "4G",
        "8G",
        "16G",
        "32G"
    };
    static unsigned int sizesMB[9] = {
        128,
        256,
        512,
        1024,
        2048,
        4096,
        8192,
        16384,
        32768
    };

    char tmp[128];
    char openString[32 + 5];
    char part_type[9+1];
    int i = 9;
    int result = -1;
    int partfd = 0;
    COLOR(0d)

    strncpy(part_type, part_typee, 9);
    sprintf(openString, "hdd0:%s", mount_point);
    openString[32 + 5 - 1] = '\0';
    partfd = iomanX_open(openString, FIO_O_RDONLY);
    if (partfd != -2) // partition already exists+
    {
        iomanX_close(partfd);
        COLOR(0c)
        printf("%s: partition already exists.\n", mount_point);
        COLOR(07)
        return (-1);
    }


    while (result < 0 && i > 0) { // create main partition
        i--;
        if (sizesMB[i] <= size_in_mb) {
            sprintf(tmp, "hdd0:%s,,,%s,%s", mount_point, sizesString[i], part_type);

            partfd = iomanX_open(tmp, FIO_O_RDWR | FIO_O_CREAT);
            if (partfd >= 0) {
                printf("Main partition of %s created.\n", sizesString[i]);
                size_in_mb = size_in_mb - sizesMB[i];
                result = partfd;
            }
        }
    }

    if (i < 0) { // dont create smaller then 128MB Main partition
        fprintf(stderr, "%lu: too small partition size.\n", size_in_mb);
        return (-1);
    }
    int j = i; // limit sub partition max size
    if (partfd >= 0) {
        while (size_in_mb > 0 && j >= 0) {
            if (sizesMB[j] <= size_in_mb) {
                if (iomanX_ioctl2(partfd, HIOCADDSUB, const_cast<char*>(sizesString[j]), strlen(sizesString[j]) + 1, NULL, 0) >= 0) {
                    printf("Sub partition of %s created.\n", sizesString[j]);
                    size_in_mb = size_in_mb - sizesMB[j];
                } else
                    j--;
            } else
                j--;
        }
    }

    if (result >= 0) {
        (void)iomanX_close(partfd), result = 0;
        if (result >= 0)
            if (strncmp(part_type, "PFS", 3) == 0)
                result = mkpfs(mount_point);
    }

    if (result < 0)
        fprintf(stderr, "(!) %s: %s.\n", mount_point, strerror(-result));
    return (result);
    COLOR(07)
}

int PFSShell::ls(const char *mount_point, const char *path, std::vector <iox_dirent_t>* dirent_return)
{
    if (dirent_return != NULL) dirent_return->clear();
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
            list_dir_objects(dh, 1, dirent_return);

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
                printf("%s: open failed with %d (%s)\n", src_path, fh, strerror(-fh)), retval = -1;

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

int PFSShell::list_dir_objects(int dh, int lsmode, std::vector <iox_dirent_t>* dirent_return)
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
        if (dirent_return != NULL) dirent_return->push_back(dirent);
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
            if (dirent_return != NULL) dirent_return->push_back(dirent);
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
    std::cout << "removing ["<<part << "]\n";
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

int PFSShell::pfs_mkdir(const char* partition, const char* path, const char* newdir)
{
    int result = PFSShell::Mount(partition);
    if (result < 0) {
        return result;
    }
    char tmp[256];
    strcpy(tmp, "pfs0:");
    strcat(tmp, path);
    if (tmp[strlen(tmp) - 1] != '/')
        strcat(tmp, "/");
    strcat(tmp, newdir);
    result = iomanX_mkdir(tmp, 0777);
    if (result < 0) {
        COLOR(0c)
        fprintf(stderr, "(!) '%s': %s.\n", tmp, strerror(-result));
        COLOR(07)
    }
    PFSShell::UMount();
    return (result);
}

int PFSShell::pfs_rmdir(const char* partition, const char* path, const char* target)
{
    int result = PFSShell::Mount(partition);
    if (result < 0) {
        return result;
    }
    char tmp[256];
    strcpy(tmp, "pfs0:");
    strcat(tmp, path);
    if (tmp[strlen(tmp) - 1] != '/')
        strcat(tmp, "/");
    strcat(tmp, target);
    result = iomanX_rmdir(tmp);
    if (result < 0) {
        COLOR(0c)
        fprintf(stderr, "(!) %s: %d (%s).\n", tmp, result, strerror(-result));
        COLOR(07)
    }
    PFSShell::UMount();
    return (result);
}

int PFSShell::pfs_rm(const char* partition, const char* path, const char* target)
{
    int result = PFSShell::Mount(partition);
    if (result < 0) {
        return result;
    }
    char tmp[256];
    strcpy(tmp, "pfs0:");
    strcat(tmp, path);
    if (tmp[strlen(tmp) - 1] != '/')
        strcat(tmp, "/");
    strcat(tmp, target);
    result = iomanX_remove(tmp);
    if (result < 0) {
        COLOR(0c)
        fprintf(stderr, "(!) %s: %s.\n", tmp, strerror(-result));
        COLOR(07)
    }
    PFSShell::UMount();
    return (result);
}

int PFSShell::pfs_rename(const char* partition, const char* path, const char* target, const char* newname)
{
    int result = PFSShell::Mount(partition);
    if (result < 0) {
        return result;
    }
    char tmp[256];
    strcpy(tmp, "pfs0:");
    strcat(tmp, path);
    if (tmp[strlen(tmp) - 1] != '/')
        strcat(tmp, "/");
    strcat(tmp, target);
    result = iomanX_rename(tmp, newname);
    if (result < 0)
        fprintf(stderr, "(!) %s: %s.\n", tmp, strerror(-result));
    PFSShell::UMount();
    return (result);
}

int PFSShell::Mount(const char* mnt) {
    int result = iomanX_mount("pfs0:", mnt, 0, NULL, 0);
    if (result < 0) {
        COLOR(0c)
        fprintf(stderr, "pfs0: mount of \"%s\" failed with %d\n", mnt, result),
        COLOR(07)
    }
    return (result);
}

int PFSShell::UMount(void) {
    int result = iomanX_umount("pfs0:");
    if (result < 0)
        COLOR(0c)
        fprintf(stderr, "pfs0: umount failed with %d\n", result);
        COLOR(07)
    return (result);
}
