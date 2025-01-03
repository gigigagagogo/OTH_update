LEX_FILE = lctoup.l
LEX_C = lex.yy.c
LEX_O = lex.yy.o
EXEC = ltp

all: clean $(LEX_C) $(LEX_O) $(EXEC)

$(LEX_C): $(LEX_FILE)
	@echo "Esecuzione di flex..."
	flex -o $(LEX_C) $(LEX_FILE)

$(LEX_O): $(LEX_C)
	@echo "Compilazione di lex.yy.c...."
	gcc -c $(LEX_C) -o $(LEX_O)

$(EXEC): $(LEX_O)
	@echo "linking dell'oggetto per creare l'eseguibile"
	gcc $(LEX_O) -o $(EXEC) -ll

clean:
	rm -f $(LEX_C) $(LEX_O) $(EXEC)

