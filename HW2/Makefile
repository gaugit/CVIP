
CC=gcc

CFLAGS=-c -lm

all: main

main: Main.o testfft.o fft2d.o
	$(CC) -o main Main.o testfft.o fft2d.o -lm

testfft.o: testfft.c
	$(CC) $(CFLAGS) testfft.c

fft2d.o: fft2d.c
	$(CC) $(CFLAGS) fft2d.c

Main.o: Main.c
	$(CC) $(CFLAGS) Main.c

clean:
	rm *o main
