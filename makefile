.PHONY: all clean

all: graph

graph: algo.c algo.h main.c
	gcc -Wall -g algo.c main.c -o graph

clean:
	rm -f algo graph *.o