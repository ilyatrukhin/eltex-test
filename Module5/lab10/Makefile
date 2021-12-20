CC=gcc
CFLAGS=-Wall -Werror -c
STD=c99

all: main

main: main.o game.o table.o player.o
	$(CC) main.o game.o table.o player.o -o main -lpthread

main.o: main.c
	$(CC) $(CFLAGS) -std=$(STD) main.c

game.o: game.c
	$(CC) $(CFLAGS) -std=$(STD) game.c

table.o: table.c table.h global.h
	$(CC) $(CFLAGS) -std=$(STD) table.c

player.o: player.c player.h global.h
	$(CC) $(CFLAGS) -std=$(STD) player.c

clean:
	rm -f *.o main