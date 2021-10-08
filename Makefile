CC=gcc
CFLAGS=-Wall -Werror -o
STD=c99

all:
	$(CC) -std=$(STD) $(CFLAGS) hello hello.c

clean:
	rm -f hello
