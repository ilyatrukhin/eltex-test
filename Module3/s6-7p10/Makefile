CC=gcc
CFLAGS=-Wall -Werror -c
STD=c99

all: prog1 prog2

prog1: prog1.o
	$(CC) prog1.o -o prog1 

prog2: prog2.o
	$(CC) prog2.o -o prog2

prog1.o: prog1.c
	$(CC) $(CFLAGS) -std=$(STD) prog1.c

prog2.o: prog2.c
	$(CC) $(CFLAGS) -std=$(STD) prog2.c

clean:
	rm -f *.o prog1 prog2