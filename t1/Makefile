CC=gcc
CFLAGS=-Wall -Wextra

objs = main.o utils.o

all: main

main: $(objs)

main.o  : main.c utils.o 
utils.o : utils.h utils.c


clean:
	 rm -f $(objs) *~

purge: clean
	-rm main