#include <stdio.h>
#include <stdlib.h>
#include "dos2sd.h"


struct ATRSSDISK *readDisk(const char *fname) 
{
  FILE *fd;
  struct ATRSSDISK *disk;
  unsigned int diskSize, sectorSize;
  int i, j;

  if((fd = fopen(fname, "r")) == (FILE *) NULL) {
    fprintf(stderr,"readDisk: Unable to open %s for reading\n", fname);
    return (struct ATRSSDISK *)NULL;
  }

  if((disk = (struct ATRSSDISK *) malloc(sizeof(struct ATRSSDISK))) == (struct ATRSSDISK *)NULL) {
    fprintf(stderr,"readDisk: Malloc fails for Header\n");
    return (struct ATRSSDISK *)NULL;
  }
  if(fread(&(disk->header), sizeof(struct ATRHeader), 1, fd) != 1) {
    fprintf(stderr,"readDisk: Header read fails\n");
    return (struct ATRSSDISK *)NULL;
  }
  if((disk->header.wMagic[0] != 0x96)||(disk->header.wMagic[1] != 0x02)) {
    fprintf(stderr,"readDisk: invalid header 0x%2x%2x\n", disk->header.wMagic[1], disk->header.wMagic[0]);
    (void) free(disk);
    return (struct ATRSSDISK *)NULL;
  }
  sectorSize = disk->header.wSecSize[1]<<8|disk->header.wSecSize[0];
  if(sectorSize != ATR_SECTOR_SIZE) {
    fprintf(stderr,"readDisk: Invalid sector size (%d)\n", sectorSize);
    (void) free(disk);
    return (struct ATRSSDISK *)NULL;
  }
  diskSize = ATR_PARS_SIZE * (disk->header.wPars[1]<<8|disk->header.wPars[0]);
  if(diskSize != (ATR_SECTOR_SIZE * ATR_NUM_SECTORS)) {
    fprintf(stderr,"readDisk: Invalid disk size (%d)\n", diskSize);
    (void) free(disk);
    return (struct ATRSSDISK *)NULL;
  }
  for(i=0;i<ATR_NUM_SECTORS;i++) {
    if((disk->sector[i] = (unsigned char *) malloc(ATR_SECTOR_SIZE)) == (unsigned char *) NULL) {
      fprintf(stderr,"readDisk: malloc fails for sector %d\n", i);
      for(j=0;j<i;j++) 
        (void) free(disk->sector[j]);
      (void) free(disk);
      return (struct ATRSSDISK *)NULL;
    }
  }
  for(i=0;i<ATR_NUM_SECTORS;i++) {
    if(fread(disk->sector[i], ATR_SECTOR_SIZE, 1, fd) != 1) {
      fprintf(stderr,"readDisk: read fails for sector %d\n", i);
      freeDisk(disk);
      return (struct ATRSSDISK *)NULL;
    }
  }
  return disk;
}

void freeDisk(struct ATRSSDISK *disk) 
{
  int i;
  for(i=0;i<ATR_NUM_SECTORS;i++) 
    (void) free(disk->sector[i]);
  (void) free(disk);
}
