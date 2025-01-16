# Nome dell'eseguibile finale
TARGET = my_language

# File sorgenti
LEX_FILE = language.l
YACC_FILE = parser.y

# File generati da Flex e Bison
LEX_C = lex.yy.c
YACC_C = parser.tab.c
YACC_H = parser.tab.h

# Compilatore e opzioni
CC = gcc
CFLAGS = -Wall -g -Wno-unused-function

# Regole principali
all: clean $(TARGET)

# Regola per creare l'eseguibile
$(TARGET): $(LEX_C) $(YACC_C)
	$(CC) $(CFLAGS) -o $@ $^

# Regola per generare il lexer
$(LEX_C): $(LEX_FILE)
	flex -o $@ $<

# Regola per generare il parser
$(YACC_C) $(YACC_H): $(YACC_FILE)
	bison -d --verbose -o $(YACC_C) $<

# Regola per pulire i file generati
clean:
	rm -f $(LEX_C) $(YACC_C) $(YACC_H) $(TARGET)

# Regola per eseguire un test rapido
run: $(TARGET)
	./$(TARGET) input.txt

