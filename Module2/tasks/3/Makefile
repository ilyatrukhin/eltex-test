CC=gcc
CFLAGS=-Wall -Werror -c
STD=c99

all: main.o vector.o
	$(CC) main.o vector.o -o main

main.o:
	$(CC) $(CFLAGS) -std=$(STD) main.c

vector.o:
	$(CC) $(CFLAGS) -std=$(STD) vector.c

clean:
	rm -f *.o main