CC=gcc
CFLAGS=-Wall -Werror -c
STD=c99

all: task1.o task2.o task3.o
	$(CC) task1.o -o  task1
	$(CC) task2.o -o  task2
	$(CC) task3.o -o  task3

task1.o:
	$(CC) $(CFLAGS) -std=$(STD) task1.c

task2.o:
	$(CC) $(CFLAGS) -std=$(STD) task2.c
	
task3.o:
	$(CC) $(CFLAGS) -std=$(STD) task3.c
	
clean:
	rm -f *.o task1 task2 task3
