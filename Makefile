# Makefile for the basic AVL-Tree implementation.
# Author: Philipp Schaad
# Creation Date: 151015

# Variable declarations:
CC=gcc
CFLAGS=-Wall -std=c99

all: avl_tree clean

avl_tree: avl_core.o avl_visualizer.o test-avl.o
	$(CC) $(CFLAGS) -o out/avl_tree avl_core.o avl_visualizer.o test-avl.o -lm

avl_core.o: avl_core.c
	$(CC) $(CFLAGS) -c avl_core.c

avl_visualizer.o: avl_visualizer.c
	$(CC) $(CFLAGS) -c avl_visualizer.c

test-avl.o: test-avl.c
	$(CC) $(CFLAGS) -c test-avl.c

clean:
	rm -rf *o
