CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
INCL = dos2sd.h

all:	dumpSector listFiles fileInfo extractFile

extractFile:	dos2sd.o extractFile.o
	$(CC)  -o $@ $^

fileInfo:	dos2sd.o fileInfo.o
	$(CC)  -o $@ $^

dumpSector:	dos2sd.o dumpSector.o
	$(CC)  -o $@ $^

listFiles:	dos2sd.o listFiles.o
	$(CC)  -o $@ $^

%.o:	 %.c $(INCL)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(OBJS) dumpSector
