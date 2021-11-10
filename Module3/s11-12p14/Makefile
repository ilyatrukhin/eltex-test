CC=gcc
CFLAGS=-Wall -Werror -c
STD=c99

all: readmapped createmapped

readmapped: readmapped.o
	$(CC) readmapped.o -o readmapped

createmapped: createmapped.o
	$(CC) createmapped.o -o createmapped

readmapped.o: readmapped.c
	$(CC) $(CFLAGS) readmapped.c

createmapped.o: createmapped.c
	$(CC) $(CFLAGS) createmapped.c

clean:
	rm -f *.o readmapped createmapped