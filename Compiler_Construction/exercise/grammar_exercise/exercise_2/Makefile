CC = gcc
CFLAGS = -O2
TARGET = main
SRC = main.c grammar.c queue.c util.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

clean:
	rm -f $(OBJ) $(TARGET)


