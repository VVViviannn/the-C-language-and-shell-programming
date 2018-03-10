#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "dos2sd.h"




static void listFiles(FILE *fd, struct ATRSSDISK *disk)
{
  int sector, entry, i, count, start, baseFileNumber;
  char name[9], ext[4];

  baseFileNumber = 0;
  for(sector=361;sector<=368;sector++) {
    for(entry=0;entry<ATR_SECTOR_SIZE;entry+=16) {
      if(disk->sector[sector-1][entry] == 0x042) {
        for(i=0;i<8;i++)
          name[i] = disk->sector[sector-1][entry+5+i];
        name[8] = '\0';
        for(i=0;i<3;i++) 
          ext[i] = disk->sector[sector-1][entry+13+i];
        ext[3] = '\0';
        count = disk->sector[sector-1][entry+1]|disk->sector[sector-1][entry+2]<<8;
        start = disk->sector[sector-1][entry+3]|disk->sector[sector-1][entry+4]<<8;
        fprintf(fd,"File entry %d %s.%s sector count %d start %d\n", baseFileNumber, name, ext, count, start);
      }
      baseFileNumber++;
    }
  }
}


int main(int argc, char *argv[])
{
  struct ATRSSDISK *disk;

  if(argc != 2) {
    fprintf(stderr,"usage: %s disk\n", argv[0]);
    exit(1);
  }
  if((disk = readDisk(argv[1])) == (struct ATRSSDISK *)NULL) {
    fprintf(stderr,"Unable to read disk %s\n", argv[1]);
    exit(1);
  }
  listFiles(stdout, disk); /* put it in atari offset notation 1..720 */
  freeDisk(disk);
  return 0;
    
}


  
  
