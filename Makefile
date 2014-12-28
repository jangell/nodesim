CC=gcc
CFLAGS=-c -Wall

all: mysim

mysim: nodesim.o simulations.h
	$(CC) -o sim nodesim.o

nodesim.o: nodesim.c
	$(CC) $(CFLAGS) nodesim.c

clean:
	rm *.o *~ sim