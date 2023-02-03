#pragma once

#define __start hdlfs_start

#define HDL_FS_MAGIC 0x1337
#define APA_FLAG_SUB 0x0001
#define HDL_INFO_MAGIC 0xDEADFEED
#define HDL_GAME_DATA_OFFSET 0x100000

#define HDLFS_GAME_TITLE_LEN 160
#define HDLFS_STARTUP_PTH_LEN 60

typedef struct
{
    unsigned int part_offset; // In CD-ROM (2048-byte) sectors
    unsigned int data_start;  // In 512-byte HDD sectors
    unsigned int part_size;   // In bytes
} part_specs_t;

typedef struct // size = 1024 bytes
{
    unsigned int magic;
    unsigned short int reserved;
    unsigned short int version;
    char gamename[HDLFS_GAME_TITLE_LEN];
    unsigned char hdl_compat_flags;
    unsigned char ops2l_compat_flags;
    unsigned char dma_type;
    unsigned char dma_mode;
    char startup[HDLFS_STARTUP_PTH_LEN]; /* NOTE: The startup file name here must be without the ";1" suffix. */
    unsigned int layer1_start;
    unsigned int discType;
    int num_partitions;
    part_specs_t part_specs[65];
} hdl_game_info;

enum HDLFS_DEVCTL_codes {
    HDLFS_DEVCTL_GET_STARTUP_PATH = 0x1000,
    HDLFS_DEVCTL_GET_TITLE,
    HDLFS_DEVCTL_SET_TITLE
};

struct HDLFS_FormatArgs
{
    unsigned char CompatFlags, DiscType;
    unsigned char TRType, TRMode;
    unsigned int NumSectors, Layer1Start;
    char GameTitle[HDLFS_GAME_TITLE_LEN];    //In UTF-8
    char StartupPath[HDLFS_STARTUP_PTH_LEN]; /* NOTE: The startup file name here must be without the ";1" suffix. */
};
