CC=gcc
CFLAGS=-Wall -Werror -c
STD=c99

all: prog1 prog2 seminit semremove

prog1: prog1.o
	$(CC) prog1.o -o prog1

prog2: prog2.o
	$(CC) prog2.o -o prog2

seminit: seminit.o
	$(CC) seminit.o -o seminit

semremove: semremove.o
	$(CC) semremove.o -o semremove
	
prog1.o: prog1.c
	$(CC) $(CFLAGS) prog1.c

prog2.o: prog2.c
	$(CC) $(CFLAGS) prog2.c

seminit.o: seminit.c
	$(CC) $(CFLAGS) seminit.c

semremove.o: semremove.c
	$(CC) $(CFLAGS) semremove.c

clean:
	rm -f *.o prog1 prog2 seminit semremove