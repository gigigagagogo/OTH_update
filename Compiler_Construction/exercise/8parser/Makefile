CC=gcc 
CFLAGS=-O2 -Wall -ggdb

calc: calc.lex.c calc.tab.c
	$(CC) -o $@ $^ -lm

calc.tab.o: calc.tab.c calc.tab.h

calc.lex.o: calc.lex.c

calc.tab.c calc.tab.h: calc.y
	bison --defines -t $^

calc.lex.c: calc.l
	flex -o $@ $^

clean:
	rm -f calc calc.lex.* calc.tab.*
