CC=gcc
CFLAGS=-Wall -Werror -c
STD=c99

all: main

main: main.o multipliers.o
	$(CC) main.o multipliers.o -o main -lm

main.o: main.c
	$(CC) $(CFLAGS) -std=$(STD) main.c

multipliers.o: multipliers.c
	$(CC) $(CFLAGS) -std=$(STD) multipliers.c
clean:
	rm -f *.o main
