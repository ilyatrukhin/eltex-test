obj-m += hello.o

all:
	make -C /lib/modules/5.11.0-40-generic/build M=$(shell pwd) modules

clean:
	make -C /lib/modules/5.11.0-40-generic/build M=$(shell pwd) clean