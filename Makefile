CC=gcc
CFLAGS=-Wall -Werror -o
STD=c99

all:
	$(CC) -std=$(STD) $(CFLAGS) main main.c math.c

clean:
	rm -f main
