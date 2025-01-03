LEX_FILE = add.l
LEX_C = lex.yy.c
LEX_O = lex.yy.o
EXEC = add

all: clean $(LEX_C) $(LEX_O) $(EXEC)

$(LEX_C): $(LEX_FILE)
	flex -o $@ $^

$(LEX_O): $(LEX_C)
	gcc -o $@ -c $<

$(EXEC): $(LEX_O)
	gcc -o $@ $^ -lfl

clean:
	rm -f $(LEX_C) $(LEX_O) $(EXEC)

