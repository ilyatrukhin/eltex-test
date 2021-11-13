all: tcpserver tcpforkserver tcpselectserver tcpclient

tcpserver: tcpserver.c
	gcc -o tcpserver tcpserver.c

tcpforkserver: tcpforkserver.c
	gcc -o tcpforkserver tcpforkserver.c

tcpselectserver: tcpselectserver.c
	gcc -o tcpselectserver tcpselectserver.c intvector.c

tcpclient: tcpclient.c
	gcc -o tcpclient tcpclient.c

clean:
	rm -f tcpserver tcpforkserver tcpselectserver tcpclient
