CC=gcc
CFLAGS=-Wall -Werror -c
STD=c99
STATICLIBNAME=STATIC_LIB
DYNLIBNAME=DYN_LIB

all: resultstat resultdyn main_2

# program using static library
resultstat: main.o static_lib
	$(CC) main.o -L. -l$(STATICLIBNAME) -o resultstat

# program using dynamic library with static loading
resultdyn: dyn_lib main.o
	$(CC) main.o -L. -l$(DYNLIBNAME) -o resultdyn

# program using dynamic function loading 
main_2: main_2.o
	$(CC) main_2.o -o main_2 -ldl

# create static library
static_lib: f1.o f2.o
	ar rc lib$(STATICLIBNAME).a f1.o f2.o
	ranlib lib$(STATICLIBNAME).a

# sample compile
f1.o: f1.c
	$(CC) $(CFLAGS) -std=$(STD) f1.c

f2.o: f2.c
	$(CC) $(CFLAGS) -std=$(STD) f2.c

main.o: main.c
	$(CC) $(CFLAGS) -std=$(STD) main.c

# create dynamic library
dyn_lib: f1_dyn.o f2_dyn.o
	$(CC) -shared -o lib$(DYNLIBNAME).so f1.o f2.o

# PIC compile
f1_dyn.o: f1.c
	$(CC) $(CFLAGS) -fPIC f1.c

f2_dyn.o: f2.c
	$(CC) $(CFLAGS) -fPIC f2.c

main_2.o: main_2.c
	$(CC) $(CFLAGS) -std=$(STD) main_2.c
clean:
	rm -f *.[oa] *.so resultstat resultdyn main_2