obj-m := hello.o

all: default test_hello

default:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

test_hello:
	gcc -o test_hello test_hello.c

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
	rm -f test_hello