CC=gcc
CFLAGS=-Wall -Werror -c
STD=c99

all: client server

client: client.o
	$(CC) client.o -o client

server: server.o  thpool.o
	$(CC) server.o thpool.o -o server -lpthread

client.o: client.c
	$(CC) $(CFLAGS) client.c

server.o: server.c
	$(CC) $(CFLAGS) server.c

thpool.o: thpool.c
	$(CC) $(CFLAGS) thpool.c
	
clean:
	rm -f *.o client server