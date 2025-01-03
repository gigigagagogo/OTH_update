CC=gcc
CFLAGS=-O2 -Wall
SRC= main.c check.c

all: clean numbers.txt check

check:  ${SRC}
	${CC} $(CFLAGS) -o $@ $^

numbers.txt:
	seq 1 7 1000 > $@

clean:
	rm -f main.o check.o check numbers.txt
