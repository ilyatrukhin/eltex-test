CC=gcc
CFLAGS=-Wall -Werror -c
STD=c99

all: main.o
	$(CC) main.o -o main

main.o:
	$(CC) $(CFLAGS) -std=$(STD) main.c

clean:
	rm -f *.o main