TARGET = my_language

LEX_FILE = language.l
YACC_FILE = parser.y
SOURCE_FILES = scope.c symbol_table.c exec_fun.c stack.c opt_tree.c

LEX_C = lex.yy.c
YACC_C = parser.tab.c
YACC_H = parser.tab.h

CC = gcc
CFLAGS = -Wall -g -Wno-unused-function

all: clean $(TARGET)

$(TARGET): $(LEX_C) $(YACC_C) $(SOURCE_FILES)
	$(CC) $(CFLAGS) -o $@ $^

$(LEX_C): $(LEX_FILE) $(YACC_H)
	flex -o $@ $<

$(YACC_C) $(YACC_H): $(YACC_FILE)
	bison -d --verbose -o $(YACC_C) $<

clean:
	rm -f $(LEX_C) $(YACC_C) $(YACC_H) $(TARGET)

run: $(TARGET)
	./$(TARGET) input.txt

