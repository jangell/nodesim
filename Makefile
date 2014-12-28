CC=gcc
CFLAGS=-c -Wall

all: mysim

mysim: nodesim.o simulations.h random.o
	$(CC) -o sim nodesim.o random.o

nodesim.o: nodesim.c
	$(CC) $(CFLAGS) nodesim.c

random.o: random.c
	$(CC) $(CFLAGS) random.c

clean:
	rm *.o *~ sim