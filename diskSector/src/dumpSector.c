#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dos2sd.h"

static void dumpSector(FILE *fd, struct ATRSSDISK *disk, int id)
{
  int i, j;
  for(j=0;j<ATR_SECTOR_SIZE;j+=32) {
    for(i=0;i<32;i++) {
       fprintf(fd,"%3d ", i+j);
    }
    fprintf(fd,"\n");
    for(i=0;i<32;i++) {
       fprintf(fd," %02x ", disk->sector[id][i+j]);
    }
    fprintf(fd,"\n");
    for(i=0;i<32;i++) {
      if(isprint(disk->sector[id][i+j]))
        fprintf(fd,"  %c ", disk->sector[id][i+j]);
      else
        fprintf(fd,"  ? ");
    }
    fprintf(fd,"\n");
  }
}


int main(int argc, char *argv[])
{
  struct ATRSSDISK *disk;

  if(argc != 3) {
    fprintf(stderr,"usage: %s disk sector\n", argv[0]);
    exit(1);
  }
  if((disk = readDisk(argv[1])) == (struct ATRSSDISK *)NULL) {
    fprintf(stderr,"Unable to read disk %s\n", argv[1]);
    exit(1);
  }
  dumpSector(stdout, disk, atoi(argv[2]) - 1); /* put it in atari offset notation 1..720 */
  freeDisk(disk);
  return 0;
    
}


  
  
