struct ATRHeader {
  unsigned char wMagic[2];
  unsigned char wPars[2];
  unsigned char wSecSize[2];
  unsigned char btParsHigh;
  unsigned char dwCRC[4];
  unsigned char dwUSED[4];
  unsigned char btFlags;
};

#define ATR_NUM_SECTORS 720
#define ATR_SECTOR_SIZE 128
#define ATR_PARS_SIZE 16

struct ATRSSDISK {
  struct ATRHeader header;
  unsigned char *sector[ATR_NUM_SECTORS];
};

/* return an ATRSSDISK (ATARI Single Sided Disk) */
struct ATRSSDISK *readDisk(const char *fname);

/* free a disk structure */
void freeDisk(struct ATRSSDISK *disk);
