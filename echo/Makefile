CC = gcc
CFLAGS = -g -O1 -Wall
LDLIBS = -lpthread

all: echoclient echoserveri 

echoclient: echoclient.c csapp.c
	$(CC) $(CFLAGS) -o echoclient echoclient.c csapp.c $(LDLIBS)

echoserveri: echoserveri.c csapp.c
	$(CC) $(CFLAGS) -o echoserveri echoserveri.c csapp.c $(LDLIBS)


clean:
	rm -f *.o *~ *.exe echoclient echoserveri csapp.o