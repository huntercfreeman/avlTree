CC=gcc
CFLAGS=-Wall -g

all: mainapp

mainapp: main.o avlTree.o stringBuilder.o
	$(CC) $(CFLAGS) main.o avlTree.o stringBuilder.o -o mainapp

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

avlTree.o: avlTree.c
	$(CC) $(CFLAGS) -c avlTree.c

stringBuilder.o: stringBuilder.c
	$(CC) $(CFLAGS) -c stringBuilder.c

clean:
	rm a.out *.o mainapp
