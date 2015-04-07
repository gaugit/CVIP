
CC=gcc

CFLAGS=-c -lm

all: part1 part2

part1: Part1.o routine.o Sobel.o
	$(CC) -o part1 Part1.o routine.o Sobel.o -lm

part2: Part2.o routine.o Sobel.o cake_make.o calculate.o
	$(CC) -o part2 Part2.o routine.o Sobel.o cake_make.o calculate.o -lm

routine.o: routine.c
	$(CC) $(CFLAGS) routine.c

Sobel.o: Sobel.c
	$(CC) $(CFLAGS) Sobel.c

cake_make.o: cake_make.c
	$(CC) $(CFLAGS) cake_make.c

calculate.o: calculate.c
	$(CC) $(CFLAGS) calculate.c

Part1.o: Part1.c
	$(CC) $(CFLAGS) Part1.c

Part2.o: Part2.c
	$(CC) $(CFLAGS) Part2.c

clean:
	rm *o
	rm part1
	rm part2
