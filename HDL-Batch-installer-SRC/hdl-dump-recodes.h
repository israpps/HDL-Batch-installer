

#define RET_ERR    -1 /* error */
#define RET_NO_MEM -2 /* out-of-memory */

#define RET_OK 0

#define RET_NOT_APA          101  /* not an APA device */
#define RET_NOT_HDL_PART     102  /* not a HD Loader partition */
#define RET_NOT_FOUND        103  /* partition is not found */
#define RET_BAD_FORMAT       104  /* bad device name format */
#define RET_BAD_DEVICE       105  /* unrecognized device */
#define RET_NO_SPACE         106  /* not enough free space */
#define RET_BAD_APA          107  /* something wrong with APA partition */
#define RET_DIFFERENT        108  /* files are different */
#define RET_INTERRUPTED      109  /* operation were interrupted */
#define RET_PART_EXISTS      110 /* partition with such name already exists */
#define RET_BAD_ISOFS        111 /* not an ISO file system */
#define RET_NOT_PS_CDVD      112 /* not a Playstation CD/DVD */
#define RET_BAD_SYSCNF       113 /* system.cnf is not in the expected format */
#define RET_NOT_COMPAT       114 /* iin probe returns "not compatible" */
#define RET_NOT_ALLOWED      115 /* operation is not allowed */
#define RET_BAD_COMPAT       116 /* iin probe is compatible, but the source is bad */
#define RET_SVR_ERR          117 /* server reported error */
#define RET_1ST_LONGER       118 /* compare_iin: first input is longer */
#define RET_2ND_LONGER       119 /* compare_iin: second input is longer */
#define RET_FILE_NOT_FOUND   120 /* pretty obvious */
#define RET_BROKEN_LINK      121 /* missing linked file (to an IML or CUE for example) */
#define RET_CROSS_128GB      122 /* data behind 128GB mark */
#define RET_ASPI_ERROR       123 /* ASPI error; they are far too many to list here */
#define RET_NO_DISC_DB       124 /* disc database file could not be found */
#define RET_NO_DDBENTRY      125 /* there is no entry for that game in the disc database */
#define RET_DDB_INCOMPATIBLE 126 /* game is incompatible according to disc database */
#define RET_TIMEOUT          127 /* communication timeout */
#define RET_PROTO_ERR        128 /* network communication protocol error */
#define RET_INVARIANT        129 /* invalid internal data state; probably a bug */
#define RET_SPTI_ERROR       130 /* SPTI error */
#define RET_MBR_KELF_SIZE    131 /* file size exceeds MAX_MBR_KELF_SIZE */
#define RET_INVALID_KELF     132 /* Invalid kelf header */
#define RET_MULTITRACK       133 /* Titles with audio tracks supported only if converted to one cue/bin */
