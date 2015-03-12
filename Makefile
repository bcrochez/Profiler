
CC=gcc
CFLAGS=-c -Wall -ansi -lMLV -lrt -std=gnu99

all: profiler test fact

profiler: main.o gui.o tree.o
	$(CC) bin/main.o bin/gui.o bin/tree.o -o bin/myprofiler -lMLV -lrt

test: src/test.c
	$(CC) src/test.c -o bin/test.o $(CFLAGS)
	$(CC) bin/test.o -o bin/test -lrt

fact: src/fact.c
	$(CC) src/fact.c -o bin/fact.o $(CFLAGS)
	$(CC) bin/fact.o -o bin/fact -lrt

tree.o: src/tree.c
	$(CC) src/tree.c -o bin/tree.o $(CFLAGS)
	
gui.o: src/gui.c
	$(CC)  src/gui.c -o bin/gui.o $(CFLAGS)
	
main.o: src/main.c
	$(CC) src/main.c -o bin/main.o $(CFLAGS)

rebuild: clean
	make
	
clean:
	rm -rf bin/*.o
	
mrproper: clean
	rm -rf bin/myprofiler
	rm -rf bin/test
	rm -rf bin/fact
