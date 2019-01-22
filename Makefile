## Simple C Makefile

## Define compiler and flags
CC=cc 
CXX=cc 
CCFLAGS=-g -std=c99 -Wall -Werror -lpthread

# Compile all C files to O files

all: hello

%.o : %.c
	$(CC) -c $(CCFLAGS) $<

hello: four.o
	$(CC) -o four four.o $(CCFLAGS)

test: hello
	./four

clean: 
	rm -f core *.o four